- Lab
    - Problem 1
        - ![](local:///Users/deedsofaraway/remnote/remnote-64326087e00ecb2f760d9d48/files/7c9vD04XZJPwKePcgUjs92YFdgCpe_638zygiJgAD28VhmZINprkz8AxHWvlGID9JCd4pU4IhrXoF65qPPNCNfDyQgFPT03DAv-psNh854WNHk8vus6WqYBAG0-hkZCb.jpeg)
        - ![](local:///Users/deedsofaraway/remnote/remnote-64326087e00ecb2f760d9d48/files/o2bWphlzuT9tYJgg-0WTrvngrCQG8JlKlh_o3-8vikSWvhOp2bA4mPPX3o8n4fycS-d95faWBiLCD1VXzis1mtXBEBmiGH8Mf8C9hbukX9UON3ouJjYxZ79lmZQwbG2-.jpeg)
        - .
            ```
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
            ```
            - > **Notice the declaration of ****`names`**** and its memory allocation:** 
            - `char name[32];` is a fixed-size character array (a string of up to 31 characters plus `\0`).
            - `char* name[32];` is an array of 32 pointers, each potentially pointing to strings of any size.
            - `char (*name)[32];` is a pointer to an array of 32 characters, useful for pointing to multiple fixed-size character arrays.
        - 
        - `argc` refers to 'argument count'
        - `argv` refers to 'argument vector'
            - `argv[0]` here is the file name, `argv[1]` here is the actual first argument
                - use `atoi()` to convert the `argv` into an integer.
        - 
        - Problem 2
        - ![](local:///Users/deedsofaraway/remnote/remnote-64326087e00ecb2f760d9d48/files/2vmrj15mzaScK0n5SeQ1giL2jrJdpBJvrg63YSB95vVY7eB27G5cNrcE7DSrheTH50jdirqE_SZnIgWjCY0ekXLEM6zlcIYMoLraESwY1RohjaVnZIs1YZ2wNUfWMs9c.jpeg)
        - ![](local:///Users/deedsofaraway/remnote/remnote-64326087e00ecb2f760d9d48/files/k2xG09FPZYU_6MX4RxF0l4aezhqXt9cl4-0Ja8xabKVZhepzRLJFPcdbAiBpOwog-Yyk_XdM1d4XMblzSnFgcK68VEEDXZqfRPha17TVZevg-4Cpm99hCXUEK1dChL0L.jpeg)
        - ![](local:///Users/deedsofaraway/remnote/remnote-64326087e00ecb2f760d9d48/files/wiRnoL5yaJ53WfAOQVUxImogeSfDsMZG0S2R6Gj5CjM6zWNdiEztg_DtNPSnlPtngfZMcEuNHEzewapTx0XKolhkixmhYF0k7c0xhrMsa2tHAb6Vjz8VA5YLuSbRLd2j.jpeg)
        - .
            ```
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
            ```
        - `input.txt` 
            - .
                ```
                4
Clara AI 2019123456
Haley CS 2019123457
Ann Softward 2019123458
Linda Philosophy 2019123459
                ```
        - > **Notes:** 
        - `char* input_path` and `char* output_path` are just simple strings.
        - `FILE` used is for input and output streams.
        - `fopen(input_path, "r")`  "r" means read.
        - `fopen(output_path, "w")`  "w" means write/create a new file through the output stream.
        - `fscanf()` in this case is similar to the `scanf()` , add stream as the first argument.
        - `fgetc()` is similar to the use of `getchar()` used when we want to read and remove the newline character in the buffer, add stream as the argument.
        - 
