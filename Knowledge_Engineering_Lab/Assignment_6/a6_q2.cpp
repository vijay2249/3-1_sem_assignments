#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
float min_sup = 35.0, min_conf = 0.5;
map<set<int>, int> L[101], C[101], FC[101], FL[101];
vector<vector<int>> transac;
int siz, N, low, high, mn_sup, mx = -1;
ifstream fin;
ofstream fout("output_2.txt");

bool prune(set<int> s, int k){
	for (int i = 0; i < s.size(); i++){
		set<int> s1 = s;
		auto itr = s1.begin();
		advance(itr, i);
		s1.erase(itr);
		if (!(L[k].count(s1)))	return false;
	}
	return true;
}

map<set<int>, int> apr_join(map<set<int>, int> l, int k){
	map<set<int>, int> res;
	map<set<int>, int>::iterator itr = l.begin(), ti1, ti2;
	for (int i = 0; i < l.size() - 1; i++){
		ti1 = itr;
		advance(ti1, i);
		set<int> s1 = (ti1)->first;
		for (int j = i + 1; j < l.size(); j++){
			ti2 = itr;
			advance(ti2, j);
			set<int> s2 = (ti2)->first;
			set<int>::iterator it1 = s1.begin(), it2 = s2.begin();
			set<int> ss;
			ss.clear();
			int x = 1;
			for (x = 1; x < k; x++){
				if (*it1 != *it2)	break;
				ss.insert(*it1);
				it1++;it2++;
			}
			if (x == k){
				ss.insert(*it1);
				ss.insert(*it2);
				if (prune(ss, k)) res[ss]++;
			}
		}
	}
	return res;
}

map<set<int>, int> getL(map<set<int>, int> gc){
	map<set<int>, int> res;
	map<set<int>, int>::iterator it = gc.begin(), ti;
	set<int> s;
	for (int i = 0; i < gc.size(); i++){
		ti = it;
		advance(ti, i);
		s = ti->first;
		set<int>::iterator itr = s.begin(), tsi;
		int sup = 0;
		for (int j = low; j < high; j++){
			int v1, v2;
			if (transac[j].size() < s.size())	continue;
			for (v1 = 0, v2 = 0; v1 < transac[j].size(); v1++){
				if (v2 == s.size())	break;
				tsi = itr;
				advance(tsi, v2);
				if (transac[j][v1] == *(tsi))	v2++;
			}
			if (v2 == s.size())	sup++;
		}
		if (sup >= mn_sup) res[s] = sup;
	}
	return res;
}

void subset(set<int> s, vector<bool> vis, int siz, int i){
	if (i < siz){
		subset(s, vis, siz, i + 1);
		vis[i] = true;
		subset(s, vis, siz, i + 1);
		vis[i] = false;
	}
	else if (i == siz){
		set<int> sub;
		vector<int> X, Y;
		for (int j = 0; j < siz; j++){
			auto it = s.begin();
			advance(it, j);
			if (vis[j]){
				X.push_back(*it);
				sub.insert(*it);
			}
			else Y.push_back(*it);
		}
		if (X.size() == 0 || X.size() == siz)	return;
		int num = L[s.size()][s];
		int den = L[X.size()][sub];
		float conf = num * 1.0 / den;
		if (conf >= min_conf){
			fout << "{ ";
			for (int j = 0; j < X.size(); j++){
				if (j < (X.size() - 1))	fout << X[j] << ",";
				else fout << X[j] << "}";
			}
			fout << " ==> {";
			for (int j = 0; j < Y.size(); j++){
				if (j < (Y.size() - 1))	fout << Y[j] << ",";
				else fout << Y[j] << "}";
			}
			fout << "\n";
		}
	}
}

void Gen_Ass_Rules(int k){
	fout << "Association Rules:-\n";
	for (int i = 1; i <= k; i++){
		auto it = FL[i].begin();
		for (; it != FL[i].end(); it++){
			vector<bool> vis(it->first.size(), false);
			subset(it->first, vis, it->first.size(), 0);
		}
	}
}

int main(){
	fin.open("Input.txt");
	N = 5;
	siz = 0;
	string str;
	while (getline(fin, str))	siz++;
	fin.close();
	int ps = siz/N;
	fin.open("Input.txt");
	while (getline(fin, str)){
		stringstream ss(str);
		string s1, s2;
		ss >> s1;
		vector<int> v;
		v.clear();
		while (ss >> s2){
			s2 = s2.substr(1, s2.size() - 1);
			int x = stoi(s2);
			v.push_back(x);
		}
		sort(v.begin(), v.end());
		transac.push_back(v);
	}
	int ii = 0;
	while (ii < transac.size()){
		C[1].clear();
		mn_sup = ceil((min_sup * ps) / 100);
		low = ii;
		for (int jj = 0; jj < ps && ii < transac.size(); jj++, ii++){
			for (int j = 0; j < transac[ii].size(); j++){
				set<int> se;
				se.insert(transac[ii][j]);
				C[1][se]++;
			}
		}
		high = ii;
		L[1].clear();
		for (auto it = C[1].begin(); it != C[1].end(); it++)
			if (it->second >= mn_sup)	L[1][it->first] = it->second;
		int k;
		for (k = 2; L[k - 1].size() != 0; k++){
			C[k].clear();
			C[k] = apr_join(L[k - 1], k - 1);
			L[k].clear();
			L[k] = getL(C[k]);
		}
		int d;
		for (d = 1; L[d].size() > 0; d++){
			for (auto itr = L[d].begin(); itr != L[d].end(); itr++){
				set<int> s = itr->first;
				FC[s.size()][s] += itr->second;
			}
		}
	}
	mn_sup = ceil((min_sup * siz) / 100);
	low = 0;
	high = transac.size();
	for (int v = 1; FC[v].size() > 0; v++) FL[v] = getL(FC[v]);
	fout << "FREQUENT ITEMSETS:\n";
	int i;
	for (i = 1; FL[i].size() > 0; i++){
		fout << i << "-itemset" << endl;
		for (auto it = FL[i].begin(); it != FL[i].end(); it++){
			auto itr = it->first.begin();
			fout << "{ ";
			for (; itr != it->first.end(); itr++)	fout << "I" << *itr << " ";
			fout << "}";
			fout << " -> sup_cnt=" << it->second;
			fout << endl;
		}
	}
	Gen_Ass_Rules(i - 1);
	fin.close();
	fout.close();
	return 0;
}
