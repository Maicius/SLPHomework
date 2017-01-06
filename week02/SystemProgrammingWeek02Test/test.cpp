#include <stdio.h>
int bitAnd(int x, int y) {

  return ~(~x | ~y);

}
int bitOr(int x, int y) {

  return ~(~x & ~y);

}
int isZero(int x) {

  return (!x);

}
int minusOne(int x) {

  return (x+~0);

}
int bitXor(int x, int y) {
	//先互相取异，再或
	int a = (~x)&y, b = x&(-y);
    return ~(~a & ~b);

}
int getByte(int x, int n){
	
	//return (0xff & (x >>( n<< 3)));
	int  a=n<<3;
	return (0xff & (x>>(n<<3)));
}
int isPositive(int x) {
	//设字长为N,算术右移n-1为，最高位为符号位
  int a=~x>>3;
  int b = ~x+1;
  int c = (~x+1)>>3;
  return (~x>>3)&((~x+1)>>3)&0x1;

}
int negate(int x) {

  return ~x+1;

}
int isLess(int x, int y){
	return !((~x+1+y)>>31);
}

int shiftAreArith(){
	return (-1)==(-1>>1);
}
int isNonNegative(int x){
	return !(x>>31);
}


int main(){
	printf("BitAnd: %d\n",bitAnd(5,6));
	printf("BitOr: %d\n",bitOr(5,6));
	printf("Iszero: %d\n",isZero(5));
	printf("Iszero: %d\n",isZero(0));
	printf("MinusOne: %d\n", minusOne(5));
	printf("XOR: %d \n", bitXor(4, 5));
	printf("Negate: %d \n", negate(32));
	printf("getByte: %x \n",getByte(0x12345678,1));
	printf("%d",isPositive(16));
	printf("%d",shiftAreArith());
	printf("%d\n",isNonNegative(5));
	printf("%d\n",isNonNegative(-5));
	printf("lsLess: %x \n",isLess(3, 2));
	getchar();
}