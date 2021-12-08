#include<iostream>
using namespace std;

int main(){
  cout<<"\t\tShortest Job First CPU Scheduling Algorithm\n\n";
  int numberOfProcesses;
  cout<<"Enter number of processes: ";cin>>numberOfProcesses;
  int processesTrack[numberOfProcesses][6];
  for(int i=0;i<numberOfProcesses;i++){
    cout<<"Enter burst   time for process["<<i+1<<"]: ";
    cin>>processesTrack[i][2];
    cout<<"Enter arrival time for process["<<i+1<<"]: ";
    cin>>processesTrack[i][1];
    processesTrack[i][0] = 1;
  }

  // Sort the processes based on arrival time
  for(int i=0;i<numberOfProcesses;i++){
    for(int j=0;j<numberOfProcesses-i-1;j++){
      if(processesTrack[j][1] > processesTrack[j+1][1]){
        for(int z=0;z<5;z++){
          int temp = processesTrack[j][z];
          processesTrack[j][z] = processesTrack[j+1][z];
          processesTrack[j+1][z] = temp;
        }
      }
    }
  }
  // implementing the algorithm
  // choosing the process based on min burst time
  processesTrack[0][3] = processesTrack[0][1] + processesTrack[0][2];
  processesTrack[0][5] = processesTrack[0][3] - processesTrack[0][1];
  processesTrack[0][4] = processesTrack[0][5] - processesTrack[0][2];
  int p;
  for(int i=1;i<numberOfProcesses;i++){
    int minBurstTime = processesTrack[i][2];
    int temp = processesTrack[i-1][3];
    for(int j=0;i<numberOfProcesses;j++){
      if(temp >= processesTrack[j][1] && minBurstTime >= processesTrack[j][2]){
        minBurstTime = processesTrack[j][2];
        p = j;
      }
    }
    processesTrack[p][3] = temp + processesTrack[p][2];
    processesTrack[p][5] = processesTrack[p][3] - processesTrack[p][1];
    processesTrack[p][4] = processesTrack[p][5] - processesTrack[p][2];
    for(int j=0;i<6;j++){
      int val = processesTrack[p][j];
      processesTrack[p][j] = processesTrack[i][j];
      processesTrack[i][j] = val;
    }
  }

  float turnAroungTimeAvg = 0.0, waitingTimeAvg = 0.0;
  for(int i=0;i<numberOfProcesses;i++){
    turnAroungTimeAvg += processesTrack[i][5];
    waitingTimeAvg += processesTrack[i][4];
  }
  turnAroungTimeAvg = (1.0*turnAroungTimeAvg)/numberOfProcesses;
  waitingTimeAvg = (1.0*waitingTimeAvg)/numberOfProcesses;
  // print the output
  cout<<"Process ID\t Burst Time\t Arrival Time\t TurnAround Time\t Waiting Time\n";
  for(int i=0;i<numberOfProcesses;i++){
    cout<<processesTrack[i][0]<<"\t\t"<<processesTrack[i][2]<<"\t\t"<<processesTrack[i][1]<<"\t\t\t"<<processesTrack[i][5]<<"\t\t"<<processesTrack[i][4]<<"\n";
  }
  cout<<"Avg waiting time: "<<waitingTimeAvg<<"\n";
  cout<<"Avg turn around time: "<<turnAroungTimeAvg<<"\n";

  return 0;
}