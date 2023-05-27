int printf(char ptr, ...);
int scanf(char ptr, ...);

int f(int ptr b){
	printf("hhh%d\n", b[0]);
	return 0;
}

int main(){
 int a = 4; 
 int a2 = 8; 
 int b[3];
 b[0] = 1;
 b[2] = 0;
 f(b);
 printf("%d\n", b[9]);
 return 0;
}