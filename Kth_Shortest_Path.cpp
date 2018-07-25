const LL INF=1e18;
int F[N],FF[N];
namespace Left_Tree{
	struct P{int l,r,h,x,y;__int128 v;}Tr[N*40];
	int RT[N],num;
	int New(P o){Tr[++num]=o;return num;}
	void start(){num=0;Tr[0].l=Tr[0].r=Tr[0].h=0;Tr[0].v=1e26;}
	int mg(int x,int y){
		if(!x)return y;
		if(Tr[x].v>Tr[y].v)swap(x,y);
		int o=New(Tr[x]);
		Tr[o].r=mg(Tr[o].r,y);
		if(Tr[Tr[o].l].h<Tr[Tr[o].r].h)swap(Tr[o].l,Tr[o].r);
		Tr[o].h=Tr[Tr[o].r].h+1;
		return o;	
	}
	void add(int&k,LL v,int x,int y){
		int o=New(Tr[0]);
		Tr[o].v=v;Tr[o].x=x;Tr[o].y=y;
		k=mg(k,o);	
	}
}
using namespace Left_Tree;
struct Dijkstra{
	int tot,fir[N],la[M],ne[M],va[M];bool v[N];
	LL d[N];priority_queue<pair<LL,int> >Q;
	Dijkstra(){tot=0;CL(fir);}
	void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
	void work(int S,int n){
		int i,x,y;
		for(int i=1;i<=n;i++)d[i]=INF,v[i]=0;
		Q.push(MP(d[S]=0,S));
		for(;!Q.empty();){
			x=Q.top().Y;Q.pop();
			if(v[x])continue;
			v[x]=1;
			for(int i=fir[x];i;i=ne[i])
				if(d[x]+va[i]<d[y=la[i]]){
					d[y]=d[x]+va[i],F[y]=x,FF[y]=i;
					Q.push(MP(-d[y],y));
				}
		}
	}
}A;
struct Kshort{
	int tot,n,m,S,T,k,fir[N],la[M],ne[M],va[M],q[N];bool v[N];
	struct P{
		int x,y;__int128 z;P(){}
		P(int x,int y,__int128 z):x(x),y(y),z(z){}
		bool operator<(P a)const{return a.z<z;}
	};
	priority_queue<P>Q;
	Kshort(){tot=0;CL(fir);}
	void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
	void init(){
		int i,x,y,z;start();
		scanf("%d%d%d%d%d",&n,&m,&S,&T,&k);
		for(i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),A.ins(y,x,z),ins(x,y,z);
		if(S==T)k++;
		A.work(T,n);
	}
	__int128 work(){
		int i,x,h=0,t=0;
		q[++t]=T;v[T]=1;
		for(;h^t;){
			x=q[++h];
			for(int i=A.fir[x];i;i=A.ne[i])if(F[A.la[i]]==x&&!v[A.la[i]])v[A.la[i]]=1,q[++t]=A.la[i];
		}
		for(i=1;i<=t;i++){
			x=q[i];
			if(F[x])RT[x]=RT[F[x]];
			for(int i=fir[x],y;i;i=ne[i])
				if(y=la[i],A.d[y]!=INF&&FF[x]!=i)add(RT[x],A.d[y]-A.d[x]+va[i],x,y);
		}
		if(!--k)return A.d[S]==INF?-1:A.d[S];
		P u,w;
		if(RT[S])Q.push(P(S,RT[S],A.d[S]+Tr[RT[S]].v));
		for(;k--;){
			if(Q.empty())return -1;
			u=Q.top();Q.pop();
			if(x=mg(Tr[u.y].l,Tr[u.y].r))Q.push(P(u.x,x,Tr[x].v-Tr[u.y].v+u.z));
			if(RT[x=Tr[u.y].y])Q.push(P(x,RT[x],u.z+Tr[RT[x]].v));
		}
		return u.z;
	}
}G;
