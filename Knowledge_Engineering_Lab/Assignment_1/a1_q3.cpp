#include<iostream>
#include<fstream>
using namespace std;

int main(){
	ofstream output;
   	output.open("output3.txt");
    ifstream input;
    input.open("input.txt");
    char ch;
    int count[26]={0};
	while(!input.eof()){
        input.get(ch);
        if(ch>='a'&&ch<='z')
        count[ch-'a']++;
    }
    for(int i=0;i<26;i++){
    	if(count[i]){
    		output<<char('a'+i)<<" "<<count[i]<<endl;
		}
	}
    input.close();
}



