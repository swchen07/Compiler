int printk(int ptr, ...);
int scank(char ptr, ...);

int quicksort(int a, int left, int right){
	int i = left;
	int	j = right;
	int	mid = a[(i + j) / 2];
	while (i < j){
		while (a[i] < mid) {
            i = i + 1;
        }
		while (mid < a[j]){
            j = j - 1;
        }
		if (i < j){
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i = i + 1;
            j = j - 1;
		}
	}
	if (left < j) {
        quicksort(a, left, j - 1);
    }
	if (i < right) {
        quicksort(a, i + 1, right);
    }

    return 0;
}

int main(void){
	int n;
	int a[10];
    int temp;

	printk("Input the size of array:\n");
	scank("%d", &n);
	printk("Input %d integers:\n", n);
    int i;
	for (i = 0; i < n; i = i + 1){
        scank("%d", &temp);
        a[i] = temp;
    }
		
	quicksort(&a, 0, n - 1);
	printk("Output quicksort result:\n");
	for (i = 0; i < n; i=i+1){
		printk("%d ", a[i]);
    }
    
	return 0;
}