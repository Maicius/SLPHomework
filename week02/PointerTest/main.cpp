struct S{
	int i;
	int *p;
};

int main(){
	S s;
	int *p=&s.i;
	p[1]=3;
	p[0]=4;
	p[2]=5;
	s.p=p;
	int i;
	
	s.p[1]=1;
	s.p[0]=2;
	

	return 0;
}