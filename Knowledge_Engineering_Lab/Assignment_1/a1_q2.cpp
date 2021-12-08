#include<iostream>
#include<fstream>
#include<ostream>
using namespace std;

int main(){
    ifstream input;
    input.open("input.txt");
    string s;
    ofstream output;
    output.open("output2.txt");
	while(input){
        while(getline(input,s))output<<s<<endl;
    }
    input.close();
}
