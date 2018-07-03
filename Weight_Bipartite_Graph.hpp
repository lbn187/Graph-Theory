//function: a weight bipartitle graph struct to solve maximum value complete match problem problem
//ln - The number of vertex in the left part
//rn - The number of vertex in the right part
//n - max(ln,rn)
//lkx[i] - The vertex match the left part vertex i
//lky[i] - The vertex match the right part vertex i
//maxv - The maximum value of edge
//lx[i] - The top mark of left part vertex i
//ly[i] - The top mark of right part vertex i
//w[i][j] - The maximum value of edge <i,j>
//Weight_Bipartite_Graph(ln,rn,maxv) - Make a Weight_Bipartite_Graph struct with ln vertexs in the left part and rn vertexs in the right part, and the maximum weight of edge is less than maxv
//Weight_Bipartite_Graph(ln,rn,**w,maxv) - Make a Weight_Bipartite_Graph struct with ln vertexs in the left part and rn vertexs in the right part, and the maximum weight of edge is less than maxv which based on matrix w
//Weight_Bipartite_Graph(ln,rn,Weight_Graph G,maxv) - Make a Weight_Bipartite_Graph struct with ln vertexs in the left part and rn vertexs in the right part, and the maximum weight of edge is less than maxv which based on Graph G
//init() - make all the edge to 0
//ins(x,y) - Add an edge from left part vertex x to right part vertex y
//KM() - Use KM algorithm to solve maximum value complete match problem problem
//print() - Print the scheme
#include "Weight_Graph.hpp"
template<typename T> struct Weight_Bipartite_Graph{
	static const int N=555;
	static const T inf=1e9;
	int n,ln,rn,lkx[N],lky[N];
	T maxv,lx[N],ly[N],w[N][N];
	private:
		T slk[N];
		bool vy[N];
		int pre[N];
	public:
		Weight_Bipartite_Graph(int _ln,int _rn,T _maxv=inf):ln(_ln),rn(_rn),maxv(_maxv){
			n=max(ln,rn);
			fr(i,n)fr(j,n)w[i][j]=-(maxv+1)*n;
		}
		Weight_Bipartite_Graph(int _ln,int _rn,T **_w,T _maxv=inf):ln(_ln),rn(_rn),maxv(_maxv){
			n=max(ln,rn);
			fr(i,n)fr(j,n)w[i][j]=_w[i][j];
		}
		Weight_Bipartite_Graph(int _ln,int _rn,Weight_Graph<T> G,T _maxv=inf):ln(_ln),rn(_rn),maxv(_maxv){
			n=max(ln,rn);
			fr(i,n)fr(j,n)w[i][j]=-(maxv+1)*n;
			fr(x,ln)for(pair<int,T> o:G.V[x])w[x][o.X]=max(w[x][o.X],o.Y);
		}
		void init(){
			fr(i,n)fr(j,n)w[i][j]=0;
		}
		void ins(int x,int y,T z){w[x][y]=max(w[x][y],z);}
		T KM(){
			T INF=(maxv+1)*n*3;int py,x,p;T d,an=0;
			fr(i,n)lx[i]=ly[i]=0;
			fr(i,ln)lkx[i]=0;fr(i,rn)lky[i]=0;
			fr(i,n)fr(j,n)lx[i]=max(lx[i],w[i][j]);
			fr(i,n){
				fr(j,n)slk[j]=INF,vy[j]=0;
				for(lky[py=0]=i;lky[py];py=p){
					vy[py]=1;d=inf;x=lky[py];
					fr(y,n)if(!vy[y]){
						if(lx[x]+ly[y]-w[x][y]<slk[y])slk[y]=lx[x]+ly[y]-w[x][y],pre[y]=py;
						if(slk[y]<d)d=slk[y],p=y;
					}
					for(int y=0;y<=n;y++)if(vy[y])lx[lky[y]]-=d,ly[y]+=d;else slk[y]-=d;
				}
				for(;py;py=pre[py])lky[py]=lky[pre[py]];
			}
			fr(i,rn)if(lky[i])lkx[lky[i]]=i;
			fr(i,n)an+=lx[i]+ly[i];
			return an;
		}
		void print(){
			fr(i,rn)if(lky[i])printf("%d - %d\n",lky[i],i);
		}
};
