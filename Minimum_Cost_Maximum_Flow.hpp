#ifndef MINIMUM_COST_MAXIMUM_FLOW_HPP
#define MINIMUM_COST_MAXIMUM_FLOW_HPP
#include "start.hpp"
template<typename T1,typename T2>struct CostEdge{int x,y,nxt;T1 cap;T2 co;};
template<typename T1,typename T2>struct Minimum_Cost_Maximum_Flow{
	static const int N=1111;
	static const T1 INF1=2147483647;
	static const T2 INF2=1e18;
	int n,m,s,t,fir[N];
	vector<CostEdge<T1,T2> >e;
	private:
		T1 fl;T2 an;
		T2 d[N];
		bool v[N];
		int pre[N],fa[N];
		bool spfa(){
			int x,y;
			fr(i,n)d[i]=INF2,v[i]=0;
			queue<int>Q;
			d[s]=1;Q.push(s);v[s]=1;
			for(;!Q.empty();){
				x=Q.front();Q.pop();v[x]=0;
				for(int i=fir[x];i;i=e[i].nxt)
					if(d[x]+e[i].co<d[y=e[i].y]&&e[i].cap>0){
						d[y]=d[fa[y]=x]+e[pre[y]=i].co;
						if(!v[y])v[y]=1,Q.push(y);
					}
			}
			return d[t]<inf;
		}
		void end(){
			T1 p=INF1;int i;
			for(i=t;i!=s;i=fa[i])p=min(p,e[pre[i]].cap);
			for(fl+=p,i=t;i!=s;i=fa[i])e[pre[i]].cap-=p,e[pre[i]^1].cap+=p,an+=p*e[pre[i]].co;
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
};
#endif
