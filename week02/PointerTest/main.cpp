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
	//�˴���p��ֵΪ1��p�ĵ�ַ��Ϊ1�����Գ���
	s.p[1]=1;	
	getchar();
	return 0;
}