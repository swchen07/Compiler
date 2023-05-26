
int a() {
	while(1){
		break; 
		continue; 
	}

	int a = 1; 
	while (a < 10) {
		a = a+1; 
		while (0) {
			a = a*2;
			continue; 
		}
		break; 
	}
}

int main() {
	int a; 
	for (a = 0; a < 10; a=a+1) {
		int a = 2;
		if (a > 3) {
			a = a+2;
			if (a < 2) {
				int a; 
				a = a-2; 
				break; 
			}
			continue; 
		}
	}
	for (;1;){
		break; 
		continue; 
	}
	a();
}

