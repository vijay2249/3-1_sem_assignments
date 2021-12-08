#include <fstream>
#include <iostream>
using namespace std;

int main(){
   ofstream outfile;
   outfile.open("output1.txt");
   outfile<<"T1 a b c e"<<"\n";
   outfile<<"T2 b d f"<<"\n";
   outfile<<"T3 a c d f"<<"\n";
   outfile<<"T4 d f"<<"\n";
   outfile<<"T5 c d e"<<"\n";
   return 0;
}


