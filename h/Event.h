

#ifndef _event_h_
#define _event_h_
typedef unsigned char IVTNo;
class KernelEv;

#include "IVTEntry.h"
#include "KerEv.h"


class Event {
	public:
 		Event (IVTNo ivtNo);
 		~Event ();
 		void wait ();
	protected: 

 		friend class KernelEv;
 		void signal(); // can call KernelEv
	private:
 		KernelEv* myImpl;
};



#define PREPAREENTRY(num,callold)\
	void interrupt inter##num(...); \
	IVTEntry* ivtEntry##num = new IVTEntry(num, inter##num);\
	void interrupt inter##num(...){\
		if (ivtEntry##num->event){\
			ivtEntry##num->event->signal();\
		}\
		if (callold == 1){\
			if (ivtEntry##num->oldRoutine)\
				ivtEntry##num->oldRoutine();\
		}\
	}\


#endif 