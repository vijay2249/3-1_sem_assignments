#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<string>names;
vector<double>n1_salaries, n1_expected, n1_experience;
vector<double>n2_salaries, n2_expected, n2_experience;
vector<double>n3_salaries, n3_expected, n3_experience;
ll new_min = 0;
ll new_max = 1;
ll diff = new_max-new_min;

int main(){
  ifstream input;
  input.open("input.txt");
  ofstream output;
  output.open("output_1.txt");
  string s;
  vector<ll>salary, expected, experience;
  ll salary_index,exp_index,ex_index, names_index, temp=0;
  if(getline(input, s)){
    stringstream ss(s);
    string word;
    while(ss>>word){
      output<<word<<"\t\t\t";
      if(word == "Name")names_index = temp;
      else if(word == "Salary")salary_index = temp;
      else if(word == "Expected")exp_index = temp;
      else if(word == "Experience") ex_index = temp;
      temp++;
    }
    output<<"\n";
  }
  ll min_sal = INT_MAX, max_sal = INT_MIN;
  ll min_exp = INT_MAX, max_exp = INT_MIN;
  ll min_ex = INT_MAX, max_ex = INT_MIN;
  double avg_sal = 0, avg_exp = 0, avg_ex = 0;
  while(getline(input, s)){
    stringstream ss(s);
    string word;
    ll index = 0;
    while(ss>>word){
      if(index == salary_index){
        ll sal = (ll)stoi(word);
        salary.push_back(sal);
        avg_sal+= sal*1.0;
        min_sal = (min_sal > sal)? sal: min_sal;
        max_sal = (max_sal < sal)? sal: max_sal;
      }
      else if(index == exp_index){
        ll sal = (ll)stoi(word);
        avg_exp += sal*1.0;
        expected.push_back(sal);
        min_exp = (min_exp > sal)? sal: min_exp;
        max_exp = (max_exp < sal)? sal: max_exp;
      }
      else if(index == ex_index){
        ll age = (ll)stoi(word);
        avg_ex+=age*1.0;
        experience.push_back(age);
        min_ex = (min_ex > age)? age: min_ex;
        max_ex = (max_ex < age)? age: max_ex;
      }
      else if(index == names_index){
        names.push_back(word);
      }
      index++;
    }
  }
  avg_ex /=20;
  avg_exp /=20;
  avg_sal /=20;
  // n-1 method
  output<<"\n\n";
  output<<"Normalization min-max Method:";
  output<<"\n\n";
  for(auto i : salary){
    double new_sal = (i-min_sal)*(diff)*1.0;
    new_sal = new_sal/(max_sal-min_sal);
    new_sal += new_min;
    n1_salaries.push_back(new_sal);
  }
  for(auto i : expected){
    double new_val = (i-min_exp)*1.0*(diff);
    new_val = new_val/(max_exp-min_exp);
    new_val += new_min;
    n1_expected.push_back(new_val);
  }
  for(auto i : experience){
    double new_val = (i-min_ex)*1.0*(diff);
    new_val = new_val/(max_ex-min_ex);
    new_val += new_min;
    n1_experience.push_back(new_val);
  }
  for(ll i=0;i<names.size();i++){
    output<<names[i]<<"\t\t\t"<<n1_salaries[i]<<"\t\t\t"<<n1_expected[i]<<"\t\t\t"<<n1_experience[i]<<"\n";
  }
  output<<"\n\n";
  // n2 method
  output<<"Normalization using z-score method:  ";
  output<<"\n\n";
  ll sd = 0;
  for(auto i : salary){
    sd += pow((i-avg_sal), 2);
  }
  sd = 1.0*sd/20;
  for(auto i: salary){
    double new_val = (i-avg_sal)/sd;
    n2_salaries.push_back(new_val);
  }
  sd = 0;
  for(auto i : expected){
    sd += pow((i-avg_exp), 2);
  }
  sd = 1.0*sd/20;
  for(auto i: expected){
    double new_val = (i-avg_exp)/sd;
    n2_expected.push_back(new_val);
  }
  sd = 0;
  for(auto i : experience){
    sd += pow((i-avg_ex), 2);
  }
  sd = 1.0*sd/20;
  for(auto i: experience){
    double new_val = (i-avg_ex)/sd;
    n2_experience.push_back(new_val);
  }
  for(ll i=0;i<names.size();i++){
    output<<names[i]<<"\t\t\t"<<n2_salaries[i]<<"\t\t\t"<<n2_expected[i]<<"\t\t\t"<<n2_experience[i]<<"\n";
  }
  output<<"\n\n";
  // n3 method
  output<<"Normalization using decimal scaling method: ";
  output<<"\n\n";
  for(auto i: salary){
    ll digits = 0;
    ll temp = i;
    while(temp>0){
      temp/=10;
      digits++;
    }
    double new_val = 1.0*(i/pow(10,digits));
    n3_salaries.push_back(new_val);
  }
  for(auto i: expected){
    ll digits = 0;
    ll temp = i;
    while(temp>0){
      temp/=10;
      digits++;
    }
    double new_val = 1.0*(i/pow(10,digits));
    n3_expected.push_back(new_val);
  }
  for(auto i: experience){
    ll digits = 0;
    ll temp = i;
    while(temp>0){
      temp/=10;
      digits++;
    }
    double new_val = 1.0*(i/pow(10,digits));
    n3_experience.push_back(new_val);
  }
  for(ll i=0;i<names.size();i++){
    output<<names[i]<<"\t\t\t"<<n3_salaries[i]<<"\t\t\t"<<n3_expected[i]<<"\t\t\t"<<n3_experience[i]<<"\n";
  }
  return 0;
}