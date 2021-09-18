#include "IdleT.h"
//#include <iostream.h>
#include "Thread.h"
#include "System.h"
#include "PCB.h"

IdleThread::IdleThread():Thread(4096, 0) {
	System::idle=myPCB;
	myPCB->createStack();
}

void IdleThread::run() {
	//cout<<"Idle"<<endl;
	while(1){}
}


