#include<map>
#include<vector>
#include<fstream>
#include<set>
#include<unordered_map>
#include<math.h>
#include<string>
#include<sstream>
using namespace std;

int class_attribute;
int no_attributes;

map<int,string>map_attributes;
vector<map<string,int>>attribute_map;
vector<vector<string>>training_data,prdt_data,tst_data;
ofstream output("output.txt");
ifstream inputfile_training_data,inputfile_predicting_data,inputfile_testing_data;

typedef struct dtnode{
	int count;
	string node_name;
	unordered_map<string,struct dtnode*> child;
	struct dtnode * parent;
	string par_branch;
}* DTPTR;

double info_d(vector<vector<string>> Data,set<int> attribute_list){
	int n = Data.size();
	double ans = 0;
	map<string,int>count_map;
	count_map.clear();
	for(int i = 0;i < Data.size();i++) count_map[Data[i][class_attribute]]++;
	for(auto itr:count_map){
		int x = count_map[itr.first];
		double pi = (x*1.0)/(n*1.0);
		if(pi == 0 || x == 0)continue;
		if(n==2 || n==3) ans += (pi*log2(pi));
	}
	if(ans==0) return 0;
	return -ans;
}


double info_attr(vector<vector<string>> Data, int attribute, set<int> attribute_list, map<string,vector<vector<string>>> mm[]){
	double ans = 0;
	int n = Data.size();
	for(auto itr:attribute_map[attribute]){
		vector<vector<string>> dj = mm[attribute][itr.first];
		int num = dj.size();
		double val = (num*1.0)/n;
		double gfg = info_d(dj,attribute_list);
		ans += (val*gfg);
	}
	return ans;
}

int best_attribute(vector<vector<string>> Data, set<int> attribute_list){
	double x = info_d(Data,attribute_list);
	map<string,vector<vector<string>>>map_creating_branches[no_attributes];
	for(int i = 0;i < Data.size();i++){
		for(auto j:attribute_list){
			if(map_creating_branches[j].count(Data[i][j]) == 0){
				vector<string>v1 = Data[i];
				vector<vector<string>>v2;
				v2.clear();
				v2.push_back(v1);
				map_creating_branches[j][Data[i][j]] = v2;
			}
			else map_creating_branches[j][Data[i][j]].push_back(Data[i]);
		}
	}
	double y, gain, mx = -1.0;
	int best_attributes;
	for(auto it:attribute_list){
		y = info_attr(Data,it,attribute_list,map_creating_branches);
		gain = (x-y);
		if(gain > mx){
			mx = gain;
			best_attributes = it;
		}
	}
	return best_attributes;
}

DTPTR generate_DT(vector<vector<string>> Data,set<int> attribute_list){
	DTPTR temp = new(struct dtnode);
	vector<vector<string>>rows = Data;
	map<string,int> class_label;
	class_label.clear();
	int mx = -1;
	string str;
	for(int i = 0;i < rows.size();i++){
		class_label[rows[i][class_attribute]]++;
		if(class_label[rows[i][class_attribute]] > mx){
			mx = class_label[rows[i][class_attribute]];
			str = rows[i][class_attribute];
		}
	}
	if(class_label.size() == 1){
		auto it = class_label.begin();
		temp->count = class_attribute;
		temp->node_name = it->first;
		temp->child.clear();
		return temp;
	}
	if(attribute_list.empty()){
		temp->count = class_attribute;
		temp->node_name = str;
		temp->child.clear();
		return temp;
	}
	int best = best_attribute(Data,attribute_list);
	attribute_list.erase(best);
	temp->count = best;
	temp->node_name = map_attributes[temp->count];
	temp->parent = NULL;
	map<string,vector<vector<string>>>map_creating_branches;
	for(int i = 0;i < rows.size();i++){
		if(map_creating_branches.count(Data[i][best]) == 0){
			vector<string> v1 = rows[i];
			vector<vector<string>>v2;
			v2.clear();
			v2.push_back(v1);
			map_creating_branches[Data[i][best]] = v2;
		}
		else map_creating_branches[Data[i][best]].push_back(rows[i]);
	}
	for(auto itr:attribute_map[best]){
		vector<vector<string>>Dj;
		string feature = itr.first;
		Dj = map_creating_branches[feature];
		DTPTR temp1 = new(struct dtnode);
		if(Dj.empty()){
			map<string,int>class_label_1;
			class_label_1.clear();
			int mx1 = -1;
			string str1;
			for(int i = 0;i < Data.size();i++){
				class_label_1[Data[i][class_attribute]]++;
				if(class_label_1[rows[i][class_attribute]] > mx1){
					mx1 = class_label_1[rows[i][class_attribute]];
					str1 = Data[i][class_attribute];
				}
			}
			temp1->count = class_attribute;
			temp1->node_name = str1;
			temp1->parent = temp;
			temp1->par_branch = feature;
			temp->child[feature] = temp1;
		}
		else{
			set<int>new_attr_list=attribute_list;
			new_attr_list.erase(best);
			DTPTR parr = generate_DT(Dj,new_attr_list);
			temp->child[feature] = parr;
			parr->parent = temp;
		}
	}
	return temp;	
}

