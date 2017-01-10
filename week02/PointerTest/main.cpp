#include<stdio.h>

struct S{
	int i;
	int *p;
};

int main(){
	S s;
	int *p=&s.i;
	p[1]=3;
	p[0]=4;
	s.p=p;
	s.p[0]=2;
	//此处将p赋值为1，p的地址变为1，所以出错
	s.p[1]=1;	
	getchar();
	return 0;
}