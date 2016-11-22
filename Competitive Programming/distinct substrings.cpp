/*
	Name: Distinct substrings in a string.
	Copyright: 
	Author: Shobhit Saxena
	Date: 14/12/13 15:29
	Description: Distinct substring are the number of nodes in a suffix trie.
					This can be computed using suffix arrays.
					By finding the lcp arrays.
*/

#include<bits/stdc++.h>
using namespace std;


//-----------------------------SUFFIX ARRAYS------------------------------------
class suffix_array
{
	private:	
		string _s;
		vector<vector<int> > _P; // this can be made of O(n) size but 
		vector<int> _sa;
		void _build_suffix_array()
		{
			//----------Determining the size of Matrix------------------------
			size_t lgsize;
			{	
				size_t _size;
				for(lgsize=0,_size=(int)(_s.size())-1;_size;_size>>=1,lgsize++);
			}
	
			 _P.resize(lgsize+1,vector<int>(_s.size()));
	
			//------------ Sorting initial character in O(nlog(sigma))-----------------
			map<char,int> char_map;
			for(int i=0;i<_s.size();i++)
				char_map[_s[i]]=0;
	
			int k=0;
			for(map<char,int>::iterator i=char_map.begin();i!=char_map.end();i++,k++)
				i->second=k;
	
			for(int i=0;i<_s.size();i++)
				_P[0][i]=char_map[_s[i]];
			//-------------------------------------------------------------------------
	
	
			typedef pair<pair<int,int>,int > entry;
			for(int step=1;(1<<(step-1))<_s.size();step++)
			{
				vector<entry> L(_s.size());
				for(int i=0;i<_s.size();i++)
				{
					L[i].first.first=_P[step-1][i];
					if((i+(1<<(step-1)))<_s.size())
						L[i].first.second=_P[step-1][i+(1<<(step-1))];
					else
						L[i].first.second=-1;
					L[i].second=i;
				}		
				sort(L.begin(),L.end());
		
				int k=0;
				_P[step][L[0].second]=0;
				for(int i=1,k=0;i<_s.size();i++)
				{
					if(L[i].first!=L[i-1].first)
						k++;
					_P[step][L[i].second]=k;	
				}
			}
			#ifdef SUFFIX_ARRAY_DEBUG
			for(int i=0;i<_P.size();i++)
			{
				for(int j=0;j<_P[i].size();j++)
					cout<<_P[i][j]<<" ";
				cout<<endl;
			}
			#endif
			_sa.resize(_s.size());
			for(int i=0;i<_s.size();i++)
				_sa[_P[_P.size()-1][i]]=i;
		}

	public:
		suffix_array()
		{
		}
		suffix_array(const string &S)
		{
			assign(S);
		}
		
		void assign(const string &S)
		{
			_P.clear();
			_s=S;
			_build_suffix_array();
		}
		
		int operator [](size_t pos) const
		{
			return _sa[pos];
		}
		
		int lcp(size_t a,size_t b) const
		{
			int ans=0;
			for(int k=_P.size()-1;k>=0;k--)
				if(_P[k][a]==_P[k][b])
				{
					ans+=(1<<k);
					a+=(1<<k);
					b+=(1<<k);
				}
			return ans;
		}
		
		void clear()
		{
			_P.clear();
			_s.clear();
		}
		~suffix_array()
		{
			clear();
		}
		size_t size() const
		{
			if(_P.size())
				return _P[0].size();
			else
				return 0;
		}
		
};
//------------------------ manbers algorithm------------------------------------

int main()
{
	
		string a;
		cin>>a;
		suffix_array sa(a);
		long long distinct=sa.size()-sa[0];
		for(int i=1;i<sa.size();i++)
		{
			distinct+=(sa.size()-sa[i])-sa.lcp(sa[i-1],sa[i]);
		}
		cout<<distinct<<endl;
}
