int printk(int ptr, ...);
int scank(int ptr, ...);

int main(){
	int a; 
	char b[100]; 
	scank("%s", b);
	printk("123131%s %d %s", "1222d", 1, b);
	return 0;
}

