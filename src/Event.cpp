#include "Event.h"
#include "KerEv.h"
#include "PCB.h"
#include "Schedule.h"
#include "IVTEntry.h"

extern void dispatch();


Event::Event(IVTNo ivtNo){
	myImpl = new KernelEv(ivtNo);
	if (IVTEntry::ivtEntries[ivtNo] != 0)
		IVTEntry::ivtEntries[ivtNo]->event = myImpl;
}

Event::~Event(){
	if (IVTEntry::ivtEntries[myImpl->ivtNo] != 0)
		IVTEntry::ivtEntries[myImpl->ivtNo]->event = 0;
	delete myImpl;
}

void Event::wait(){
	asm pushf
	asm cli
	if (PCB::running == myImpl->owner && myImpl->value == 0){
		myImpl->value = 1;
		myImpl->owner->status = BLOCKED;
		asm popf
		dispatch();
	}
	else 
		asm popf
}

void Event::signal(){
	asm pushf
	asm cli
	if (myImpl->value == 1){
		myImpl->value = 0;
		myImpl->owner->status = READY;
		Scheduler::put(myImpl->owner);
	}
	asm popf
}