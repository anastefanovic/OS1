#include "PCB.h"
#include "Thread.h"
#include "List.h"
#include "Schedule.h"
#include <dos.h>
#include <iostream.h>

PCB* PCB::running = 0;
PCBTimeList* PCB::sleepingList=new PCBTimeList();

PCB::PCB (StackSize stackSize_, Time timeSlice_, Thread* myThread_) {
	stackSize = stackSize_ / sizeof(StackSize);
	timeSlice = timeSlice_;
	myThread = myThread_;
	status = NEW;
	stack=0;
	blockedOnMe=new PCBList();
}

PCB::~PCB () {
	delete stack;
}

#ifndef BCC_BLOCK_IGNORE

void PCB::createStack () {
	stack = new unsigned int [stackSize];
	stack[stackSize - 1] = 0x0200;
	stack[stackSize - 2] = FP_SEG(wrapper);
	stack[stackSize - 3] = FP_OFF(wrapper);
	sp = bp = FP_OFF(stack + stackSize - 12);
	ss = FP_SEG(stack + stackSize - 12);
}

#endif

void PCB::wrapper () {
	running->myThread->run();
	running->status=FINISHED;
	PCB* pcb=running->blockedOnMe->getFirst();
	running->blockedOnMe->removeFirst();
	while(pcb) {
		pcb->status=READY;
		Scheduler::put(pcb);
		pcb=running->blockedOnMe->getFirst();
		running->blockedOnMe->removeFirst();
	}
	dispatch();
}
