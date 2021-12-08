#include<bits/stdc++.h>
using namespace std;
ofstream outputfile;
int min_support;
map<string,vector<string> > data;
map<pair<string,string>,double >output;
bool compare(vector<string>a,vector<string>b,int len)
{
	if(len==2&&a!=b)
	return true;
	else
	{
		if(a.size()!=b.size())
		return false;
		else
		{
			int cnt=0;
			for(int i=0;i<a.size();i++)
			{
				if(a[i]==b[i])
				cnt++;
				else
				break;
			}
			if(cnt==len-2)
			return true;
			else
			return false;
		}
	}
}
void printC(map<vector<string> , int > m)
{
	
	for(auto x:m)
	{
		for(int i=0;i<x.first.size();i++)
		{
			outputfile<<x.first[i]<<" ";
		}
		outputfile<<x.second<<endl;
	}
}
int eval(vector<string>ans)
{
	int count=0;
	for(auto x:data)
	{
		bool flag=true;
		for(int i=0;i<ans.size();i++)
		{
			if(find(x.second.begin(),x.second.end(),ans[i])!=x.second.end())
			continue;
			else
			{
				flag=false;
				break;
			}
		}
		if(flag==true)
		count++;
	}
	return count;
}

bool check(map<vector<string> , int > &m,int len)
{
	
	map<vector<string>,int> apri;
	map<vector<string>,int> aprinew;
	for(auto x:m)
	{
		if(x.second>=min_support)
		apri[x.first]=x.second;
	}
	if(apri.size()==0)
	return false;
	map<vector<string>,int> :: iterator it1;
	map<vector<string>,int> :: iterator it2;
	for(it1=apri.begin();it1!=apri.end();++it1)
	{
		for(it2=it1;it2!=apri.end();++it2)
		{
			if(compare(it1->first,it2->first,len)==true)
			{
				vector<string>res;
				string asso1="{";
				for(int i=0;i<it1->first.size();i++)
				{
					if(asso1=="{")
					asso1+=it1->first[i];
					else
					asso1+=","+it1->first[i];
					res.push_back(it1->first[i]);
				}
				asso1+="}";
				string asso2="{";
				asso2+=it2->first[it1->first.size()-1];
				asso2+="}";
				res.push_back(it2->first[it1->first.size()-1]);
				int cnt=eval(res);
				if(cnt>=min_support)
				{
					output[{asso1,asso2}]=(double(cnt)*100)/m[it1->first];
					output[{asso2,asso1}]=(double(cnt)*100)/m[it2->first];	
				}
				aprinew[res]=cnt;
			}
		}
	}
	m.clear();
	m=aprinew;
	return true;
}
void random_generation()
{
	ofstream outputfile;
	
	outputfile.open("random_output.txt");
	
	srand((unsigned) time(0));
	
	int t=1+rand()%(50); 
	
	int l=1;
	int u=5;
	
	
	for(int i=1;i<=t;i++)
	{
		outputfile<<"T"<<i<<" ";
		
		int v=1+(rand()%(10));
		
		for(int j=0;j<v;j++)
		{
			
        int num = (rand() % (u-l+1)) + l;  
           outputfile<<"l"<<num<<" ";
	
		
	    }    
		outputfile<<endl;
    }
	
	
}

int main()
{
	random_generation();
	ifstream inputfile;
	ofstream outputfile;
	outputfile.open("Output_2_3.txt");
	inputfile.open("Random_Output.txt");
	string s;
	string temp="";
	map<vector<string>,int>m;
	while(inputfile>>s)
	{
		if(s.size()>=2&&s[0]=='T'&&s[1]>='0'&&s[1]<='9')
		temp=s;
		else
		{
			data[temp].push_back(s);
			m[{s}]++;
		}
	}
	int n=m.size();
	int A[]={30,50,70};
	for(int i=0;i<3;i++)
	{
		min_support=floor((A[i]*data.size())/100);
		outputfile<<"for mimimum support value of "<<A[i]<<" % \nthe cutoff value is : "<<min_support<<endl;
		map<vector<string>,int>m1;
		m1=m;
		for(int len=2;len<=n;len++)
		{
			bool b=check(m1,len);
			if(b==false)
			break;
		}
		outputfile<<"\nassociations : "<<endl;
		for(auto x:output)
		{
			outputfile<<x.first.first<<" -> "<<x.first.second<<" confindence : "<<x.second<<endl;
		}
		outputfile<<endl;
		output.clear();
	}
}