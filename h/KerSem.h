#ifndef _kersem_h_
#define _kersem_h_


#include "List.h"

class Semaphore;


class KernelSem {
public:
	KernelSem(int value_);
	~KernelSem();
	int value;
	PCBList *blocked;
};

#endif
