#include "KerSem.h"

KernelSem::KernelSem(int value_){
	value=value_;
	blocked=new PCBList();
}

KernelSem::~KernelSem(){
	delete blocked;
}


