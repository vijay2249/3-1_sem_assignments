#include<vector>
#include <fstream>
#include<sstream>
using namespace std;

int n = 2;//Total number of Classes - yes or no
vector<vector<string>> Data;
vector<vector<string>> test_data;
vector<float> class_prob(n, 0);

float prob(string x, int k, string c){
  int siz = Data[0].size();
  float count1 = 0, count2 = 0;
  for (int i = 0; i < Data.size(); i++){
    if (Data[i][siz - 1] == c){
      count1++;
      if (Data[i][k] == x) count2++;
    }
  }
  return float(count2 / count1);
}

int main(){
  ifstream fin;
  fin.open("Input.txt");
  string str;
  getline(fin, str);
  while (getline(fin, str)){
    stringstream ss(str);
    string s1, s2;
    ss >> s1;
    vector<string> v;
    v.clear();
    while (ss >> s2) v.push_back(s2);
    Data.push_back(v);
  }
  int size = Data.size();
  ifstream f1;
  f1.open("testing_data.txt");
  int p = 0;
  while (getline(f1, str))
  {
    stringstream ss(str);
    string s2;
    vector<string> v;
    v.clear();
    while (ss >> s2) v.push_back(s2);
    test_data.push_back(v);
  }
  int s = Data[0].size();
  for (int i = 0; i < Data.size(); i++){
    if (Data[i][s - 1] == "yes") class_prob[1]++;
    else class_prob[0]++;
  }
  for (int i = 0; i < class_prob.size(); i++) class_prob[i] = class_prob[i] / size;
  ofstream f2;
  f2.open("output.txt");
  f2 << "Test samples:\n"<< "\n";
  for (int i = 0; i < test_data.size(); i++){
    float max = 0.0;
    string class_calculated;
    for (int a = 0; a < test_data[i].size(); a++) f2 << test_data[i][a] << " ";
    for (int c = 0; c < n; c++){
      float pxc = 1.0;
      for (int j = 0; j < test_data[i].size(); j++){
        string s;
        if (c == 0) s = "no";
        else s = "yes";
        pxc = pxc * prob(test_data[i][j], j, s);
      }
      pxc = pxc * class_prob[c];
      if (max < pxc){
        max = pxc;
        class_calculated = (c == 0) ? "no" : "yes";
      }
    }
    f2 << ": class is " << class_calculated;
    if (class_calculated == "yes") f2 << ": buys computer" << "\n";
    else f2 << ": doesnot buy computer" << "\n";
    f2 << "\n";
  }
}