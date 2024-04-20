#include <stdio.h>
#include <stdlib.h>

struct TreeStruct {
    int size;
    int numOfNode;
    int* element;
};

typedef struct TreeStruct* Tree;

Tree CreateTree(int size);
void Insert(Tree tree, int value);
void PrintTree(Tree tree);
void PrintPreorder(Tree tree, int index);
void PrintInorder(Tree tree, int index);
void PrintPostorder(Tree tree, int index);
void DeleteTree(Tree tree);

int main(int argc, char* argv[]) {
    FILE* fi;
    Tree tree;
    int treeSize;
    int tmpNum;

    fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &treeSize);

    tree = CreateTree(treeSize);

    while(fscanf(fi, "%d", &tmpNum) == 1) {
        Insert(tree, tmpNum);
    }

    PrintTree(tree);
    DeleteTree(tree);

    return 0;
}

Tree CreateTree(int size) {
    Tree t = malloc(sizeof(struct TreeStruct));
    if (t == NULL) {
        printf("Error! Out of memory!");
        exit(1);
    }

    t->size = size;
    t->numOfNode = 0;
    t->element = malloc(sizeof(int) * size);

    if (t->element == NULL) {
        printf("Error! Out of memory!");
        exit(1);
    }

    return t;
}

void Insert(Tree tree, int value) {
    if (tree->numOfNode == tree->size) {
        printf("Error with node %d! Tree is full so we cannot insert any value in the tree!\n", value);
        return;
    }
    tree->element[tree->numOfNode++] = value;
}

void PrintTree(Tree tree) {
    printf("Preorder: ");
    PrintPreorder(tree, 0);
    printf("\n");

    printf("Inorder: ");
    PrintInorder(tree, 0);
    printf("\n");

    printf("Postorder: ");
    PrintPostorder(tree, 0);
    printf("\n");
}


void PrintPreorder(Tree tree, int index) {
    if (index < tree->numOfNode) {
        printf("%d ", tree->element[index]);
        PrintPreorder(tree, 2 * index + 1);
        PrintPreorder(tree, 2 * index + 2);
    }
}

void PrintInorder(Tree tree, int index) {
    if (index < tree->numOfNode) {
        PrintInorder(tree, 2 * index + 1);
        printf("%d ", tree->element[index]);
        PrintInorder(tree, 2 * index + 2);
    }
}

void PrintPostorder(Tree tree, int index) {
    if (index < tree->numOfNode) {
        PrintPostorder(tree, 2 * index + 1);
        PrintPostorder(tree, 2 * index + 2);
        printf("%d ", tree->element[index]);
    }
}

void DeleteTree(Tree tree) {
    free(tree->element);
    free(tree);
}
