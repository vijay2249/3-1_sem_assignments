#include<bits/stdc++.h>
using namespace std;

int min_support=2;

vector<string> items;
map<string,int> items_count;
vector<vector<string> > data;
map<string,vector<pair<vector<string> ,int > > >CPB;
map<pair<string,string>,int >CFPT;
map<string,vector<string> >FPG;

bool frequency(string a,string b){
	if(items_count[a]>items_count[b]) return true;
	else return false;
}

void check_min_support(vector<string> &temp){
	vector<string>t;
	for(int i=0;i<temp.size();i++)
		if(items_count[temp[i]]>=min_support) t.push_back(temp[i]);
	temp=t;
}

typedef struct fptree{
	int freq;
	struct fptree *FP[10];
	string data;
	int level;
} * FPTPTR;

void new_node(FPTPTR &T,string s){
	FPTPTR t=new fptree();
	t->freq=1;
	t->level=0;
	t->data=s;
	for(int i=0;i<10;i++) t->FP[i]=NULL;
	T=t; 
}

int search(string s){
	for(int i=0;i<items.size();i++){
		if(items[i]==s) return i;
	}
	return -1;
}

void insert(FPTPTR &T,vector<string> temp){
	FPTPTR t=T;
	int level=-1;
	for(int i=0;i<temp.size();i++){
		int k=search(temp[i]);
		if(t->FP[k]==NULL){
			new_node(t->FP[k],temp[i]);
			t->level=level+1;
			level=t->level;
		}
		else t->FP[k]->freq++;
		t=t->FP[k];
	}
}

void print(FPTPTR T,vector<string> v,int k){
	if(T==NULL) return;
	if(v.size()>0){
		string s=v[v.size()-1];
		v.pop_back();
		if(v.size()>0) CPB[s].push_back({v,k});
		v.push_back(s);
	}
	for(int i=0;i<10;i++){
		if(T->FP[i]!=NULL){
			v.push_back(T->FP[i]->data);
			print(T->FP[i],v,min(k,T->FP[i]->freq));
			v.pop_back();
		}
	}		
}

void FI_Generation(vector<string>&v,vector<vector<string> > &result,vector<string> temp,int start,string s){
	if(temp.size()>0){
		temp.push_back(s);
		if(find(result.begin(),result.end(),temp)==result.end()) result.push_back(temp);
		temp.pop_back();
	}
	for(int i=start;i<v.size();i++){
		temp.push_back(v[i]);
		FI_Generation(v,result,temp,i+1,s);
		temp.pop_back();
	}
	return;
}

int main(){
	ifstream inputfile;
	inputfile.open("input.txt");
	ofstream outputfile;
	outputfile.open("output.txt");
	string s;
	vector<string> t;
	while(inputfile>>s){
		if(s.size()>=2&&s[0]=='T'){
			if(t.size()>0)
			data.push_back(t);
			t.clear();
		}
		else{
			if(find(t.begin(),t.end(),s)==t.end()){
				t.push_back(s);
				if(find(items.begin(),items.end(),s)==items.end()) items.push_back(s);
				items_count[s]++;
			}
		}
	}
	if(t.size()>0) data.push_back(t);
	sort(items.begin(),items.end());
	for(int i=0;i<data.size();i++) sort(data[i].begin(),data[i].end(),frequency);
	for(int i=0;i<data.size();i++) check_min_support(data[i]);
	outputfile<<"items & frequency :\n";
	for(auto x:items_count){
		outputfile<<x.first<<" "<<x.second<<endl;
	}
	FPTPTR T=NULL;
	new_node(T,"( )");
	for(int i=0;i<data.size();i++){
		insert(T,data[i]);
	}
	vector<string > v;
	print(T,v,100);
	outputfile<<"Conditional Pattern Base "<<endl;
	for(auto x:CPB){
		for(int i=0;i<x.second.size();i++){
			outputfile<<x.first<<"->";
			for(int j=0;j<x.second[i].first.size();j++){
				CFPT[{x.first,x.second[i].first[j]}]+=x.second[i].second;
				outputfile<<x.second[i].first[j]<<" ";
			}
			outputfile<<"\t-\t"<<x.second[i].second<<endl;
		}
	}
	outputfile<<"Conditional FP TREE :"<<endl;
	for(auto x:CFPT){
		if(x.second>=min_support){
			FPG[x.first.first].push_back(x.first.second);
			outputfile<<x.first.first<<"->"<<x.first.second<<"\t-\t"<<x.second<<endl;
		}
	}
	outputfile<<"Frequent patterns Generated "<<endl;
	for(auto x:FPG){
		vector<vector<string> >result;
		vector<string>temp;
		FI_Generation(x.second,result,temp,0,x.first);
		for(int i=0;i<result.size();i++)
		{
			outputfile<<x.first<<"->";
			for(int j=0;j<result[i].size();j++)
			{
				outputfile<<result[i][j]<<" ";
			}
			outputfile<<"\t-\t"<<CFPT[{x.first,result[i][0]}]<<endl;
		}
	}
	
}
