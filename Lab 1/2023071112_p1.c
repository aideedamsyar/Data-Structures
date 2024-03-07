#include <stdio.h>

int main() {
	for(int i=1; i<=9; i++) {
		printf("2*%d = %d", i, 2*i); 
		if (i!=9) {
			printf("\n");
		}

	}
	return 0;
}