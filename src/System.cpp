#include "Thread.h"
#include "System.h"
#include "PCB.h"
#include "Schedule.h"
#include "List.h"
#include <iostream.h>
#include <dos.h>

FPointer System::oldRoutine = 0;
FPointer System::newRoutine = 0;

PCB* System::idle=0;

volatile int counter = 0;
volatile int dispatchCalled = 0;

#ifndef BCC_BLOCK_IGNORE

void System::setNewTimer(){
	oldRoutine = getvect(0x08);
	newRoutine = timer;
	setvect(0x60, oldRoutine);
	setvect(0x08, newRoutine);
}


void System::restoreOldTimer(){
	setvect(0x08, oldRoutine);
}

#endif

unsigned int sp_;
unsigned int bp_;
unsigned int ss_;
extern void tick();

void interrupt System::timer(...){
	if (!dispatchCalled){
		counter--;
		PCB::sleepingList->update();
		asm int 0x60
		tick();
	}
	if (dispatchCalled || counter == 0 || PCB::running == idle){
		asm{
			mov sp_, sp
			mov bp_, bp
			mov ss_, ss
		}
		PCB::running->sp = sp_;
		PCB::running->bp = bp_;
		PCB::running->ss = ss_;

		if(PCB::running->status==RUNNING && PCB::running!=idle) {
			PCB::running->status=READY;
			Scheduler::put(PCB::running);
		}

		PCB::running=Scheduler::get();

		if(PCB::running!=0) {
			PCB::running->status=RUNNING;
			counter=PCB::running->timeSlice;
		}
		else {
			PCB::running = idle;
			counter=1;
		}

		sp_=PCB::running->sp;
		bp_=PCB::running->bp;
		ss_=PCB::running->ss;
		asm {
			mov sp, sp_
			mov bp, bp_
			mov ss, ss_
		}
	}
	if (dispatchCalled) dispatchCalled=0;
}

void dispatch(){
	asm pushf
	asm cli
	dispatchCalled = 1;
	asm int 0x08;
	asm popf
}
