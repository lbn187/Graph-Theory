#define f0(i,n) for(int i=0;i<n;i++)//redefine
		template<typename T>struct Mat{
			static const LL MOD=1000000007;
			bool fi=(typeid(T)==typeid(int)||typeid(T)==typeid(LL));
			int n,m;
			VEC<VEC<T>>v;
			Mat()=default;
			Mat(int _n):n(_n),m(_n){
				VEC<T>tmp;
				fr(i,n)tmp.PB(0);
				fr(i,n)v.PB(tmp);
				f0(i,n)v[i][i]=1;
			}
			Mat(int _n,int _m):n(_n),m(_m){
				VEC<T>tmp;
				fr(i,m)tmp.PB(0);
				fr(i,n)v.PB(tmp);
			}
			Mat(VEC<VEC<T>>tmp){
				v=tmp;n=SZ(v);
				if(n)m=SZ(v[0]);
			}
			Mat(const Mat&a):n(a.n),m(a.m),v(a.v){}
			Mat(Mat &&a)noexcept:n(a.n),m(a.m){v.swap(a.v);}
			Mat &operator=(const Mat&a){
				if(this==&a)return TI;
				n=a.n;m=a.m;v=a.v;
				return TI;
			}
			Mat &operator=(Mat &&a)noexcept{
				n=a.n;m=a.m;
				v.swap(a.v);
				return TI;
			}
			~Mat(){clear();}
			void init(int _n){
				clear();
				n=m=_n;
				VEC<T>tmp;
				fr(i,n)tmp.PB(0);
				fr(i,n)v.PB(tmp);
				f0(i,n)v[i][i]=1;
			}
			void init(int _n,int _m){
				clear();
				n=_n;m=_m;
				VEC<T>tmp;
				fr(i,m)tmp.PB(0);
				fr(i,n)v.PB(tmp);
			}
			void init(VEC<VEC<T>>tmp){
				clear();
				v=tmp;n=SZ(v);
				if(n)m=SZ(v[0]);
			}
			void clear(){n=m=0;CR(v);}
			VEC<T>& operator[](int id){
				if(id>=n||id<0)throw "取的行数超出范围";
				return v[id];
			}
			const VEC<T>& operator[](int id)const{
				if(id>=n||id<0)throw "取的行数超出范围";
				return v[id];
			}
			Mat&operator+=(const Mat&a){
				if(n!=a.n||m!=a.m)throw "行列不匹配，不能相加";
				f0(i,n)f0(j,m){
					v[i][j]+=a[i][j];
					if(fi)v[i][j]%=MOD;
				}
				return TI;
			}
			Mat&operator-=(const Mat&a){
				if(n!=a.n||m!=a.m)throw "行列不匹配，不能相减";
				f0(i,n)f0(j,m){
					v[i][j]-=a[i][j];
					if(fi)v[i][j]=(v[i][j]%MOD+MOD)%MOD;
				}
				return TI;
			}
			Mat&operator*=(const Mat&a){
				TI=(TI)*a;
				return TI;
			}
			Mat&operator*=(T a){
				f0(i,n)f0(j,m)
					if(fi)v[i][j]=1ll*v[i][j]*a%MOD;else v[i][j]*=a;
				return TI;
			}
			Mat&operator/=(T a){
				f0(i,n)f0(j,m)
					if(fi)v[i][j]=1ll*v[i][j]*inv1(a,MOD)%MOD;else v[i][j]/=a;
				return TI;
			}
			Mat&operator^=(LL a){
				if(n!=m)throw "n!=m";
				Mat an(n),tmp(v);
				for(;a;a>>=1,tmp*=tmp)
					if(a&1)an*=tmp;
				TI=an;
				return TI;
			}
			Mat trans(){
				Mat a(m,n);
				f0(i,m)f0(j,n)a[i][j]=v[j][i];
				return a;
			}
			int rank(){
				if(n!=m)throw "不是方阵，不能求秩";
				int cnt=0;VEC<VEC<T>>a=v;
				if(fi){//整数模意义下 
					f0(i,n)f0(j,n)a[i][j]=(a[i][j]%MOD+MOD)%MOD;
					f0(i,n){
						T t=a[i][i];
						if(t==0)continue;
						cnt++;
						f0(j,n)a[i][j]=1ll*a[i][j]*inv1(t,MOD)%MOD;
						f0(j,n)if(i!=j){
							t=a[j][i];
							f0(k,n)a[j][k]=(a[j][k]-1ll*t*a[i][k]%MOD+MOD)%MOD;
						}
					}
				}else{//实数、分数或模类 
					f0(i,n){
						T t=a[i][i];
						if(typeid(T)==typeid(double)||typeid(T)==typeid(long double))
							if(fabs(t)<eps)continue;else if(t==0)continue;
						cnt++;
						f0(j,n)a[i][j]/=t;
						f0(j,n)if(i!=j){
							t=a[j][i];
							f0(k,n)a[j][k]-=t*a[i][k];
						}
					}
				}
				return cnt;
			}
			Mat inv(){
				if(n!=m)throw "不是方阵，不能求逆";
				if(TI.rank()!=n)throw "未满秩，不能求逆";
				Mat<T>I(n);VEC<VEC<T>>a=v;
				if(fi){//整数模意义下 
					f0(i,n)f0(j,n)a[i][j]=(a[i][j]%MOD+MOD)%MOD;
					f0(i,n){
						T t=inv1(a[i][i],MOD);
						f0(j,n)a[i][j]=1ll*a[i][j]*t%MOD,I[i][j]=1ll*I[i][j]*t%MOD;
						f0(j,n)if(i!=j){
							t=a[j][i];
							f0(k,n)a[j][k]=(a[j][k]-1ll*t*a[i][k]%MOD+MOD)%MOD,I[j][k]=(I[j][k]-1ll*t*I[i][k]%MOD+MOD)%MOD;
						}
					}
				}else{
					f0(i,n){
						T t=a[i][i];
						f0(j,n)a[i][j]/=t,I[i][j]/=t;
						f0(j,n)if(i!=j){
							t=a[j][i];
							f0(k,n)a[j][k]-=t*a[i][k],I[j][k]-=t*I[i][k];
						}
					}
				}
				return I;
			}
			T sgn(){//求模质数或实数的行列式 
				if(n!=m)throw "不是方阵，不能求行列式";
				T an=1;VEC<VEC<T>>a=v;
				if(fi){
					f0(i,n)f0(j,n)a[i][j]=(a[i][j]%MOD+MOD)%MOD;
					if(IsPrime(MOD)){
						f0(i,n){
							T t=a[i][i];
							an=1ll*an*t%MOD;
							if(t==0)continue;
							f0(j,n)a[i][j]=1ll*a[i][j]*inv1(t,MOD)%MOD;
							f0(j,n)if(i!=j){
								t=a[j][i];
								f0(k,n)a[j][k]=(a[j][k]-1ll*t*a[i][k]%MOD+MOD)%MOD;
							}
						}
					}else{
						bool f=0;
						f0(i,n){
							FR(j,i+1,n-1)for(T A=v[i][i],B=v[j][i],t;B;){
								t=A/B;A%=B;swap(A,B);
								FR(k,i,n-1)(v[i][k]+=MOD-1ll*t*v[j][k]%MOD)%=MOD;
								FR(k,i,n-1)swap(v[i][k],v[j][k]);
								f^=1;
							}
							if(!v[i][i])return 0;
							an=1ll*an*a[i][i]%MOD;
						}
						if(f)an=(MOD-an)%MOD;
					}
				}else{
					f0(i,n){
						T t=a[i][i];
						an*=t;
						if(t==0)continue;
						f0(j,n)a[i][j]/=t;
						f0(j,n)if(i!=j){
							t=a[j][i];
							f0(k,n)a[j][k]-=t*a[i][k];
						}
					}
				}
				return an;
			}
			T Hash();
		};
		template<typename T> ostream &operator<<(ostream &os,const Mat<T>&a){
			os<<"N = "<<a.n<<",  M = "<<a.m<<endl;
			f0(i,a.n){
				f0(j,a.m)os<<a[i][j]<<"  ";
				os<<endl;
			}
			return os;
		}
		template<typename T> istream &operator>>(istream &is,Mat<T>&a){
			int n,m;is>>n>>m;a.init(n,m);
			f0(i,n)f0(j,m)is>>a[i][j];
			return is;
		}
		template<typename T> bool operator==(const Mat<T>&a,const Mat<T>&b){
			if(a.n!=b.n||a.m!=b.m)return 0;
			f0(i,a.n)f0(j,a.m)if(a[i][j]!=b[i][j])return 0;
			return 1;
		}
		template<typename T> bool operator!=(const Mat<T>&a,const Mat<T>&b){return !(a==b);}
		template<typename T> Mat<T> operator-(const Mat<T>&a){
			Mat<T> c(a.n,a.m);
			f0(i,a.n)f0(j,a.n)if(a.fi)c[i][j]=(a.MOD-a[i][j])%a.MOD;else c[i][j]=-a[i][j];
			return c;
		}
		template<typename T> Mat<T> operator+(const Mat<T>&a,const Mat<T>&b){
			if(a.n!=b.n||a.m!=b.m)throw "行列不匹配，不能相加";
			Mat<T> c(a.n,a.m);
			f0(i,a.n)f0(j,a.m){
				c[i][j]=a[i][j]+b[i][j];
				if(a.fi)c[i][j]%=a.MOD;
			}
			return c;
		}
		template<typename T> Mat<T> operator-(const Mat<T>&a,const Mat<T>&b){
			if(a.n!=b.n||a.m!=b.m)throw "行列不匹配，不能相减";
			Mat<T> c(a.n,a.m);
			f0(i,a.n)f0(j,a.m)
				if(a.fi)c[i][j]=(a[i][j]-b[i][j]+a.MOD)%a.MOD;else c[i][j]=a[i][j]-b[i][j];
			return c;
		}
		template<typename T> Mat<T> operator*(const Mat<T>&a,const Mat<T>&b){
			if(a.m!=b.n)throw "行列不匹配，不能相乘";
			Mat<T> c(a.n,b.m);
			f0(i,a.n)f0(j,b.m)f0(k,a.m)
				if(a.fi)c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j])%a.MOD;else c[i][j]+=a[i][k]*b[k][j];
			return c;
		}
		template<typename T> Mat<T> operator/(const Mat<T>&a,const Mat<T>&b){return a*b.inv();}
		template<typename T> Mat<T> operator*(const Mat<T>&a,T b){
			Mat<T> c(a.n,a.m);
			f0(i,a.n)f0(j,a.n)
				if(a.fi)c[i][j]=1ll*a[i][j]*b%a.MOD;else c[i][j]=a[i][j]*b;
			return c;
		}
		template<typename T> Mat<T> operator*(T a,Mat<T>&b){return b*a;}
		template<typename T> Mat<T> operator/(const Mat<T>&a,T b){
			Mat<T> c(a.n,a.m);if(a.fi)b=inv1(b,a.MOD);
			f0(i,a.n)f0(j,a.n)
				if(a.fi)c[i][j]=1ll*a[i][j]*b%a.MOD;else c[i][j]=a[i][j]/b;
			return c;
		}
		template<typename T> Mat<T> operator/(T a,const Mat<T>&b){return a*b.inv();}
