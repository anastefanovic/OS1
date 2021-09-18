#ifndef _pcb_h_
#define _pcb_h_ 


typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55ms
typedef int ID;
typedef enum State {NEW, READY, RUNNING, BLOCKED, FINISHED};


class Thread;
class PCBList;
class PCBTimeList;

class PCB {

	public:
		StackSize stackSize;
		Time timeSlice;

		unsigned int sp;
		unsigned int bp;
		unsigned int ss;
        unsigned int* stack;

        PCBList* blockedOnMe;

        static PCBTimeList* sleepingList;

		Thread* myThread;
		
		State status;

		static PCB* running;

		PCB(StackSize stackSize_, Time timeSlice_, Thread* myThread_);
		~PCB();

		void createStack();

		static void wrapper();
};

#endif
