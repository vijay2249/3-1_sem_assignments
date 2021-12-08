#include<bits/stdc++.h>
using namespace std;
float min_support=25;
vector<string> items;
map<string,vector<string>> input;
set<pair<int,vector<string>>> output;
map<vector<string>,int> freq;

bool calculate(vector<string> temp){
	int count=0;
	for(auto i: input){
		bool flag=true;
		for(int j=0;j<temp.size();j++){
			if(find(i.second.begin(),i.second.end(),temp[j])!=i.second.end())	continue;
			else{
				flag=false;
				break;
			}
		}
		if(flag)count++;
	}
	if(count>=min_support){
		output.insert({temp.size(),temp});
		freq[temp]+=count;
		return true;
	}
	return false;
}

void itemsets(vector<string> temp,vector<string> items,int start,int end,bool &b){
	if(temp.size()>end)
		return;
	else if(temp.size()==end){
		bool flag=calculate(temp);
		if(flag)
			b=true;
	}
	else{
		for(int i=start;i<items.size();i++){
			temp.push_back(items[i]);
			itemsets(items,temp,i+1,end,b);
			temp.pop_back();
		}
	}
}
int main(){
	ifstream inputFile;
	inputFile.open("input.txt");
	ofstream outputFile;
	outputFile.open("output3_1.txt");
	string s,t="";
	while(inputFile>>s){
		if(s[0]=='T' && s.length()>=2)t=s;
		else{
			if(find(input[t].begin(),input[t].end(),s)==input[t].end())	input[t].push_back(s);
			if(find(items.begin(),items.end(),s)==items.end()) items.push_back(s);
		}
	}
	float n=input.size()*min_support/100;
	min_support=ceil(n);
	for(int i=1;i<items.size();i++){
		vector<string> temp;
		bool b=false;
		itemsets(temp,items,0,i,b);
		if(!b)break;
	}
	for(auto i : output){
		outputFile<<i.first<<" ";
		for(int j=0;j<i.second.size();j++){
			outputFile<<i.second[j]<<" ";
		}
		outputFile<<freq[i.second]<<endl;
	}
	return 0;
}
