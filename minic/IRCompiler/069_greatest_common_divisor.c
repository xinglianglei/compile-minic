int fun(int m,int n){
	int rem;			
	while(n > 0){
		rem = m % n;
		m = n;
		n = rem;
	}
	return m;				
}

int getint();
void putint(int k);
void putch(int k);

int main(){
	int n,m;
	int num;
	m=getint();
	n=getint();
	num=fun(m,n);
	putint(num);

	return 0; 
}
