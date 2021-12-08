#include<iostream>
using namespace std;

int main(){
  cout<<"\t\tRound Robin CPU Scheduling Algorithm\n";
  int numberOfProcesses;
  cout<<"Enter number of processes: ";cin>>numberOfProcesses;
  int arrivalTime[numberOfProcesses], burstTime[numberOfProcesses], dup_burstTime[numberOfProcesses], processId[numberOfProcesses];
  for(int i=0;i<numberOfProcesses;i++){
    cout<<"Enter burst time of the process["<<i+1<<"]: ";
    cin>>burstTime[i];
    dup_burstTime[i] = burstTime[i];
    cout<<"Enter arrival time of the process["<<i+1<<"]: ";
    cin>>arrivalTime[i];
  }
  int quantum;cout<<"Enter quantum size: ";cin>>quantum;

  // implementing the algorithm
  int time = 0, waitingTime[numberOfProcesses], turnAroundTime[numberOfProcesses];
  float avgWaitingTime = 0, avgTurnAroundTime = 0;
  while(1){
    bool isDone = true;
    for(int i=0;i<numberOfProcesses;i++){
      if(dup_burstTime[i] > 0){
        isDone = false;
        if(dup_burstTime[i] > quantum){
          time += quantum;
          dup_burstTime[i] -= quantum;
        }
        else{
          time += dup_burstTime[i];
          waitingTime[i] = time - burstTime[i];
          avgWaitingTime += waitingTime[i];
          turnAroundTime[i] = waitingTime[i] + burstTime[i];
          avgTurnAroundTime += turnAroundTime[i];
          dup_burstTime[i] = 0;
        }
      }
    }
    if(isDone)break;
  }
  avgTurnAroundTime = (1.0*avgTurnAroundTime)/numberOfProcesses;
  avgWaitingTime = (1.0*avgWaitingTime)/numberOfProcesses;

  cout<<"ProcessId\t Waiting Time\t Turn around time\t burst time\n";
  for(int i=0;i<numberOfProcesses;i++){
    cout<<processId[i+1]<<"\t\t"<<waitingTime[i]<<"\t\t"<<turnAroundTime[i]<<"\t\t\t"<<burstTime[i]<<"\n";
  }
  cout<<"Avg Turn Around Time: "<<avgTurnAroundTime<<"\n";
  cout<<"Avg Waiting Time: "<<avgWaitingTime;

  return 0;
}