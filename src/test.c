int printk(int ptr, ...);
int scank(int ptr, ...);

static int a;
static int b;

static int c[10000];

int st(){
	int temp;
	temp = c[5];
	printk("%d", temp);
	return 0;
}

int main(){
	int f[10000];
	f[9999] = 10;
	int e[100];
	a = 10;
	e[10] = a;
	c[10] = a;
	b = c[10];
	int d;

	st();
	
 return 0;
}