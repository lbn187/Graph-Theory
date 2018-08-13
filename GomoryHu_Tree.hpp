#ifndef GOMORYHU_TREE_HPP
#define GOMORYHU_TREE_HPP
template<typename T,const int N,T INF> struct GomoryHu_Tree:public Maximum_Flow<T,N,INF>{
	using Maximum_Flow<T,N,INF>::n;
	vector<tuple<int,int,T>>tree;
	T an[N][N];
	private:
		bool vs[N];
		void build(VI V){
			int s,t;
			if(SZ(V)<=1)return;
			TI.reset();
			T fl=TI.ISAP(s=V[0],t=V.back());
			VI SV=TI.Minimum_cut_set(s),TV;
			tree.PB(MT(s,t,fl));
			for(auto x:V)vs[x]=0;
			for(auto x:SV)vs[x]=1;
			for(auto x:V)if(!vs[x])TV.PB(x);
			for(auto x:SV)for(auto y:TV)Min(an[x][y],fl);
			build(SV);build(TV);
		}
	public:
		GomoryHu_Tree()=default;
		GomoryHu_Tree(int n):Maximum_Flow<T,N,INF>(n){
			fr(i,n)fr(j,n)an[i][j]=INF;
		}
		void init(int n){
			Maximum_Flow<T,N,INF>::init(n);
			fr(i,n)fr(j,n)an[i][j]=INF;
		}
		void ins(int x,int y,T z){
			Maximum_Flow<T,N,INF>::ins(x,y,z);
			Maximum_Flow<T,N,INF>::ins(y,x,z);
		};
		void work(){
			VI V;
			fr(i,n)V.PB(i);
			build(V);
		}
};
#endif
