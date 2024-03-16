## 📚 Lab 2-1: Dynamic Name Storage
- **Program**: `{student_id}_p2_1.c`
- **Structure**: Pointer array
- **📥 Input**: `n` names without spaces, max 30 chars
- **📤 Output**: Echo `n` names
- **🔒 Conditions**:
  - Dynamic memory with `malloc()`
  - Error if `n` < 2: "Input number of students!"
 
```C
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
## Understanding Pointers and Arrays
- **Name Declarations and Memory Allocation**:
  - `char name[32];` ➡️ Fixed-size character array (up to 31 characters + null terminator).
  - `char* name[32];` ➡️ Array of 32 pointers to strings.
  - `char (*name)[32];` ➡️ Pointer to an array of 32 characters.
  
- **Command Line Arguments**:
  - `argc` ➡️ Argument Count.
  - `argv` ➡️ Argument Vector.
    - `argv[0]` is the program name.
    - `argv[1]` is the first actual argument.
    - Use `atoi(argv[1])` to convert this argument to an integer.
   
---

## 🏗️ Lab 2-2: Student Structs
- **Program**: `{student_id}_p2_2.c`
- **CLI Usage**: `<input file> <output file>`
- **🛠️ Structure**: Store and print student info
- **📋 Input**: Number of students + details
- **📝 Output**: Student details as entered
- **🚫 Conditions**:
  - Names/majors: ≤30 chars, no spaces
  - `student_id`: Integer range (-2,147,483,648 to 2,147,483,647)
  - Error if files not specified: "Enter the input/output file!"

## 👨‍💻 Lab 2-2 Code Snippet
- **C Program**: File I/O with student structs.
- **Syntax**: `typedef` for struct, file manipulation with `FILE*`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
  char *name;
  int student_id;
  char *major;
} student; // Define struct!

int main(int argc, char *argv[]) {
  char *input_path, *output_path;
  FILE *fi, *fo;
  int num, i;
  student* students;

  // Code omitted for brevity
  // ...

  return 0;
}
```


```C
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

## File I/O in C
- **Path Variables**:
  - `char* input_path` and `char* output_path` are string variables for file paths.
  
- **File Operations**:
  - `FILE*` is used for input and output streams.
  - `fopen(input_path, "r")` ➡️ Open a file for reading ("r").
  - `fopen(output_path, "w")` ➡️ Open a file for writing ("w"), creates a new file if it doesn't exist.
  
- **Reading and Writing**:
  - `fscanf()` functions like `scanf()`, but with a file stream as the first argument.
  - `fgetc()` is used like `getchar()`, for reading and removing newline characters from the buffer, with a file stream as the argument.
