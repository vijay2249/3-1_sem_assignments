#include<iostream>
#include<utility>
#include<vector>
#include<math.h>
#include<fstream>
#include<sstream>
using namespace std;

void print_vector_pair(vector<pair<double, double>> inputnumbers){
  for(int i=0;i< inputnumbers.size();i++)
    cout<<inputnumbers[i].first<<", "<<inputnumbers[i].second<<"\n";
}

double eucleadian_distance(pair<double,double> p1, pair<double,double> p2){
  return sqrt((p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second));
}

void print_clusters(vector<vector<pair<double,double>>> clusters, vector<pair<double,double>> centre){
  ofstream outputfile;
  outputfile.open("output.txt");
  for(int i=0;i<clusters.size();i++){
    outputfile<<"Cluster No.: "<<i+1<<"\n";
    outputfile<<"Centroid: ( "<<centre[i].first<<", "<<centre[i].second<<" )\n";
    outputfile<<"[\n";
    for(int j=0;j<clusters[i].size();j++)
      outputfile<<"\t("<<clusters[i][j].first<<", "<<clusters[i][j].second<<"),\n";
    outputfile<<"]\n";
  }
}

int main(){
  ifstream inputfile;
  inputfile.open("input.txt");
  int no_of_clusters;
  vector<pair<double, double>> inputnumbers;
  int i=0;
  while(!inputfile.eof()){
    if(i == 0){
      inputfile>>no_of_clusters;
      i++;
    }
    else{
      double x, y;
      pair<double,double> p;
      inputfile>>x>>y;
      p.first=x;
      p.second=y;
      inputnumbers.push_back(p);
    }
  }
  inputnumbers.pop_back();
  vector<vector<pair<double,double>>> clusters(no_of_clusters);
  vector<pair<double,double>> centre;
  for(int i=0;i<no_of_clusters;i++){
    clusters[i].push_back(inputnumbers[i]);
    centre.push_back(inputnumbers[i]);
  }
  for(int i=no_of_clusters;i< inputnumbers.size();i++){
    int min=-1, min_dist=INT_MAX;
    for(int j=0;j<no_of_clusters;j++){
      if(eucleadian_distance(inputnumbers[i],centre[j])<min_dist){
        min_dist=eucleadian_distance(inputnumbers[i],centre[j]);
        min=j;
      }
    }
    clusters[min].push_back( inputnumbers[i]);
    centre[min].first=(centre[min].first + inputnumbers[i].first)/2;
    centre[min].second=(centre[min].second + inputnumbers[i].second)/2;
  }
  print_clusters(clusters, centre);
}