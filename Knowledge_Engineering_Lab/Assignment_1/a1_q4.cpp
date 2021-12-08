#include<bits/stdc++.h>
using namespace std;

int main(){
  ifstream input;
  input.open("input.txt");
  ofstream output;
	output.open("output4.txt");
  char ch;
  vector<int>count[26];
  int cnt=0;
	while(!input.eof()){
		input.get(ch);
		if(ch>='0'&&ch<='9'){
			cnt=ch-'0';
		}
		if(ch>='a'&&ch<='z'){
			count[ch-'a'].push_back(cnt);
		}
	}
	for(int i=0;i<26;i++){
		if(!count[i].empty()){
			output<<char('a'+i)<<" ";
			for(int j=0;j<count[i].size();j++){
				output<<count[i][j]<<" ";
			}
			output<<endl;
		}
	}
	input.close();
}
