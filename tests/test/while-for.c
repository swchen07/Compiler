int printk(int ptr, ...);

int main(void){
	int c[2][3][4];
	int i;
	int j;
	int k;
	for (i = 0; i < 2; i=i+1) {
		for (j = 0; j < 3; j=j+1) {
			for (k=0; k < 4; k=k+1) {
				c[i][j][k] = i*j+k+1;
			}
		}
	}
	i = 0;
	while(i < 2) {
		j = 0;
		while(j < 3) {
			k = 0;
			while(k < 4) {
				printk("%d ", c[i][j][k]);
				k = k+1;
			}
			j = j+1;
		}
		i = i+1;
	}
	return 0;
}

