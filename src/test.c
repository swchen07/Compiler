int printk(int ptr, ...);
int scank(int ptr, ...);

int main(){
	int a; 
	char b[100]; 
	char c;
	char d; 
	scank("%d", &a); 
	scank("%s", b);
	scank("%c%c", &c, &d);
	printk("123131 %s %d %d %s %c\n", "1222d", 1, a, b, d);
	return 0;
}

