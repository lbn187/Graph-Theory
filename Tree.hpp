#ifndef TREE_HPP
#define TREE_HPP
#include "start.hpp"
struct Tree{
	static const int N=111111;
	int n,rt;
	VI V[N];
	int sz[N],mv[N];
	int st[N],ed[N],to[N];
	int d[N];
	private:	
		int id=0,nv,u,w;
		void dfsdis(int x,int fa,int dis){
			if(dis>nv)nv=dis,u=x;
			for(int y:V[x])if(y!=fa)dfsdis(y,x,dis+1);
		}
	public:		
		Tree(int _n=0,int _rt=0):n(_n),rt(_rt){fr(i,n)V[i].clear();}
		Tree(int *fa,int _n,int _rt):n(_n),rt(_rt){fr(i,n)if(fa[i])ins(fa[i],i);}
		Tree(const Tree&G):n(G.n),rt(G.rt){fr(i,n)V[i]=G.V[i];}
		Tree &operator=(const Tree&G){
			if(this==&G)return *this;
			fr(i,n)V[i].clear();
			n=G.n;rt=G.rt;
			fr(i,n)V[i]=G.V[i];
		}
		~Tree(){clear();}
		void clear(){fr(i,n)V[i].clear();}
		void ins(int x,int y){V[x].PB(y);V[y].PB(x);}
		void dfssz(int x,int fa){
			sz[x]=1;mv[x]=0;
			for(int y:V[x])if(y!=fa)
				dfssz(y,x),sz[x]+=sz[y],mv[x]=max(mv[x],mv[y]);
			mv[x]=max(mv[x],n-sz[x]);
		}
		void dfsid(int x,int fa){
			st[x]=++id;to[id]=x;
			for(int y:V[x])if(y!=fa)dfsid(y,x);
			ed[x]=id;
		}
		void dfsdeep(int x,int fa,int dis){
			d[x]=dis;
			for(int y:V[x])if(y!=fa)dfsdeep(y,x,dis+1); 
		}
		pair<int,PII> diameter(){
			u=1;nv=0;
			dfsdis(1,0,0);
			w=u;nv=0;dfsdis(w,0,0);
			return MP(nv,MP(w,u));
		}
		int center(){
			dfssz(1,0);
			fr(i,n)if(mv[i]<=n/2)return i;
		}
};
#endif
