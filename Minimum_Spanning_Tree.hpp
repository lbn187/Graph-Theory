//funtion - Struct to solve the minimum spanning tree problem
//n - The number of vertex
//vector<P<T> >p - The vector to store edges
//T Prim() - Use Prim algorithm to solve the problem
//pair<int,T> Kruskal() - Use Kruskal algorithm to solve the problem
//vector<P<T> > scheme() - Return the minimum spanning tree scheme
#ifndef MINIMUM_SPANNING_TREE_HPP
#define MINIMUM_SPANNING_TREE_HPP
#include "Weight_Tree.hpp"
template<typename T>struct P{
	int x,y;T z;
	bool operator<(P a)const{return z<a.z;}
};
template<typename T>struct Minimum_Spanning_Tree{
	static const int N=222222;
	int n;
	vector<P<T> >p;
	private: 
		int F[N];
		vector<P<T> >tr;
		vector<pair<int,T> >V[N];
		bool v[N];
		int gf(int x){return F[x]==x?x:F[x]=gf(F[x]);}
	public:
		Minimum_Spanning_Tree(int _n):n(_n){}
		Minimum_Spanning_Tree(int _n,vector<P<T> > w):n(_n){p=w;}
		void ins(int x,int y,T z){p.PB({x,y,z});}
		T Prim(int s=1){
			PQ<pair<T,int> >Q;int x;T z,an=0;CL(v);v[s]=1;
			for(P<T> o:p)V[o.x].PB(MP(o.y,o.z)),V[o.y].PB(MP(o.x,o.z));
			for(pair<int,T> o:V[s])Q.push(MP(-o.Y,o.X));
			for(;!Q.empty();){
				x=Q.top().Y;z=-Q.top().X;Q.pop();
				if(!v[x]){
					v[x]=1;an+=z;
					for(pair<int,T> o:V[x])Q.push(MP(-o.Y,o.X));
				}
			}
			return an;
		}
		pair<int,T> Kruskal(){
			T an=0;int cnt=0;
			sort(p.begin(),p.end());
			fr(i,n)F[i]=i;
			for(P<T> o:p){
				int x=gf(o.x),y=gf(o.y);
				if(x!=y)F[x]=y,cnt++,an+=o.z,tr.PB(o);
			}
			return MP(cnt,an);
		}
		vector<P<T> > scheme(){return tr;}
};
#endif
