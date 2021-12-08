#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<set>
#include<sstream>
#include<unordered_map>
#include<math.h>
using namespace std;

typedef long long ll;
ll M = 2, trx_var = 5, trxs;
vector<vector<ll>>transactions;
map<set<ll>,ll>m, L[10], C[10], CF,CI,IF,II;
float min_sup = 35.0;
ifstream fin;
ofstream fout("Output.txt");

int main(){
  fin.open("input.txt");
  string ss;
  ll count = 0;
  while(getline(fin, ss))count++;
  fin.close();
  min_sup = ceil((min_sup*count)/100);
  trxs = count;
  fin.open("Input.txt");
  string str;
  while(getline(fin, str)){
    stringstream ss(str);
    string s;
    vector<ll>v;
    while(ss>>s){
      s = s.substr(1,s.size()-1);
      v.push_back((ll)stoi(s));
      set<ll>sets;
      sets.insert((ll)stoi(s));
      C[1][sets]++;II[sets]=1;m[sets]=0;
    }
    sort(v.begin(), v.end());
    transactions.push_back(v);
  }
  ll index = 0;
  while(II.size() > 0 || IF.size() > 0){
    ll temp = M;
    while(temp--){
      vector<ll>temp_trx = transactions[index];
      unordered_map<ll, ll>p;
      for(ll i=0;i<temp_trx.size();i++)p[temp_trx[i]] = 1;
      for(auto i=IF.begin();i!=IF.end();i++){
        set<ll>s=i->first;
        auto s_temp = s.begin();
        bool flag = false;
        m[s]++;
        for(;s_temp!=s.end();s_temp++){
          if(p.count(*s_temp) == 0){
            flag = true;
            break;
          }
        }
        if(!flag)L[s.size()][s]++;
      }
      for(auto i=II.begin();i!=II.end();i++){
        set<ll>s=i->first;
        auto s_temp = s.begin();
        bool flag = false;
        m[s]++;
        for(;s_temp!=s.end();s_temp++){
          if(p.count(*s_temp) == 0){
            flag = true;
            break;
          }
        }
        if(!flag)L[s.size()][s]++;
      }
      vector<set<ll>>r;
      for(auto i = II.begin();i != II.end(); i++){
        set<ll>s = i->first;
        if(L[s.size()][s] >= min_sup){
          IF[s] = 1;
          r.push_back(s);
          vector<bool>b(trx_var+1, false);
          for(auto i2 = s.begin();i2 != s.end();i2++)b[*i2] = true;
          for(ll a = 1;a <= trx_var;a++){
            for(ll c = 1;c <= trx_var;c++){
              if(!b[c]){
                set<ll>check1, check2;
                check2 = s;
                check2.insert(c);
                bool flag = false;
                for(ll d = 0;d < s.size(); d++){
                  check1 = s;
                  auto temp_itr = check1.begin();
                  advance(temp_itr, d);
                  check1.erase(temp_itr);
                  check1.insert(c);
                  if(CF.count(check1) != 1 && IF.count(check1) != 1){
                    flag = true;
                    break;
                  }
                }
                if(!flag)II[check2] = 1;
              }
            }
          }
        }
      }
      for(ll i = 0;i < r.size(); i++) II.erase(r[i]);
      cout<<"first clear after\n";
      for(ll i=0;i<r.size();i++){
        for(auto j : r[i]){
          cout<<j<<" ";
        }
        cout<<"\n";
      }
      r.clear();
      for(auto i = IF.begin(); i != IF.end(); i++){
        set<ll>s = i->first;
        if(m[s] == trxs){
          r.push_back(s);CF[s]++;
        }
      }
      for(ll i = 0;i<r.size();i++)IF.erase(r[i]);
      r.clear();
      for(auto i = II.begin(); i != II.end(); i++){
        set<ll>s = i->first;
        if(m[s] == trxs){
          r.push_back(s);CI[s]++;
        }
      }
      for(ll i = 0;i<r.size();i++)IF.erase(r[i]);
      r.clear();
      index = (index+1)%trxs;
    }
  }
  fout<<"Frequent Itemsets: \n";
  for(ll i = 1;i<L[i].size();i++){
    fout<<i<<" itemset \n";
    for(auto j = L[i].begin();j != L[i].end(); j++){
      if(j->second >= min_sup){
        auto k = j->first.begin();
        fout<<"{ ";
        for(;k != j->first.end();k++)fout<<"T"<<*k<<" ";
        fout<<"}";
        fout<<" - sup_count = "<<j->second;
        fout<<"\n";
      }
    }
  }
  fin.close();
  fout.close();
  return 0;
}