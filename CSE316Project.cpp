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
		int responseTime;
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
			status = a;
		}
		void BURST_UPDATE(int burst) {
			burstTime = burst;
		}
}process[10];

int queue_burst[10],queue_arrivalTime[10],queue_priority[10],queue_turnAround[10],temp_burst[10],complitionTime[10];
int timer = 0,limit;


								/*ROUND ROBIN QUEUE SCHEDULLING*/
void roundRobinProcessing() {
	int timeQuantum = 2;       //declartion of "TIME QUANTUM"

	int count = 0; 
	int n = sizeof(queue_burst)/sizeof(int);
	int loop = *max_element(queue_burst,queue_burst+n) / timeQuantum;
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
								/*FUNCTION FOR SORTING USING ARRIVAL TIME*/
void arrivalTimeSorting(int size)
{
    for(int i = 0; i < size-1; i++) {     
        for(int j = i + 1; j < size; j++) { 
            if(process[i].getArrivalTime() > process[j].getArrivalTime()) {
                swap(process[i],process[j]);
            }
        }   
    }
}

void priorityProcessing() {	
	for(int i=0;i<limit;i++) {
		int time = process[i+1].getArrivalTime();
		temp_burst[i] = temp_burst[i] - time;
		if(queue_priority[i] <= queue_priority[i+1]) {
			timer += queue_burst[i];
			queue_burst[i] = 0;
			process[i].setStatus(0);
			complitionTime[i] = timer;
		}
		else {
			process[i].setStatus(1);
			timer++;
			continue;
		}
	}
	
}
								/*MAIN FUNCTION*/
int main() {
	int number,first = 1000;
	cout<<"Enter the Number of processes:\t";
	cin>>number;
	limit = number;
	for(int i=0;i<number;i++) {		
		cout<<"-------------------------------------------------------------------------------------"<<endl;
		cout<<"ENTER THE DETAILS OF PROCESS "<<i+1<<endl;
		process[i].getDetails(i+1);		
	}
	arrivalTimeSorting(number);                     //calling the "ARRIVALTIMESORTING" function
	//cout<<"after sort";
	for(int i=0;i<number;i++) {
		queue_burst[i] = process[i].getBurstTime();
		temp_burst[i] = process[i].getBurstTime();
		queue_arrivalTime[i] = process[i].getArrivalTime();
		queue_priority[i] = process[i].getPriority();
	}
	
	priorityProcessing();
	
	roundRobinProcessing();
	
	cout<<"Process\tTurn Around\tWaiting Time"<<endl;
	cout<<"--------------------------------------------------------------"<<endl;
	for(int i=0;i<number;i++) {
		cout<<process[i].getID()<<"\t\t"<<complitionTime[i]-queue_arrivalTime[i]<<"\t\t"<<(complitionTime[i]-queue_arrivalTime[i])-queue_burst[i]<<endl;
	}
	
	return 0;
	
}
