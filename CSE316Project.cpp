/*LEVEL 1:FIXED PRIORITY PREMPTIVE SCHEDULING ,LEVEL 2:ROUND ROBIN SCHEDULING*/
#include<iostream>
#include<queue> 
using namespace std;

queue<int> queue_roundRobin; 
int flag[20],arrivalTime[20],burstTime[20],priority[20],remainTime[20],finishingTime[20],fe[20],fe_flag[20],processId[20],timer,qt[20];
int i=0,number,smallest=0,last_smallest=-1,minimum,sum=0,largeArrival=0;


void getDetails(int i) {
	cout<<"Enter the Process Id(1,2,3....): ";
        cin>>processId[i];
        cout<<"Enter Arrival Time: ";
        cin>>arrivalTime[i];
        cout<<"Enter Burst Time: ";
        cin>>burstTime[i];
        cout<<"Enter Priority: ";
        cin>>priority[i];
        cout<<"-------------------------------------------------------"<<endl;
 		if(arrivalTime[i] > largeArrival) {
            largeArrival = arrivalTime[i];
        }
        sum += burstTime[i];
        remainTime[i] = burstTime[i];
}
/*****************************************ROUND ROBIN SCHEDULING**************************************************/ 
void roundRobinProcessing() {
      if(!queue_roundRobin.empty())
      {
        if(remainTime[queue_roundRobin.front()]>0 && qt[queue_roundRobin.front()]<4)
        {
                qt[queue_roundRobin.front()]++;
                remainTime[queue_roundRobin.front()]--;
                if(remainTime[queue_roundRobin.front()]==0)
                {
                finishingTime[queue_roundRobin.front()]=timer+1;
                queue_roundRobin.pop();
                }
                if(remainTime[queue_roundRobin.front()]!=0 && qt[queue_roundRobin.front()]==4)
                {
                qt[queue_roundRobin.front()]=0;
                queue_roundRobin.push(queue_roundRobin.front());
                queue_roundRobin.pop();
                }
            }
      }
}


/******************************************MAIN FUNCTION*************************************************/
int main()
{
    cout<<"ENTER THE NUMBER OF PROCESSES: ";
    cin>>number;
    cout<<endl;
    for(i=0;i<number;i++) {       
        getDetails(i);
    }

    for(;!queue_roundRobin.empty() || timer <= sum+largeArrival;timer++)
    {
      	minimum = 20;
      	smallest=-1;
      	for(int i = 0;i < number; i++)
      	{
        	if(arrivalTime[i] <= timer && priority[i]< minimum && remainTime[i] > 0 && !flag[i])
        	{
            	minimum = priority[i];
            	smallest = i;
        	}
      	}
      	if(smallest == -1 && !queue_roundRobin.empty())
      	{
        	if(last_smallest !=-1 && remainTime[last_smallest]==0)
        	{
            	finishingTime[last_smallest] = timer;
                flag[last_smallest] = 1;
            }
            last_smallest=-1;
            roundRobinProcessing();
            continue;
      	}
      	else if(smallest!=-1 && !queue_roundRobin.empty() && last_smallest==-1) {
        	if(qt[queue_roundRobin.front()]<=4 && qt[queue_roundRobin.front()]>0) {
            	queue_roundRobin.push(queue_roundRobin.front());
            	queue_roundRobin.pop();
           	}
      	}
      	if(smallest!=-1 && !fe_flag[smallest]) {
        	fe[smallest] = timer - arrivalTime[smallest];
        	fe_flag[smallest] = 1;
      	}
      	if( smallest!=last_smallest && last_smallest!=-1 && !flag[last_smallest])
     	{
        	queue_roundRobin.push(last_smallest);
        	flag[last_smallest]=1;
      	}
      	if(smallest !=-1)
        remainTime[smallest]--;
     
      	if((smallest !=-1) && ((remainTime[smallest]==0) ||(burstTime[smallest]-remainTime[smallest])==6)) { //remaining burst
        	if((burstTime[smallest]-remainTime[smallest])==6 && remainTime[smallest]!=0) {
            	flag[smallest]=1;
            	queue_roundRobin.push(smallest);
        	}
        	else if(smallest!=-1)
        	{
            	finishingTime[smallest]=timer+1;
            	flag[smallest]=1;
        	}
      	}
      	last_smallest=smallest;
    }
/**********************************PRINTING THE FINAL TABLE*****************************************/    
    cout<<endl<<"**********THE FINAL TABLE(AFTER PROCESSING)**********"<<endl<<endl;
    
	cout<<"PROCESS ID\t"<<"WAITING TIME\t"<<"FINISH TIME\t"<<"TURNAROUND TIME\t"<<endl;
   	
	for(int i=0;i<number;i++){
   		cout<<processId[i]<<"\t\t"<<fe[i]<<"\t\t"<<finishingTime[i]<<"\t\t"<<finishingTime[i]-burstTime[i]-arrivalTime[i]<<endl;
 	}
 	return 0; 
}
