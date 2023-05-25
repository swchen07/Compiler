int main() {
	int i = 0; 
	int x = 0;
	for (i = 0; i < 10; i = i+1) {
		x = x + i; 
		if (x < 10) {
			x = x + 1; 
			if (x > 10) {
				x = x - 1;
			}
		}
	}

	for (;i < 10;) {
	}
}
