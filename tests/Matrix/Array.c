static int c;
static int d[100];
int printk(int ptr, ...);
int scank(int ptr, ...);

int main(){
	int a2;
	int b1;
	int a1;
	int b2 =2;
	d[1] = b2;
	int Arr1[1000];
	int Arr2[1000];
	int Res[1000];
	int i;
	int j;
	int k;
	int temp1;


	scank("%d %d", &a1, &b1);

	for(i = 0;i<a1;i=i+1){
		for(j=0;j<b1;j=j+1){
			scank("%d", &temp1);
			Arr1[i*25+j] = temp1;
		}
	}

	scank("%d %d ", &a2, &b2);
	for(i = 0;i<a2;i=i+1){
		for(j=0;j<b2;j=j+1){
			scank("%d", &temp1);
			Arr2[i*25+j] = temp1;
		}
	}
	
	if(b1 != a2){
		printk("Incompatible Dimensions\n");
		return 0;
	}
	for(i = 0;i<a1;i=i+1){
		for(j=0;j<b2;j=j+1){
			int sum = 0;
			for(k=0;k<b1;k=k+1){
				int temp1 = Arr1[i*25+k];
				int temp2 = Arr2[k*25+j];
				sum = sum + temp1 * temp2;
			}
			Res[i*25+j] = sum;
		}
	}
	for(i=0;i<a1;i=i+1){
		for(j=0;j<b2;j=j+1){
			int temp = Res[i*25+j];
			printk("%10d",temp);
		}
		printk("\n");
	}

	return 0;
}