#include<iostream>
using namespace std;

int main(){
  cout<<"\t\tPriority Based Scheduling Algorithm\n";
  int numberOfProcesses;
  cout<<"Enter number of processes: ";cin>>numberOfProcesses;
  int burstTime[numberOfProcesses], priority[numberOfProcesses], processId[numberOfProcesses];
  for(int i=0;i<numberOfProcesses;i++){
    cout<<"Enter bursttime for process["<<i+1<<"]: ";
    cin>>burstTime[i];
    cout<<"Enter priority  for process["<<i+1<<"]: ";
    cin>>priority[i];
    processId[i] = i;
  }

  // soting the values based on priority of the process 
  for(int i=0;i<numberOfProcesses;i++){
    bool swap = false;
    for(int j=0;i<numberOfProcesses-i-1;j++){
      if(priority[j] < priority[j+1]){
        int temp = burstTime[i];
        burstTime[j] = burstTime[j+1];
        burstTime[j+1] = temp;
        temp = priority[j];
        priority[j] = priority[j+1];
        priority[j+1] = temp;
        temp = processId[j];
        processId[j] = processId[j+1];
        processId[j+1] = temp;
        swap = true;
      }
    }
    if(swap) break;
  }
  int waitingTime[numberOfProcesses], turnAroundTime[numberOfProcesses];
  float avgWaitingTime = 0.0, avgTurnAroundTime = 0.0;
  for(int i=0;i<numberOfProcesses;i++){
    for(int j=0;j<i;j++){
      waitingTime[i] += burstTime[j];
    }
    avgWaitingTime += waitingTime[i];
    turnAroundTime[i] = burstTime[i] + waitingTime[i];
    avgTurnAroundTime += turnAroundTime[i];
  }
  avgTurnAroundTime = (1.0*avgTurnAroundTime)/numberOfProcesses;
  avgWaitingTime = (1.0*avgWaitingTime)/numberOfProcesses;

  cout<<"ProcessId\t Waiting Time\t Turn around time\t burst time\n";
  for(int i=0;i<numberOfProcesses;i++){
    cout<<processId[i]<<"\t\t"<<waitingTime[i]<<"\t\t\t"<<turnAroundTime[i]<<"\t\t\t"<<burstTime[i]<<"\n";
  }
  cout<<"Avg Turn Around Time: "<<avgTurnAroundTime<<"\n";
  cout<<"Avg Waiting Time: "<<avgWaitingTime;
  return 0;
}