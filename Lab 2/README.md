## Dynamic Memory Allocation - Week 2

This document covers the basics of dynamic memory allocation in C programming. Here, we will go through examples that demonstrate how to dynamically allocate memory for data structures such as arrays and structs.

### Example 1: Allocating Memory for an Array of Names

```c
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
        scanf("%s", names[i]);
    }

    for (int i=0; i<n; i++) {
        printf("%s", names[i]);
        if (i != n-1) { 
            printf("\\n");
        }
    }

    free(names);
    return 0;
}

### Understanding Pointers and Arrays

- `char name[32];` declares an array of 32 characters.
- `char* name[32];` declares an array of 32 character pointers.
- `char (*name)[32];` declares a pointer to an array of 32 characters.
- `argc` and `argv` are used to handle command line arguments, where `argc` is the argument count, and `argv` is an array of pointers to the arguments.
- `argv[0]` usually contains the name of the program, and `argv[1]` would contain the first command line argument passed to the program.
- `atoi(argv[1])` converts the string argument to an integer. This is used to determine the number of students based on user input.

### Example 2: Structs and Dynamic Memory

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 31 // Include null character '\0'

typedef struct student {
    char* name;
    int student_id;
    char *major;
} student;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Please enter the input file or output file!\\n");
        return 1; 
    }

    char *input_path, *output_path;
    FILE *fi, *fo;
    int num, i;

    input_path = argv[1];
    output_path = argv[2];

    fi = fopen(input_path, "r");
    fo = fopen(output_path, "w");

    fscanf(fi, "%d", &num); 
    fgetc(fi); // Skip newline character in buffer

    student *students = malloc(sizeof(student) * num);

    for (i = 0; i < num; i++) {
        students[i].name = malloc(sizeof(char) * MAX_LENGTH); 
        students[i].major = malloc(sizeof(char) * MAX_LENGTH); 
        fscanf(fi, "%30s %30s %d", students[i].name, students[i].major, &students[i].student_id);
    }

    for (i = 0; i < num; i++) {
        fprintf(fo, "%s\\t%s\\t%d\\n", students[i].name, students[i].major, students[i].student_id);
    }

    for (i = 0; i < num; i++) {
        free(students[i].name);
        free(students[i].major);
    }

    free(students);
    fclose(fi);
    fclose(fo);

    return 0;
}
