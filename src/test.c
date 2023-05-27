int printk(int ptr, ...);

int main(){
	int a[1000][10];
	int i = 0;
	int j = 0;
	a[9][0] = 1;
	for(i=0;i<1000;i=i+1){
		for(j=0;j<10;j=j+1){
			a[i][j] = i+j;
			if(i == 99){
				printk("%d ", a[9][j]);
			}
			int k = 0;
			if(i == 100 && j == 5){
				for(k=0;k<10;k=k+1){
					if(k == 5){
						printk("$$$We are Best!$$$");
					}
				}
			}
		}
	}
	return 0;
}

