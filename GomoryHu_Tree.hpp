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
			VI W=TI.Minimal_cut_set(s),SV,TV;
			tree.PB(MT(s,t,fl));
			for(auto x:V)vs[x]=0;
			for(auto x:W)vs[x]=1;
			for(auto x:V)if(vs[x])SV.PB(x);else TV.PB(x);
			for(auto x:SV)for(auto y:TV)Min(an[x][y],fl),Min(an[y][x],fl);
			build(SV),build(TV);
		}
	public:
		GomoryHu_Tree()=default;
		GomoryHu_Tree(int n):Maximum_Flow<T,N,INF>(n){clear();}
		~GomoryHu_Tree(){clear();}
		void init(int n){
			Maximum_Flow<T,N,INF>::init(n);
			clear();
		}
		void clear(){
			fr(i,n)fr(j,n)an[i][j]=INF;
			tree.clear();
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
