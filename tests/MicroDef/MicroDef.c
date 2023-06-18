int printk(int ptr, ...);
int scank(char ptr, ...);

#define MAXLEN 10000
#define SortMethod quicksort
#define Zero 0

int quicksort(int ptr a, int left, int right){
	//printk("QuickSort\n");
	int i = left;
	int	j = right;
	int temp = i + j;
	temp = temp/2;
	//printk(" %d %d %d @@@", temp, left, right);
	int mid;
	mid = a[temp];
	//printk(" %d# ", mid);
	while (i < j){
		while (a[i] < mid) {
            i = i + 1;
			//printk("What i%d?\n",i);
        }
		while (mid < a[j]){
            j = j - 1;
			//printk("What j%d?\n",j);
        }
		if (i <= j){
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i = i + 1;
            j = j - 1;
		}
		//printk("\n");
	}
	
	if (left < j) {
        quicksort(a, left, j);
    }
	if (i < right) {
        quicksort(a, i, right);
    }

    return Zero;
}

int main(){
	int n;
    int temp;
	int a[MAXLEN];
	scank("%d", &n);
    int i;
	
	for (i = 0; i < n; i = i + 1){
        scank("%d", &temp);
        a[i] = temp;
    }
		
	SortMethod(a, 0, n - 1);
	for (i = 0; i < n; i=i+1){
		printk("%d\n", a[i]);
    }
    
	return Zero;
}