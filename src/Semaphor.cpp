#include "Semaphor.h"
#include "Schedule.h"
#include "KerSem.h"
#include "PCB.h"

extern void dispatch();

Semaphore::Semaphore(int init) {
	myImpl= new KernelSem(init);
}

Semaphore::~Semaphore() {
	delete myImpl;
}

int Semaphore::wait(int toBlock) {
	asm pushf
	asm cli
	if(toBlock!=0) {
		if(--myImpl->value < 0) {
			PCB::running->status=BLOCKED;
			myImpl->blocked->insertPCB(PCB::running);
			asm popf
			dispatch();	
			return 1;
		}
		else {
			asm popf
			return 0;
		}
	}
	else {
		if(myImpl->value<=0) {
			asm popf
			return -1;
		}
		else {
			myImpl->value--;
			asm popf
			return 0;
		}
	}
}

void Semaphore::signal() {
	asm pushf
	asm cli
	if(myImpl->value++ < 0) {
		PCB* toUnblock=myImpl->blocked->getFirst();
		myImpl->blocked->removeFirst();
		toUnblock->status=READY;
		Scheduler::put(toUnblock);
	}
	asm popf
}

int Semaphore::val()const{
	return myImpl->value;
}