#include <dos.h>
#include "IVTEntry.h"
#include "KerEv.h"

IVTEntry* IVTEntry::ivtEntries[256] = {0};

IVTEntry::IVTEntry(IVTNo ivtNo_, FunctionPointer newRoutine_){
	ivtNo = ivtNo_;
	newRoutine = newRoutine_;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(ivtNo);
	setvect(ivtNo, newRoutine);
#endif
	ivtEntries[ivtNo] = this;
	event = 0;
}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, oldRoutine);
#endif
	event = 0;
	ivtEntries[ivtNo] = 0;
}

