#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode {
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Max(ElementType num1, ElementType num2);
int Height(Position P);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
AVLTree Insert(ElementType X, AVLTree T);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);

int main(int argc, char *argv[]) {
    AVLTree myTree = NULL;
    int key;

    FILE *fi = fopen(argv[1], "r");
    while (fscanf(fi, "%d", &key) != EOF) {
        myTree = Insert(key, myTree);
    }
    fclose(fi);

    PrintInorder(myTree);
    printf("\n");

    DeleteTree(myTree);
    return 0;
}

int Max(ElementType num1, ElementType num2) {
    if (num1 > num2) return num1;
    else return num2;
}

int Height(Position P) {
    if (P == NULL) 
        return -1; 
    else 
        return P->Height;
}


Position SingleRotateWithLeft(Position node) {
    Position K1;
    Position K2 = node;
    K1 = K2->Left;

    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), K2->Height) + 1; 

    return K1;
}

Position SingleRotateWithRight(Position node) {
    Position K1;
    Position K2 = node;
    K1 = K2->Right;

    K2->Right = K1->Left;
    K1->Left = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), K2->Height) + 1; 

    return K1;
    
}

Position DoubleRotateWithLeft(Position node) {
    Position K3 = node;
    K3->Left = SingleRotateWithRight(K3->Left);
    
    return SingleRotateWithLeft(K3);
}

Position DoubleRotateWithRight(Position node) {
    Position K3 = node;
    K3->Right = SingleRotateWithLeft(K3->Left);
    
    return SingleRotateWithRight(K3);
}


AVLTree Insert(ElementType X, AVLTree T) {
    if (T == NULL) {
        T = malloc(sizeof(struct AVLNode));
        if (T == NULL) {
            printf("Error: Out of space!");
            return NULL;
        } else {
            T->Element = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    } else if (X < T->Element) {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2) {
            if (X < T->Left->Element) {
                printf("There's node(%d) to be balanced! Do SingleRotateWithLeft!\n", T->Element);
                T = SingleRotateWithLeft(T);
            } else {
                printf("There's node(%d) to be balanced! Do DoubleRotateWithLeft!\n", T->Element);
                T = DoubleRotateWithLeft(T);
            }
        }
    } else if (X > T->Element) {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2) {
            if (X > T->Right->Element) {
                printf("There's node(%d) to be balanced! Do SingleRotateWithRight!\n", T->Element);
                T = SingleRotateWithRight(T);
            } else {
                printf("There's node(%d) to be balanced! Do DoubleRotateWithRight!\n", T->Element);
                T = DoubleRotateWithRight(T);
            }
        }
    } else {
        printf("Insertion Error: %d is already in the tree!\n", T->Element);
    }

    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

void PrintInorder(AVLTree T) {
    if (T != NULL) {
        PrintInorder(T->Left);
        printf("%d(%d) ", T->Element, T->Height);
        PrintInorder(T->Right);
    }
}

void DeleteTree(AVLTree T) {
    if (T->Left != NULL) DeleteTree(T->Left);
    if (T->Right != NULL) DeleteTree(T->Right);
    free(T);
}