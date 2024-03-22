#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node {
    ElementType element;
    Position next;
};

List MakeEmptyList();
int isLast(Position p);
void Delete(ElementType x, List l);
Position FindPrevious(ElementType x, List l);
Position Find(ElementType x, List l);
void Insert(ElementType x, Position p, List l);
void DeleteList(List l);
void PrintList(List l);

int main(int argc, char *argv[]) {
    char command;
    int key1, key2;
    FILE *input, *output;
    Position header = NULL, tmp = NULL;

    if (argc <= 1) {
        printf("please enter an input file.");
        return 0;
    } else {
        input = fopen(argv[1], "r");
    }

    header = MakeEmptyList();

    while(1) {
        command = fgetc(input);
        if(feof(input)) break;

        switch(command) {
            case 'i':
                fscanf(input, "%d %d", &key1, &key2);
                if (key2 == -1) {        
                    Insert(key1, header, header);
                } else {
                    tmp = Find(key2, header);
                    Insert(key1, tmp, header);
                }
                break;
            case 'd':
                fscanf(input, "%d", &key1);
                Delete(key1, header);
                break;
            case 'f':
                fscanf(input, "%d", &key1);
                tmp = FindPrevious(key1, header);
                if (isLast(tmp)) {
                    printf("Could not find %d in the list.\n", key1);
                } else if (tmp->element > 0) {
                    printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
                } else {
                    printf("Key of the previous node of %d is header.\n", key1);
                }
                break;
            case 'p':
                PrintList(header);
                break;
            default:
                ;    
        }
    }
    fclose(input);
    DeleteList(header);
    return 0;
}

List MakeEmptyList() {
    List l = (List)malloc(sizeof(struct Node));
    l->element = -1;
    l->next = NULL;
    return l;
}

int isLast(Position p) {
    if (p == NULL) return 0; 
    return p->next == NULL;
}

Position FindPrevious(ElementType x, List l) {
    Position p = NULL;
    p = l;
    while(p->next != NULL && p->next->element != x){
        p = p->next;
    }
    return p;
}

void Insert(ElementType x, Position p, List l) {
    Position new_node = (Position)malloc(sizeof(struct Node));
    if (p == NULL) {
        printf("Insertion(%d) Failed: cannot find the location to be inserted.\n", x);
    } else {
        new_node->element = x;
        new_node->next = p->next;
        p->next = new_node;
    }
}

void Delete(ElementType x, List l) {
    Position p, tmp;
    if (l->next != NULL && l->next->element == x) { 
        tmp = l->next;
        l->next = tmp->next;
        free(tmp);
        return;
    }
    p = FindPrevious(x, l); 
    if (p != NULL && p->next != NULL && p->next->element == x) {
        tmp = p->next;
        p->next = tmp->next;
        free(tmp);
    } else {
        printf("Deletion Failed: element %d is not in the list.\n", x);
    }
}

void DeleteList(List l) {
    Position p = NULL, tmp = NULL;
    p = l->next;
    l->next = NULL;
    while(p != NULL){
        tmp = p -> next;
        free(p);
        p = tmp;
    }
}

void PrintList(List l) {
    PtrToNode tmp = NULL;
    tmp = l->next;
    if(tmp == NULL){
        printf("list is empty!\n");
        return;
    }
    while(tmp != NULL){
        printf("key: %d\t", tmp->element);
        tmp = tmp->next;
    }
    printf("\n");

}

Position Find(ElementType x, List l) {
    Position p = NULL;
    p = l->next;
    while(p != NULL && p->element != x){
    p = p->next;
    }
    return p;
}