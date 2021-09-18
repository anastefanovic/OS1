#ifndef _idlethread_h_
#define _idlethread_h_

#include "Thread.h"

class IdleThread:public Thread {
public:
	IdleThread();
	void run();

};

#endif
