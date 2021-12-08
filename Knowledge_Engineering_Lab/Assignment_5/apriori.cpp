#include<bits/stdc++.h>
using namespace std;
int min_confidence=30; 
map<string,int> ALL; 


int get_support(set<string>&candidate,map<string,set<string>>&transactions){
  int support=0;
  for(auto &i:transactions){
    set<string>temp=candidate;
    for(auto j:i.second){
      auto it=temp.find(j);
      if(it!=temp.end())
        temp.erase(it); // removing those instructions of current transaction which are 
        // found in candidate we are searching
    }
    if(temp.empty()) // if we found all items of candidates then we will increase support count
      support++;
  }
  return support; // returning final support count for given candidate
}

bool check(set<string>&merged,vector<map<set<string>,int>>&itemsets,int k){
  map<set<string>,int>m=itemsets[k-1];
  for(auto &i:merged){
    merged.erase(i); // removing 1 by 1 element from k itemset to generate all k-1 size sets 
    if(m.find(merged)==m.end()) // check if k-1 subset is present in candidateset
      return false;
    merged.insert(i); // again inserting that element to generate other subsets
  }
  return true; // return true if all subsets of candidate are frequent
}
vector<set<string>> join(vector<map<set<string>,int>>&itemsets,int k,
    vector<map<set<string>,int>>&candidates)
{
    vector<set<string>>c; // to store final answer
    map<set<string>,int>m=itemsets[k];
    auto it1=m.begin();
    auto it2=m.begin();
    // two iterators to check all possible pairs and join them
    while(it1!=m.end())
    {
        it2=it1;
        it2++;
        while(it2!=m.end())
        {
            set<string>merged=it1->first;
            merged.insert(it2->first.begin(),it2->first.end());
            // create a merged set of itemset from both itemsets 
            // check if size of merged itemset is 1 more than original and all k size subsets are frequent
            if(merged.size()==k+1 && check(merged,itemsets,k+1)) 
                c.push_back(merged);
            it2++;
        }
        it1++;
    }
    return c;
}
void generate(map<string,set<string>>&transactions,vector<map<set<string>,int>>&candidates,
    vector<map<set<string>,int>>&itemsets,int max_size,int min_support)
{
    for(int k=2;k<=max_size,!itemsets[k-1].empty();k++) //generating k-itemsets using k-1 candidates
    {
        vector<set<string>>c=join(itemsets,k-1,candidates);// candidate set for k-1

        for(auto candidate:c)
        {
            int support=get_support(candidate,transactions);// getting support count for candidate
            candidates[k][candidate]=support;
            if(support>=min_support)
                itemsets[k][candidate]=support; // adding to frequent itemset if supp>=min_supp
        }
    }
}
unordered_set<string> ispresent;
void print(string str){
    if(str.length()==1)return;
    int n=str.length();
   

    for(int i=1;i<n;i++){
        string s=str;
        string first=s.substr(0,i),sec=s.substr(i,n-i);
        string temp=first;
       sort(s.begin(),s.end());
       sort(temp.begin(),temp.end());
       sort(sec.begin(),sec.end());
       
        if(ALL.find(s)==ALL.end())continue;

        float support=(ALL[s]*100.0)/ALL[temp];
        if(ispresent.find(s+" "+temp)!=ispresent.end())continue;
         ispresent.insert(s+" "+temp);
       if(support>=min_confidence) cout<<first<<"->"<<sec<<endl;
    }
}

void permute(string s,int first,int last){
    if(first==last){
        print(s);
    }
    else{
        for(int i=first;i<=last;i++){
          swap(s[first],s[i]);
          permute(s,first+1,last);
          swap(s[first],s[i]);
        }
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string s;
    map<string,set<string>>transactions;// store transaction database
    vector<map<set<string>,int>>candidates;// candidates[k] will be k-itemset which are candidates
    vector<map<set<string>,int>>itemsets; // itemsets[k] will be k-itemset which is frequent
    map<string,int>counter;// to store 1-itemsets and their support counts
    int max_size=0;// to store maximum size of transaction
    int min_support=2;
    while(getline(cin,s))
    {
        stringstream ss(s);
        int k=0;
        string t,i;
        ss>>t;
        while(ss>>i)
            transactions[t].insert(i),counter[i]++;
        max_size=max(max_size,(int)transactions[t].size());
    }
    candidates.resize(max_size+1);
    itemsets.resize(max_size+1);
    for(auto i:counter)
        {
            candidates[1][{i.first}]=i.second;
            if(i.second>=min_support)
                itemsets[1][{i.first}]=i.second;
        }
    //storing 1-itemsets 
    generate(transactions,candidates,itemsets,max_size,min_support);
    for(int i=1;i<=max_size;i++)
    {
        if(!itemsets[i].empty())
        { for(auto j:itemsets[i])
            { string p="";
              for(auto k:j.first)p=p+k[1];
              ALL[p]=j.second;}
        }
    }


      for(int i=1;i<=max_size;i++)
    {
        if(!itemsets[i].empty())
        {
            for(auto j:itemsets[i])
            {
                string p="";
                for(auto k:j.first)
                  { p=p+k[1];}
                 permute(p,0,p.length()-1);
            }
        }
    }
}