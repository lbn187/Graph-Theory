#ifndef CHU_LIU_HPP
#define CHU_LIU_HPP
#include "DSU.hpp"
template<typename T,const int N>struct Chu_Liu{
	int n,m,s,pa[N];
	vector<tuple<int,int,T>>edge;
	struct Node{Node *l,*r;int x,y;T v,lz;};//带lazy标记左偏树
	private:
		DSU W,S;Node *H[N],*pe[N];
		vector<PII>G[N];
		int dist[N];
		void add(Node *node,T z){if(node!=NULL)node->v+=z,node->lz+=z;}
		void down(Node *node){//传标记
			add(node->l,node->lz);
			add(node->r,node->lz);
			node->lz=0;
		}
		Node* merge(Node* LT,Node* RT){
			if(LT==NULL)return RT;
			if(RT==NULL)return LT;
			if(RT->v<LT->v)swap(LT,RT);
			down(LT);LT->r=merge(LT->r,RT);
			swap(LT->l,LT->r);
			return LT;
		}
		Node *pop(Node*node){
			down(node);
			return merge(node->l,node->r);
		}
	public:
		Chu_Liu()=default;
		Chu_Liu(int _n):n(_n){}
		Chu_Liu(int _n,int _s):n(_n),s(_s){}
		void ins(int x,int y,T z){edge.PB(MT(x,y,z));m++;}
		T solve(int _s=0,int _n=0){//如果不必输出方案，不用处理G[],pe[]和rid
			if(_s)s=_s;if(_n)n=_n;
			fr(i,n)G[i].clear(),H[i]=NULL;
			W.init(n);S.init(n);
			T ans=0;int rid=0;
			for(auto o:edge)H[get<1>(o)]=merge(new Node{NULL,NULL,get<0>(o),get<1>(o),get<2>(o),0},H[get<1>(o)]);
			fr(i,n)if(i!=s)
				for(;;){
					auto in=H[S[i]];
					if(in==NULL)return -1;//No Solution
					H[S[i]]=pop(H[S[i]]);
					if(S[in->x]==S[i])continue;
					ans+=in->v;
					pe[S[i]]=in;
					//if (in->x==s) , root=in->y
					add(H[S[i]],-in->v);//注意判NULL和+lz
					G[in->x].PB({in->y,++rid});
					if(W[in->x]!=W[i]){W[in->x]=W[i];break;}
					for(int j=S[in->x];j!=S[i];j=S[pe[j]->x]){
						G[pe[j]->x].PB({pe[j]->y,rid});
						H[j]=merge(H[S[i]],H[j]);//merge注意标记下传
						S[i]=S[j];
					}
				}
			++rid;
			fr(i,n)if(i!=s&&S[i]==i){
				G[pe[i]->x].PB({pe[i]->y,rid});
				return ans;
			}
		}
		void makeSol(){//用堆优化Prim构造方案，pa[i]表示点i在方案中的父亲
			fr(i,n)dist[i]=n+1;
			pa[s]=0;
			for(multiset<PII>h={{0,s}};!h.empty();){
				int x=h.begin()->Y;
				h.erase(h.begin());dist[x]=0;
				for(auto o:G[x])if(o.Y<dist[o.X]){
					h.erase({dist[o.X],o.X});
					h.insert({dist[o.X]=o.Y,o.X});
					pa[o.X]=x;
				}
			}
		}
};
#endif
