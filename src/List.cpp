#include "List.h"
#include "PCB.h"
#include "Schedule.h"

//PCB list

PCBList::PCBList() {
	first=last=0;
}

PCBList::~PCBList() {
	Elem* delCur=0;
	Elem* cur=first;
	while(cur) {
		delCur=cur;
		cur=cur->next;
		delete delCur;
	}
	first=last=0;
}

 void PCBList::insertPCB(PCB* pcb) {
	 Elem* newPCB=new Elem(pcb);
	 if(last!=0) last->next=newPCB;
	 else first=newPCB;
	 last=newPCB;
 }

 void PCBList::removePCB(PCB* pcb) {
	 Elem *prev=0;
	 for(Elem *cur=first; cur!=0; cur=cur->next) {
		 if(cur->pcb==pcb) {
			 if(cur==first) { removeFirst(); return; }
			 if(cur==last) last=prev;
			 prev->next=cur->next;
			 delete cur;
			 return;
		 }
		 prev=cur;
	 }
 }

 void PCBList::removeFirst() {
	 if(first!=0) {
		 Elem* cur=first;
		 first=first->next;
		 delete cur;
		 if(first==0) last=0;
	 }
 }

PCB* PCBList::getPCB(PCB* pcb) {
	 for(Elem* cur=first; cur!=0; cur=cur->next)
	 if(cur->pcb==pcb) return cur->pcb;
	 return 0;
 }

PCB* PCBList::getFirst() {
	if(first!=0) return first->pcb;
	else return 0;
}

//Time list

PCBTimeList::PCBTimeList() { first=last=0; }

PCBTimeList::~PCBTimeList() {
	Elem* delCur=0;
	Elem* cur=first;
	while(cur) {
			delCur=cur;
			cur=cur->next;
			delete delCur;
	}
		first=last=0;
}


void PCBTimeList::insertPCB(PCB* pcb, int time) {
	Elem* prev=0;
	Elem* newPCB=new Elem(pcb, time);
	int totalTime=0;
	for(Elem* cur=first; cur!=0; cur=cur->next) {
		totalTime+=cur->time;
		if(newPCB->time <= totalTime) {
			newPCB->next=cur;
			if(prev!=0) {
				totalTime-=cur->time;
				prev->next=newPCB;
				newPCB->time-=totalTime;
				cur->time-=newPCB->time;
			}
			else { 
				first->time-=newPCB->time; 
				first=newPCB; 
			}
			return;
		}
		prev=cur;
	}
	if(first!=0) {
		newPCB->time-=totalTime;
		last->next=newPCB;
		last=newPCB;
	}
	else first=last=newPCB;
}

void PCBTimeList::removeFirst() {
	if(first) {
		Elem* cur=first;
		first=first->next;
		if(first==0) last=0;
		delete cur;
	}
}

PCB* PCBTimeList::getPCB(PCB* pcb) {
	 Elem *cur=first;
		 while(cur!=0 && cur->pcb!=pcb) cur=cur->next;
		 if(cur!=0) return cur->pcb;
		 else return 0;
}

PCB* PCBTimeList::getFirst() {
	if(first!=0) return first->pcb;
		else return 0;
}

void PCBTimeList::update() {
	if(first) {
		first->time--;
		while(first && first->time==0) {
			first->pcb->status=READY;
			Scheduler::put(first->pcb);
			removeFirst();
		}
	}
}
