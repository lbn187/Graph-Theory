#ifndef STAINER_TREE_HPP
#define STAINER_TREE_HPP
#include"start.hpp"
namespace Stainer_Tree{
	using Val=LL;//可以修改类型
	const int N=1111;
	const int M=1025;//1<<k
	const Val INF=1e18;
	vector<pair<int,Val>>V[N];
	Val f[N][M],an=INF;bool v[N];
	void ins(int x,int y,Val z){V[x].PB(MP(y,z));}
	Val solve(int n,vector<tuple<int,int,Val>>Edge,VI Set){
		int k=SZ(Set),sub,x,y;
		fr(i,n)f0(j,1<<k)f[i][j]=INF;
		for(auto o:Edge){
			int x=get<0>(o),y=get<1>(o);
			Val z=get<2>(o);
			ins(x,y,z);ins(y,x,z);
		}
		f0(i,k)f[Set[i]][1<<i]=0;
		fr(s,(1<<k)-1){
			fr(i,n)for(sub=s&(s-1);sub;sub=s&(sub-1))
				f[i][s]=min(f[i][s],f[i][sub]+f[i][s-sub]);
			QI Q;
			fr(i,n)if(f[i][s]<INF)Q.push(i),v[i]=1;
			for(;!Q.empty();){
				v[x=Q.front()]=0,Q.pop();
				for(auto o:V[x])if(f[x][s]+o.Y<f[y=o.X][s])
					if(f[y][s]=f[x][s]+o.Y,!v[y])Q.push(y),v[y]=1;
			}
		}
		fr(i,n)an=min(an,f[i][(1<<k)-1]);
		return an>=INF?-1:an;
	}
};
#endif
