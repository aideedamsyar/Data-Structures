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
        printf("Please enter the input file or output file!\n");
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
        fprintf(fo, "%s\t%s\t%d\n", students[i].name, students[i].major, students[i].student_id);
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
