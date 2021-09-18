
#ifndef _kerev_h_
#define _kerev_h_

class PCB;
typedef unsigned char IVTNo;

class KernelEv{
	public:
		PCB* owner;
		int value;
		IVTNo ivtNo;

		KernelEv(IVTNo ivtNo_);
		~KernelEv();

		void signal();

};


#endif