int printk(int ptr, ...);
int scank(int ptr, ...);

static int y;
static int ym[20];

int a(int x){
	printk("%10d\n", x);
	return 1;
}

int main(){
	int a = 4; 
	int a2 = 8; 
	y = 2;
	// ym[3] = 3;
	printk("%d ", y);
	printk("%d\n", ym[3]);
	a(100);
	a(a);
	a(100*a);

	// a
	/*
	sdsadassad
	*/
	// int a; 
	// char b[100]; 
	// char c;
	// char d; 
	// scank("%d", &a); 
	// scank("%s", b);
	// scank("%c%c", &c, &d);
	// printk("123131 %s %d %d %s %c\n", "1222d", 1, a, b, d);

	int ma[2][2];
	int mb[2][2];
	int i;
	int j;

	for(i=0; i < 2; i=i+1){
		for (j=0; j < 2; j=j+1){
			
		}
		printk("\n");
	}

	return 0;
}

