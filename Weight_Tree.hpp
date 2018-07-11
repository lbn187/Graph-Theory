#ifndef WEIGHT_TREE_HPP
#define WEIGHT_TREE_HPP
#include "start.hpp"
template<typename T> struct Weight_Tree{
	static const int N=111111;
	int n,rt;
	vector<pair<int,T> >V[N];
	int sz[N],mv[N];
	int st[N],ed[N],to[N];
	int d[N];
	private:	
		int id=0,nv,u,w;
	public:		
		Weight_Tree(int _n=0,int _rt=0):n(_n),rt(_rt){}
		Weight_Tree(int *fa,int _n,int _rt):n(_n),rt(_rt){fr(i,n)if(fa[i])ins(fa[i],i);}
		Weight_Tree(const Weight_Tree&G):n(G.n),rt(G.rt){fr(i,n)V[i]=G.V[i];}
		Weight_Tree &operator=(const Weight_Tree&G){
			if(this==&G)return *this;
			fr(i,n)V[i].clear();
			n=G.n;rt=G.rt;
			fr(i,n)V[i]=G.V[i];
		}
		~Weight_Tree(){clear();}
		void clear(){fr(i,n)V[i].clear();}
		void ins(int x,int y,T z){V[x].PB(MP(y,z));V[y].PB(MP(x,z));}
		void dfssz(int x,int fa){
			sz[x]=1;mv[x]=0;
			for(pair<int,T> o:V[x])if(o.X!=fa)
				dfssz(o.X,x),sz[x]+=sz[o.X],mv[x]=max(mv[x],mv[o.X]);
			mv[x]=max(mv[x],n-sz[x]);
		}
		void dfsid(int x,int fa){
			st[x]=++id;to[id]=x;
			for(pair<int,T> o:V[x])if(o.X!=fa)dfsid(o.X,x);
			ed[x]=id;
		}
		void dfsdeep(int x,int fa,T dis){
			d[x]=dis;
			for(pair<int,T> o:V[x])if(o.X!=fa)dfsdeep(o.X,x,dis+o.Y); 
		}
		int center(){
			dfssz(1,0);
			fr(i,n)if(mv[i]<=n/2)return i;
		}
};
#endif
