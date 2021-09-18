#ifndef _list_h_
#define _list_h_


class PCB;


class PCBList {

private:
	struct Elem {
		PCB* pcb;
		Elem* next;
		Elem(PCB* pcb_) { pcb=pcb_;	next=0; }
		~Elem() { pcb=0; next=0; }
	};

	Elem* first;
	Elem* last;

public:
	PCBList();
	~PCBList();
	void insertPCB(PCB* pcb);
	void removePCB(PCB* pcb);
	void removeFirst();
	PCB* getPCB(PCB* pcb);
	PCB* getFirst();

};

class PCBTimeList {
private:
	struct Elem {
		PCB* pcb;
		int time;
		Elem* next;
		Elem(PCB* pcb_, int time_) { pcb=pcb_; time=time_; next=0; }
		~Elem() { pcb=0; next=0; }
	};

	Elem* first;
	Elem* last;

public:
	PCBTimeList();
	~PCBTimeList();
	void insertPCB(PCB* pcb, int time);
	void removeFirst();
	PCB* getPCB(PCB* pcb);
	PCB* getFirst();
	void update();

};


#endif
