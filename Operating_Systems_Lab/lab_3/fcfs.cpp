#include<iostream>
using namespace std;

int main(){
  cout<<"\t\"First come First Serve\" CPU Scheduling Algorithm\n\n";
  int numberOfProcesses;
  cout<<"Enter number of processes: ";cin>>numberOfProcesses;
  int burstTime[numberOfProcesses], arrivalTime[numberOfProcesses], processId[numberOfProcesses];
  for(int i=0;i<numberOfProcesses;i++){
    cout<<"Enter burst   time for process["<<i+1<<"]: ";
    cin>>burstTime[i];
    cout<<"Enter arrival time for process["<<i+1<<"]: ";
    cin>>arrivalTime[i];
    processId[i] = i;
  }
  // Sort the processes based on arrival time
  for(int i=0;i<numberOfProcesses;i++){
    bool swap = false;
    for(int j=0;j<numberOfProcesses-i-1;j++){
      if(arrivalTime[j] > arrivalTime[j+1]){
        int temp = arrivalTime[j];
        arrivalTime[j] = arrivalTime[j+1];
        arrivalTime[j+1] = temp;
        temp = burstTime[i];
        burstTime[j] = burstTime[j+1];
        burstTime[j+1] = temp;
        temp = processId[j];
        processId[j] = processId[j+1];
        processId[j+1] = temp;
        swap = true;
      }
    }
    if(swap) break;
  }

  // Implementing the logic
  int finishTime[numberOfProcesses], waitingTime[numberOfProcesses], turnAroundTime[numberOfProcesses];
  finishTime[0] = arrivalTime[0] + burstTime[0];
  turnAroundTime[0] = finishTime[0] - arrivalTime[0];
  waitingTime[0] = turnAroundTime[0] - burstTime[0];
  float waitingTimeSum = waitingTime[0];
  float turnAroundTimeSum = turnAroundTime[0];
  for(int i=1;i<numberOfProcesses;i++){
    finishTime[i] = burstTime[i] + finishTime[i-1];
    turnAroundTime[i] = finishTime[i] - arrivalTime[i];
    turnAroundTimeSum += turnAroundTime[i];
    waitingTime[i] = turnAroundTime[i] - burstTime[i];
    waitingTimeSum += waitingTime[i];
  }
  waitingTimeSum = (1.0*waitingTimeSum)/numberOfProcesses;
  turnAroundTimeSum = (1.0*turnAroundTimeSum)/numberOfProcesses;

  // printing the output
  cout<<"Process ID\t Burst Time\t Arrival Time\t TurnAround Time\t Finish Time\n";
  for(int i=0;i<numberOfProcesses;i++){
    cout<<processId[i]<<"\t\t "<<burstTime[i]<<"\t\t "<<arrivalTime[i]<<"\t\t "<<turnAroundTime[i]<<"\t\t\t "<<finishTime[i]<<"\n";
  }
  cout<<"Avg. Waiting time: "<<waitingTimeSum<<"\n";
  cout<<"Avg. TurnAround Time: "<<turnAroundTimeSum<<"\n";
  return 0;
}