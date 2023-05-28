int printk(int ptr, ...);
int scank(char ptr, ...);

static int a[10001];
int quicksort(int left, int right){
	int i = left;
	int	j = right;
	int temp = (i + j) / 2;
	int mid;
	mid = a[temp];
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
        quicksort(left, j - 1);
    }
	if (i < right) {
        quicksort(i + 1, right);
    }

    return 0;
}

int main(){
	int n;
    int i;
    int temp;

	scank("%d", &n);
	
	for (i = 0; i < n; i = i + 1){
        scank("%d", &temp);
        a[i] = temp;
    }
		
	quicksort(0, n - 1);
	for (i = 0; i < n; i=i+1){
		printk("%d\n", a[i]);
    }
    
	return 0;
}