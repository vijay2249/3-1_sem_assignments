#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll replace_missing_val_with_global_val = 40;

int main(){
  ifstream input;
  input.open("input_1.txt");
  ofstream output1; // method 1 output
  output1.open("output1_1.txt");
  ofstream output2; // method 2 output
  output2.open("output1_2.txt");
  ofstream output3; // method 3 output
  output3.open("output1_3.txt");
  string s;
  ll total = 0;
  ll total_nums = 0;
  while(getline(input, s)){
    stringstream ss(s);
    string num;
    while(ss>>num){
      total_nums ++;
      if((ll)stoi(num) != -1) {
        total += (ll)stoi(num);
        // method one data storing
        // Implementing method one-> ignoring the missing data-> updating the outputfile
        // this can be directly implemented while reading the data, as we are just ignoring the missed data
        // method one implementation
        output1<<(ll)stoi(num);
        output1<<" ";
        // method-2 data storing
        output2<<(ll)stoi(num);
        output2<<" ";
        // method-3 data storing
        output3<<(ll)stoi(num);
        output3<<" ";
      }
      else{
        // method-2 implementation as is asks for the missing data and have to enter it manually
        ll ask_input;cout<<"enter missing value: ";cin>>ask_input;
        output2<<ask_input;
        output2<<" ";
        // method - 3 implementation is to replace the missing data with the global_variable
        output3<<replace_missing_val_with_global_val;
        output3<<" ";
      }
    }
  }
  cout<<total/total_nums;
  input.close();
  output1.close();
  output2.close();
  output3.close();
  return 0;
}