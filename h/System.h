#ifndef _system_h_
#define _system_h_

class PCB;

typedef void interrupt (*FPointer)(...);

class System{
	public:
	    static PCB* idle;
		static FPointer oldRoutine;
		static FPointer newRoutine;
		static void interrupt timer(...);
		static void setNewTimer();
		static void restoreOldTimer();
};

#endif 
