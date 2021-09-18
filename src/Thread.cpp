#include "Thread.h"
#include "PCB.h"
#include "Schedule.h"
#include "List.h"

Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB = new PCB(stackSize, timeSlice, this);
}

Thread::~Thread(){
	delete myPCB;
}

void Thread::start(){
	myPCB->createStack();
	myPCB->status = READY;
	Scheduler::put(myPCB);
}

void Thread::waitToComplete() {
	if(myPCB->status!=FINISHED && myPCB->status!=NEW && myPCB!=PCB::running) {
		PCB::running->status=BLOCKED;
		myPCB->blockedOnMe->insertPCB(PCB::running);
		dispatch();
	}
}

void Thread::sleep(Time timeToSleep) {
	if(timeToSleep > 0) {
		PCB::running->status=BLOCKED;
		asm pushf
		asm cli
		PCB::sleepingList->insertPCB(PCB::running, timeToSleep);
		asm popf
		dispatch();
	}
}
