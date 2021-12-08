#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll class_size = 5;
vector<vector<ll>>data(class_size);
vector<ll>values;
vector<ll>mean_values(class_size);

int main(){
  ifstream input;
  input.open("input_3.txt");
  ofstream output;
  output.open("output3.txt");
  string s;
  ll total = 0;
  ll missing_values_count = 0;
  while(getline(input, s)){
    stringstream ss(s);
    string num;
    while(ss>>num){
      ll n = (ll)stoi(num);
      values.push_back(n);
      if(n == -1) missing_values_count++;
      else{
        data[n%class_size].push_back(n);
        total+=n;
      }
    }
  }
  for(ll i=0;i<data.size();i++){
    ll mean = 0;
    for(auto j : data[i]) mean += j;
    mean = mean/data[i].size();
    mean_values[i] = mean;
  }
  for(auto i : values){
    if(i == -1){
      random_device r;
      mt19937 gen(r());
      uniform_int_distribution<>dis(1,class_size);
      ll random_num = dis(gen);
      output<<mean_values[random_num]<<" ";
    }else{
      output<<i<<" ";
    }
  }
  output<<"\n";
  input.close();
  output.close();
  return 0;
}