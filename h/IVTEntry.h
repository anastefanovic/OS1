
#ifndef _ivtentry_h_
#define _ivtentry_h_


typedef unsigned char IVTNo;
typedef void interrupt (*FunctionPointer) (...);

class Event;
class KernelEv;

class IVTEntry{
	public:
		IVTNo ivtNo;
		KernelEv* event;
		FunctionPointer oldRoutine;
		FunctionPointer newRoutine;

		static IVTEntry* ivtEntries[256];

		IVTEntry(IVTNo ivtNo_, FunctionPointer newRoutine_);
		~IVTEntry();

	
};


#endif