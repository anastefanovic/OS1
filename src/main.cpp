#include "System.h"
#include "PCB.h"
#include "IdleT.h"
extern userMain(int argc, char**argv);

PCB* initMain;

int main(int argc, char**argv){
	IdleThread* idleThread = new IdleThread();
	initMain=new PCB(4096, 2, 0);
	PCB::running = initMain;
	System::setNewTimer();
	userMain(argc, argv);
	System::restoreOldTimer();
	return 0;
}

