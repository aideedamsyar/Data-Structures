#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Stack {
    int* key;
    int top;
    int max_stack_size;
} Stack;

Stack* CreateStack(int max);
void Push(Stack* s, int x);
int Pop(Stack* s);
int Top(Stack* s);
void DeleteStack(Stack* s);
int IsEmpty(Stack* s);
int IsFull(Stack* s);
void Postfix(Stack* s, char input_str);

Stack* CreateStack(int max) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s || !(s->key = (int*)malloc(max * sizeof(int)))) {
        // If memory allocation fails, print error and return NULL
        printf("Memory allocation failed\n");
        return NULL;
    }
    s->top = -1;
    s->max_stack_size = max;
    return s;
}

void Push(Stack* s, int x) {
    if(IsFull(s)) {
        printf("Stack Overflow\n");
        return; // Simply return without exiting or pushing
    }
    s->key[++s->top] = x;
}

int Pop(Stack* s) {
    if(s->top == -1) {
        printf("Stack Underflow\n");
        return -1; // Return an invalid value indicating error
    }
    return s->key[s->top--];
}

int Top(Stack* s) {
    if(IsEmpty(s)) {
        printf("Stack is empty\n");
        return -1; // Return an invalid value indicating error
    }
    return s->key[s->top];
}

void DeleteStack(Stack* s) {
    free(s->key);
    free(s);
}

int IsEmpty(Stack* s) {
    return s->top == -1;
}

int IsFull(Stack* s) {
    return s->top == s->max_stack_size - 1;
}

void Postfix(Stack* s, char input) {
    if(input >= '0' && input <= '9') { 
        Push(s, input - '0');
    } else {
        int operand2 = Pop(s);
        int operand1 = Pop(s);
        // Check for errors from Pop before proceeding
        if(operand1 == -1 || operand2 == -1) {
            printf("Error in operands\n");
            return; // Early return to avoid further calculation
        }
        switch(input) {
        case '+': Push(s, operand1 + operand2); break;
        case '-': Push(s, operand1 - operand2); break;
        case '*': Push(s, operand1 * operand2); break;
        case '/': if(operand2 == 0) {printf("Division by zero\n");} else {Push(s, operand1 / operand2);} break;
        case '%': if(operand2 == 0) {printf("Division by zero\n");} else {Push(s, operand1 % operand2);} break;
        default: printf("Invalid Operator!\n");
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc==1){
        printf("Please enter an input file.");
        return 0;
    }

    FILE *fi = fopen(argv[1], "r");

    Stack* stack = CreateStack(10);

    char c;
    printf("Top numbers: ");
    while(1) {
        fscanf(fi, "%c", &c);
        if (c == '!') {
            printf("\nCalculating Done!");
            break;
        }
        Postfix(stack, c);
        printf("%d ", Top(stack));
    }
    printf("\n");
    printf("evaluation result: %d\n", Pop(stack));

    fclose(fi);
    DeleteStack(stack);
}
