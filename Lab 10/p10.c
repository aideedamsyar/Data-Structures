#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet {
    int size;
    int* ptr_arr; // parent
} DisjointSets;

typedef struct _PrintDisjointSet {
    int size;
    int *ptr_arr; // wall, (if wall exist -> 1, otherwise 0)
} PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets *maze, int n);
int find(DisjointSets *sets, int x);
void union_(DisjointSets *sets, int i, int j);
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n);
void printMaze(PrintDisjointSets *maze, int n);
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze);

int main(int argc, char* argv[]) {
    int num;
    FILE *fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &num);
    fclose(fi);

    DisjointSets *sets;
    PrintDisjointSets *maze;

    sets = (DisjointSets*) malloc(sizeof(DisjointSets));
    maze = (PrintDisjointSets*) malloc(sizeof(PrintDisjointSets));

    init(sets, maze, num);
    createMaze(sets, maze, num);
    printMaze(maze, num);
    freeMaze(sets, maze);

    return 0;
}

void init(DisjointSets *sets, PrintDisjointSets *maze, int n) {
    sets->size = n;
    maze->size = n;

    sets->ptr_arr = malloc(sizeof(int) * n * n);
    maze->ptr_arr = malloc(sizeof(int) * (n * n * 2));

    for (int i=0; i < n * n; i++) {
        sets->ptr_arr[i] = -1;
    }

    for (int i=0; i < (n * n * 2); i++) {
        maze->ptr_arr[i] = 1;
    }
}

int find(DisjointSets *sets, int x){
 	if(sets->ptr_arr[x] < 0 || sets->ptr_arr[x] == x)
 		return x;
 	return find(sets, sets->ptr_arr[x]);
}

void union_(DisjointSets *sets, int i, int j) {
    int root1 = find(sets, i);
    int root2 = find(sets, j);

    if (root1 != root2) {  
        if (sets->ptr_arr[root1] < sets->ptr_arr[root2]) {  
            sets->ptr_arr[root2] = root1;
        } else {
            if (sets->ptr_arr[root1] == sets->ptr_arr[root2]) {
                sets->ptr_arr[root1]--;  
            }
            sets->ptr_arr[root2] = root1;
        }
    }
}

void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n) {
    int totalWalls = n * (n - 1) * 2; 
    srand(time(NULL)); 

    while (find(sets, 0) != find(sets, n * n - 1)) { 
        int chosenWall = rand() % totalWalls; 
        int leftCell, rightCell;

        if (chosenWall < n * (n - 1)) { 
            int row = chosenWall / (n - 1);
            int col = chosenWall % (n - 1);
            leftCell = row * n + col;
            rightCell = leftCell + 1;
        } else { // Vertical walls
            int verticalWallIndex = chosenWall - n * (n - 1);
            int row = verticalWallIndex / n;
            int col = verticalWallIndex % n;
            leftCell = row * n + col;
            rightCell = leftCell + n;
        }

        if (find(sets, leftCell) != find(sets, rightCell)) { 
            maze->ptr_arr[chosenWall] = 0; 
            union_(sets, leftCell, rightCell); 
        }
    }
}

void printMaze(PrintDisjointSets *maze, int n) {
    printf("*"); 
    for (int j = 0; j < n - 1; j++) printf("-*");
    printf("-*\n"); 

    for (int i = 0; i < n; i++) {
        if (i == 0) printf(" ");  
        else printf("|");

        for (int j = 0; j < n - 1; j++) {
            int rightWall = i * (n - 1) + j;
            printf(" "); 
            if (maze->ptr_arr[rightWall] == 1) printf("|");
            else printf(" ");  
        }

        if (i == n - 1) printf("  \n");  
        else printf(" |\n"); 

        if (i < n - 1) {
            printf("*");  
            for (int j = 0; j < n; j++) {
                int bottomWall = n * (n - 1) + i * n + j;
                if (maze->ptr_arr[bottomWall] == 1) printf("-*"); 
                else printf(" *");  
            }
            printf("\n"); 
        }
    }

    printf("*");  
    for (int j = 0; j < n - 1; j++) printf("-*");
    printf("-*\n");
}

void freeMaze(DisjointSets *sets, PrintDisjointSets *maze) {
    if (sets != NULL) {
        free(sets->ptr_arr);  
        free(sets);          
    }

    if (maze != NULL) {
        free(maze->ptr_arr); 
        free(maze);         
    }
}