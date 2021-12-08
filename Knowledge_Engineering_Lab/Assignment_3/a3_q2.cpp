#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<map<set<string>,int>>itemsets;
vector<map<set<string>,int>>c_sets;
map<string, set<string>>trx;
map<string, int>counts;
ll size_max = 0;
ll min_sup = 2;

ll get_sup(set<string>&cd){
  ll sup = 0;
  for(auto &i: trx){
    set<string>temp = cd;
    for(auto j:i.second){
      auto it = temp.find(j);
      if(it != temp.end()) temp.erase(it);
    }
    if(temp.empty()) sup++;
  }
  return sup;
}

bool check(set<string>&merge, int k){
  map<set<string>, int>m=itemsets[k-1];
  for(auto &i:merge){
    merge.erase(i);
    if(m.find(merge) == m.end()) return false;
    merge.insert(i);
  }
  return true;
}

vector<set<string>>join(ll k){
  vector<set<string>>c;
  map<set<string>, int>m = itemsets[k];
  auto t1 = m.begin();
  while(t1 != m.end()){
    auto t2 = t1;
    t2++;
    while(t2 != m.end()){
      set<string> merge = t1->first;
      merge.insert(t2->first.begin(), t2->first.end());
      if(merge.size() == k+1 && check(merge, k+1)) c.push_back(merge);
      t2++;
    }
    t1++;
  }
  return c;
}

void generate_sets(){
  for(ll k=2;k<=size_max, !itemsets[k-1].empty(); k++){
    vector<set<string>>c = join(k-1);
    for(auto cd: c){
      ll sup = get_sup(cd);
      c_sets[k][cd] = sup;
      if(sup >= min_sup) itemsets[k][cd] = sup;
    }
  }
}

int main(){
  ifstream input;
  input.open("input.txt");
  ofstream output;
  output.open("output2.txt");
  string s;
  while(getline(input,s)){
    stringstream ss(s);
    string t,i;
    ss>>t;
    while(ss>>i){
      trx[t].insert(i);
      counts[i]++;
    }
    size_max = max(size_max, (ll)trx[t].size());
  }
  c_sets.resize(size_max+1);
  itemsets.reserve(size_max+1);
  cout<<size_max<<" "<<min_sup<<endl;
  for(auto i:counts){
    c_sets[1][{i.first}] = i.second;
    if(i.second >= min_sup) itemsets[1][{i.first}] = i.second;
  }
  generate_sets();
  for(ll i=1;i<=size_max;i++){
    if(!itemsets[i].empty()){
      output<<"L"<<i<<"Itemsets:\n";
      for(auto j:c_sets[i]){
        for(auto k:j.first){
          output<<k<<" ";
        }
        output<<"with support of"<<j.second<<endl;
      }
      output<<endl;
    }
  }
  return 0;
}