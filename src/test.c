int printf(char ptr, ...);
int scanf(char ptr, ...);

int f(int ptr b){
	printf("hhh%d\n", b[1]);
	return 0;
}

int main(){
 int a = 4; 
 int a2 = 8; 
 int b[10];
 b[0] = 11;
 b[1] = 2;
 b[2] = 9;
 b[3] = 3;
 f(b);
 int t = b[2];
 printf("%d\n", b[2]);
 return 0;
}