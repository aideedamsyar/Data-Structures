#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("Please input the number of students!");
        return -1;
    }
    
    int n = atoi(argv[1]);

    if (n < 2) {
        printf("Please input the number of students more than one!");
        return -1;
    }

    char (*names)[32] = malloc(sizeof(char[32]) * n);
	
    printf("Please enter %d names:\n", n);
        for(int i=0; i<n; i++) {
            char* name;
            scanf("%s", names[i]);
        }

    for (int i=0; i<n; i++) {
        printf("%s", names[i]);
        
        // Go to next line after printing except for the name
        if (i != n-1) { 
            printf("\n");
        }
    }
    
    free(names);
    
    return 0;
}