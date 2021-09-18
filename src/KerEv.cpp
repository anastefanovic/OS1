#include "KerEv.h"
#include "PCB.h"
#include "Schedule.h"


KernelEv::KernelEv(IVTNo ivtNo_){
	value = 0;
	owner = PCB::running;
	ivtNo = ivtNo_;
}


KernelEv::~KernelEv(){
	owner = 0;
	
}

void KernelEv::signal(){
	asm pushf
	asm cli
	if (value == 1){
		value = 0;
		owner->status = READY;
		Scheduler::put(owner);
	}
	asm popf
}