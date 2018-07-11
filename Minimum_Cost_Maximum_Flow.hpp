//funcion - The struct to solve minimum cost maximum flow problem
//Edge<T>{x,y,nxt,cap,co} - The template to store edges, which from x to y with flow z and cost co, which next edge is nxt
//n - The number of vertex
//m - The number of edges
//s - The start vertex
//t - The terminate vertex
//Minimum_Cost_Maximum_Flow(n,s=0,t=0) - Initial opeartion
//ins(x,y,cap,co) - Add an edge from x to y with flow limit cap and cost co
//pair<T1,T2> cal(int _s,int _t,int _n=0) - Use spfa force algorithm to solve the problem, and return the flow and cost
//pair<T1,T2> dinic_cal(int _s,int _t,int _n=0) - Use spfa algorithm and dinic to solve the problem
//pair<T1,T2> ZKW(int _s,int_t,int _n=0) - Use ZKW algorithm to solve the problem
#ifndef MINIMUM_COST_MAXIMUM_FLOW_HPP
#define MINIMUM_COST_MAXIMUM_FLOW_HPP
#include "start.hpp"
template<typename T1,typename T2>struct CostEdge{int x,y,nxt;T1 cap;T2 co;};
template<typename T1,typename T2>struct Minimum_Cost_Maximum_Flow{
	static const int N=555;
	static const T1 INF1=2147483647;
	static const T2 INF2=1e18;
	int n,m,s,t,fir[N];
	vector<CostEdge<T1,T2> >e;
	private:
		T1 fl;T2 an,d[N];
		bool v[N];
		int pre[N],fa[N],cur[N];
		bool spfa(){
			int x,y,i;QI Q;
			fr(i,n)d[i]=INF2,v[i]=0;
			d[s]=0;Q.push(s);v[s]=1;
			for(;!Q.empty();)
				for(i=fir[x=Q.front()],Q.pop(),v[x]=0;i;i=e[i].nxt)
					if(d[x]+e[i].co<d[y=e[i].y]&&e[i].cap>0)
						if(d[y]=d[fa[y]=x]+e[pre[y]=i].co,!v[y])v[y]=1,Q.push(y);
			return d[t]<INF2;
		}
		void end(){
			T1 p=INF1;int i;
			for(i=t;i!=s;i=fa[i])p=min(p,e[pre[i]].cap);
			for(fl+=p,i=t;i!=s;i=fa[i])e[pre[i]].cap-=p,e[pre[i]^1].cap+=p,an+=p*e[pre[i]].co;
		}
		bool _spfa(){
			int x,y,i;QI Q;
			fr(i,n)d[i]=INF2,v[i]=0;
			for(d[t]=0,Q.push(t),v[t]=1;!Q.empty();)
				for(i=fir[x=Q.front()],Q.pop(),v[x]=0;i;i=e[i].nxt)
					if(d[x]+e[i^1].co<d[y=e[i].y]&&e[i^1].cap>0)
						if(d[y]=d[x]+e[i^1].co,!v[y])v[y]=1,Q.push(y);
			return d[s]<INF2;
		}
		T1 dfs(int x,T1 p){
			if(x==t)return fl+=p,an+=d[s]*p,p;
			if(v[x])return 0;
			T1 tmp=0;v[x]=1;
			for(int &i=cur[x],y;i;i=e[i].nxt)
				if(e[i].cap>0&&d[x]==e[i].co+d[y=e[i].y]){
					T1 w=dfs(y,min(p-tmp,e[i].cap));
					e[i].cap-=w;e[i^1].cap+=w;tmp+=w;
					if(tmp==p)break;
				}
			v[x]=0;return tmp;
		}
		T1 aug(int x,T1 p){
			if(x==t)return fl+=p,an+=d[s]*p,p;
			v[x]=1;T1 tmp=0,w;
			for(int &i=cur[x],y;i;i=e[i].nxt){
				if(!v[y=e[i].y]&&e[i].cap>0&&d[x]==d[y]+e[i].co){
					w=aug(y,min(e[i].cap,p-tmp));
					e[i].cap-=w;e[i^1].cap+=w;tmp+=w;
					if(tmp==p)return tmp;
				}
			}
			return tmp;
		}
		bool mdflabel(){
			T2 z=INF2;int x,y,i;
			for(i=2;i<SZ(e);i++)if(v[x=e[i].x]&&!v[y=e[i].y]&&e[i].cap>0)z=min(z,d[y]-d[x]+e[i].co);
			if(z==INF2)return 0;
			fr(i,n)if(v[i])d[i]+=z;
			return 1;
		}
	public:
		Minimum_Cost_Maximum_Flow(int _n,int _s=0,int _t=0):n(_n),m(0),s(_s),t(_t){e.PB({0,0,0,0,0});e.PB({0,0,0,0,0});}
		void ins(int x,int y,T1 cap,T2 co){
			int id=SZ(e);
			e.PB({x,y,fir[x],cap,co});fir[x]=id;
			e.PB({y,x,fir[y],0,-co});fir[y]=id+1;
			m++;
		}
		pair<T1,T2> cal(int _s,int _t,int _n=0){
			s=_s;t=_t;if(_n)n=_n;
			for(an=0,fl=0;spfa();end());
			return MP(fl,an);
		}
		pair<T1,T2> dinic_cal(int _s,int _t,int _n=0){
			s=_s;t=_t;if(_n)n=_n;
			for(;_spfa();)for(CP(cur,fir);dfs(s,INF1););
			return MP(fl,an);
		}
		pair<T1,T2> ZKW(int _s,int _t,int _n=0){
			s=_s;t=_t;if(_n)n=_n;
			an=0;fl=0;CL(d);
			do do CL(v),CP(cur,fir);while(aug(s,INF1)>0);while(mdflabel());
			return MP(fl,an);
		}
};
#endif
