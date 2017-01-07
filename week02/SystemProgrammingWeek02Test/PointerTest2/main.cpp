#include <stdio.h>
#include <malloc.h>
#include <string>
int counter=0;
//int* ptr_to_zero(){
//	int i=0;
//	return &i;
//}
//void main(){
//	int x=4;
//	int *p=&x;
//	int *k=p++;
//	char r=p-k;
//	while(1){
//		printf("addr:%d\n",ptr_to_zero());
//	}
//	printf("%d",r);
//}
//void GetMemory(char** p, int num){
//	*p=(char*)malloc(sizeof(char)*num);
//}
//void main(){
//	char *str=NULL;
//	GetMemory(&str,100);
//	strcpy(str,"hello");
//	getchar();
//}
int f(int);
int func1(int x){
	return f(x)+f(x)+f(x)+f(x);
}
int func2(int x){
	return 4*f(x);
}
int main(){
	//int a=func1(1);
	int b=func2(1);
	//printf("func1:%d\n", a);
	printf("fcun2:%d\n", b);
	getchar();
}
int f(int x){
	return counter++;
}
