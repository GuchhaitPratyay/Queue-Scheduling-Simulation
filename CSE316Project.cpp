/*LEVEL:1 PRIORITY PREEMTIVE QUEUE SCHEDULING,LEVEL:2 ROUNDROBIN QUEUE SCHEDULING*/
#include<iostream>
#include<algorithm>
using namespace std;

class Process {
	private:
		int processId;
		int burstTime;
		int priority;
		int arrivalTime;
		int waitingTime;
		int turnAroundTime;
		//int responseTime;
		int status;
	public:
		void getDetails(int id) {
			cout<<"Arrival Time:\t";
			cin>>this->arrivalTime;
			cout<<endl<<"Burst Time:\t";
			cin>>this->burstTime;
			cout<<endl<<"Priority:\t";
			cin>>this->priority;
			this->processId = id;
		}
		int getPriority() {
			return priority;
		}
		int getBurstTime() {
			return burstTime;
		}
		int getArrivalTime() {
			return arrivalTime;
		}
		int getStatus() {
			return status;
		}
		int getID() {
			return processId;
		}
		void setStatus(int a) {
			this->status = a;
		}
		void BURST_UPDATE(int burst) {
			burstTime = burst;
		}
}process[10];

int process_burst[10],process_arrivalTime[10],process_priority[10],process_turnAround[10],temp_burst[10],complitionTime[10];
int timer = 0,limit;

/**************************************ROUND ROBIN QUEUE SCHEDULLING***************************************/
void roundRobinProcessing() {
	int timeQuantum = 4;       //declartion of "TIME QUANTUM"

	int count = 0; 
	int n = sizeof(process_burst)/sizeof(int);
	int loop = *max_element(process_burst,process_burst+n) / timeQuantum;
	while(loop--) {
		for(int i=0;i<limit;i++) {
			count++;
			if(temp_burst[i] != 0 && process[i].getStatus() == 1) {
				temp_burst[i] -= timeQuantum;
				timer += timeQuantum;
				//queue_turnAround[i] += timeQuantum;
				complitionTime[i] += timeQuantum;
			}
			
		}
	}
}
/*********************************************FUNCTION FOR SORTING USING ARRIVAL TIME*************************************************/
void arrivalTimeSorting(int size)
{
    for(int i = 0; i < size-1; i++) {     
        for(int j = 0; j < size; j++) { 
            if(process[j].getArrivalTime() > process[j+1].getArrivalTime()) {
                swap(process[j],process[j+1]);
            }
        }   
    }
}
/*******************************************FIXED PRIORITY PRE-EMPTIVE SCHEDULING*****************************************************/
void priorityProcessing() {
	int timeSlice = 6;				//declaration of Time Slice
	vector<Process> p;
	for(int i=0;i<limit;) {
		int time = process[i+1].getArrivalTime();
		temp_burst[i] = temp_burst[i] - time;
		timeSlice -= time;
		if(process_priority[i] <= process_priority[i+1]) {
			timer += timeSlice;
			process_burst[i] -= timeSlice ;
			process[i].setStatus(1);
			complitionTime[i] = timer;
			i++;
		}
		else {
			p.push_back(process[i]);
			i++;
			//timer++;
			//continue;
		}
	}
	vector<Process>::interator i = p.begin();
	for(;
}
/********************************************************MAIN FUNCTION***********************************************************/
int main() {
	int number;
	cout<<"ENTER THE NUMBER OF PROCESSES:\t";
	cin>>number;
	limit = number;
	for(int i=0;i<number;i++) {		
		cout<<"----------------------------------------------------------------------------------"<<endl;
		cout<<"ENTER THE DETAILS OF PROCESS "<<i+1<<endl;
		process[i].getDetails(i+1);		
	}
	arrivalTimeSorting(number);                     //calling the "ARRIVALTIMESORTING" function
	
	for(int i=0;i<number;i++) {
		process_burst[i] = process[i].getBurstTime();
		temp_burst[i] = process[i].getBurstTime();
		process_arrivalTime[i] = process[i].getArrivalTime();
		process_priority[i] = process[i].getPriority();
	}
/********************************Fixed Priority Preemptive Scheduling******************************************************/	
	priorityProcessing();
/********************************Round Robin Scheduling********************************************************************/	
	roundRobinProcessing();
/*********************************Printing of the Final Table**************************************************************/	
	cout<<"Process\tTurn Around\tWaiting Time"<<endl;
	cout<<"--------------------------------------------------------------"<<endl;
	for(int i=0;i<number;i++) {
		cout<<process[i].getID()<<"\t\t"<<complitionTime[i]-queue_arrivalTime[i]<<"\t\t"<<(complitionTime[i]-queue_arrivalTime[i])-queue_burst[i]<<endl;
	}
	return 0;
}
