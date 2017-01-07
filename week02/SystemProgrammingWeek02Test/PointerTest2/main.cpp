#include <stdio.h>
#include <malloc.h>
#include <string>
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
void GetMemory(char** p, int num){
	*p=(char*)malloc(sizeof(char)*num);
}
void main(){
	char *str=NULL;
	GetMemory(&str,100);
	strcpy(str,"hello");
	getchar();
}