void print(DTPTR t){
	if(t){
		output<<"[NODE_NAME->";
		output<<"("<<map_attributes[t->count]<<") its branches:{";
		int g = 1;
		for(auto it:t->child){
			output<<"branch"<< g++ <<"->("<<it.first<<")->";
			print(it.second);
			output<<",";
		}
		output<<"}]";
	}
}

string get_class(vector<string> tup,DTPTR T){
	while(T->count != class_attribute){
		string gs = tup[T->count];
		T = T->child[gs];
	}
	return T->node_name;
}

int main(){
	inputfile_training_data.open("training_data.txt");
	inputfile_testing_data.open("testing_data.txt");
	inputfile_predicting_data.open("predicting_data.txt");
	string s;
	getline(inputfile_training_data,s);
	stringstream str(s);
	str >> s;
	no_attributes = 0;
	set<int>attribute_list;
	while(str >> s){
		no_attributes++;
		attribute_list.insert(no_attributes);
		map_attributes[no_attributes] = s;
	}
	class_attribute = no_attributes;
	attribute_list.erase(class_attribute);
	attribute_map.resize(no_attributes+1);
	while(getline(inputfile_training_data,s)){
		vector<string>row;
		row.clear();
		stringstream str1(s);
		string s1,s2;
		str1 >> s1;
		row.push_back(s1);
		int p = 1;
		while(str1 >> s2){
			attribute_map[p++][s2]++;
			row.push_back(s2);
		}
		training_data.push_back(row);
	}
	output<<"Given Training sample data:"<<"\n";
	for(int i = 0;i < training_data.size();i++){
		output<<"RID"<<(i+1)<<"\t";
		for(int j = 0;j < training_data[i].size();j++)
		output<<training_data[i][j]<<" ";
		output<<"\n";
	}
	output<<"\n\n";
	DTPTR root = NULL;
	root = generate_DT(training_data,attribute_list);
	output<<"Created Decision Tree according to splits in preorder:-\n";
	print(root);
	output<<"\n";
	getline(inputfile_testing_data,s);
	while(getline(inputfile_testing_data,s)){
		vector<string>row;
		row.clear();
		stringstream str(s);
		string sdd="dummy";
		string s1;
		row.push_back(sdd);
		while(str >> s1) row.push_back(s1);
		tst_data.push_back(row);
	}
	getline(inputfile_predicting_data,s);
	while(getline(inputfile_predicting_data,s)){
		vector<string> row;
		row.clear();
		stringstream str(s);
		string sdd = "dummy";
		string s1;
		row.push_back(sdd);
		while(str >> s1) row.push_back(s1);
		prdt_data.push_back(row);
	}
	inputfile_testing_data.close();
	inputfile_predicting_data.close();
	inputfile_testing_data.open("testing_data.txt");
	inputfile_predicting_data.open("predicting_data.txt");
	output<<"\nGiven testing set and their estimated class label \n";
	string str1;
	getline(inputfile_testing_data,s);
	output<<str1<<"\tEstimated_Class \n";
	double tst_acc;
	int crct = 0,tot;
	tot = tst_data.size();
	for(int i = 0;i < tst_data.size();i++){
		getline(inputfile_testing_data,s);
		output << s;
		str1 = tst_data[i][class_attribute];
		string str2 = get_class(tst_data[i],root);	
		output<<"\t"<<str2<<"\n";
		if(str1 == str2) crct++;
	}
	tst_acc = (crct*1.0)/tot;
	output<<"\nGiven predict sample and their predicted class label:\n";
	getline(inputfile_predicting_data,s);
	output<<str1<<"\t "<<"predicted_class \n";
	for(int i = 0;i < prdt_data.size();i++){
		getline(inputfile_predicting_data,s);
		output<<s;
		string str2 = get_class(prdt_data[i],root);	
		output<<"\t"<<str2<<"\n";
	}
	output<<"\nTesting_accuracy is:"<<tst_acc<<"\n";
	return 0;
}