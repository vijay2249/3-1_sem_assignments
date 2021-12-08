#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<vector<ll>>data_values;
vector<ll>values;
vector<ll>bin_set;
ll bin_size = 3;

int main(){
  ifstream input; input.open("input_2.txt");
  ofstream output; output.open("output2.txt");
  string s;
  // O(n)
  while(getline(input,s)){
    stringstream ss(s);
    string num;
    while(ss >> num) values.push_back((ll)stoi(num));//since all the input is in string format, convert into ll
  }
  // O(nlogn)
  sort(values.begin(), values.end()); //sort the input numbers
  ll it = 0;
  // O(n)
  for(ll i=0;i<values.size();i++){
    bin_set.push_back(values[i]);//add the numbers to bin
    it++;//check whether the size of bin is reached to max or not
    // if yes then add the bin to vector and clear it to add next bin set
    if(it%bin_size == 0){
      data_values.push_back(bin_set);
      bin_set.clear();
    }
  }
  if(values.size()%bin_size != 0) data_values.push_back(bin_set);
  // O(n)
  output<<"Partition into Bin's\n";
  for(ll i=0;i<data_values.size();i++){
    output<<"Bin "<<(i+1)<<": ";
    for(ll j=0;j<data_values[i].size();j++){
      output<<data_values[i][j];
      output<<" ";
    }
    output<<"\n";
  }
  output<<"\n\nSmoothing by bin means\n";
  for(ll i=0;i<data_values.size();i++){
    output<<"Bin "<<(i+1)<<": ";
    ll total = 0, count = 0;
    for(ll j=0;j<data_values[i].size();j++){
      total += data_values[i][j];
      count++;
    }
    ll mean = total/count;
    while(count--){
      output<<mean<<" ";
    }
    output<<"\n";
  }
  output<<"\n\nSmoothing by bin boundaries: \n";
  for(ll i=0;i<data_values.size();i++){
    output<<"Bin "<<(i+1)<<": ";
    for(ll j=0;j<data_values[i].size();j++){
      if(j==0 || j == data_values[i].size()-1){
        output<<data_values[i][j]<<" ";
      }else{
        ll mini_val = data_values[i][j]-data_values[i].front();
        ll maxi_val = data_values[i].back()-data_values[i][j];
        ll val = (maxi_val > mini_val)? data_values[i].front() : data_values[i].back();
        output<<val<<" ";
      }
    }
    output<<"\n";
  }
  input.close();
  output.close();
  return 0;
}