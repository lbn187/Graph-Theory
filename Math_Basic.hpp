#ifndef MATH_BASIC_HPP
#define MATH_BASIC_HPP
#include "start.hpp"
namespace Math_Basic{
	LL Mul(LL a,LL b,LL p){//O(1)LL*LL%LL 
		LL t=(a*b-LL((long double)a/p*b+1e-3)*p)%p;
		return t<0?t+p:t;
	}
	LL FastMul(LL a,LL b,LL p){//O(logn)快速乘 
    	LL v=0;
    	for(;b;a=(a+a)%p,b>>=1)
        	if(b&1)v=(v+a)%p;
    	return v;
	}
	LL Pw(LL a,LL b,LL p){//快速幂 
		LL v=1;
		for(a%=p;b;a=a*a%p,b>>=1)
			if(b&1)v=v*a%p;
		return v;
	}
	LL gcd(LL a,LL b){//递归版gcd 
		return b?gcd(b,a%b):a;
	}
	LL ungcd(LL a,LL b){//非递归版gcd 
    	for(LL t;b;)t=a%b,a=b,b=t;
    	return a;
	}
	void exgcd(LL a,LL b,LL&x,LL&y,LL&d){//扩欧，ax+by=gcd(a,b)
		if(!b)x=1,y=0,d=a;else
		exgcd(b,a%b,y,x,d),y-=a/b*x;
	}
	LL phi(LL n){//O(n^0.5)求欧拉函数，预处理素数可做到O(n^0.5/logn) 
    	LL i,V=n;
    	for(i=2;i*i<=n;i++)
        	if(n%i==0)for(V=V/i*(i-1);n%i==0;)n/=i;
    	if(n>1)V=V/n*(n-1);
    	return V;
	}
	LL inv1(LL a,LL n){//求a关于模数n的逆元 
    	LL d,x,y;
    	exgcd(a,n,x,y,d);
    	return d==1?(x+n)%n:-1;
	}
	LL inv2(LL a,LL p){return Pw(a,p-2,p);}//费马小定理 
	LL inv3(LL a,LL n){return Pw(a,phi(n)-1,n);}//欧拉定理
	LL inv4(LL i,LL m){//递归求单个数的逆元 
		if(i==1)return 1;
		return inv4(m%i,m)*(m-m/i)%m;
	}
	void preinv(int n,int M,int inv[]){//预处理1~n模M的逆元 
		inv[1]=1;
		for(int i=2;i<=n;i++)inv[i]=1ll*inv[M%i]*(M-M/i)%M;
	}
}
#endif
