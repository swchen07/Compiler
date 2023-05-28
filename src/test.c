int printk(int ptr, ...);
int scank(int ptr, ...);

int st(int ptr a){
	int temp;
	temp = a[1];
	a[9999] = 1000;
	printk("%d ",temp);
	return 0;
}

int main(){
	int a[10000];
	a[1] = 1;

	st(a);
	int temp = a[9999];
	printk("%d ",temp);
	
 return 0;
}