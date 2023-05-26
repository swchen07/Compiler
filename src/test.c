int printk(int ptr, ...);

int main(void){
 int a = 2;
 printk("%d\n", &a);
 return 0;
}

