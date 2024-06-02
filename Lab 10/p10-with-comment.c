#include <stdio.h>
#include <stdlib.h>
#include<time.h>

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

    if (root1 != root2) {  // Only unite if they are from different sets
        if (sets->ptr_arr[root1] < sets->ptr_arr[root2]) {  // root1 has more members
            sets->ptr_arr[root2] = root1;
        } else {
            if (sets->ptr_arr[root1] == sets->ptr_arr[root2]) {
                sets->ptr_arr[root1]--;  // Increment the rank
            }
            sets->ptr_arr[root2] = root1;
        }
    }
}

void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n) {
    int totalWalls = n * (n - 1) * 2; // Total walls includes both horizontal and vertical walls
    srand(time(NULL)); // Seed random number generator

    while (find(sets, 0) != find(sets, n * n - 1)) { // Ensure the entrance and exit are connected
        int chosenWall = rand() % totalWalls; // Choose a wall randomly
        int leftCell, rightCell;

        if (chosenWall < n * (n - 1)) { // Horizontal walls
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

        if (find(sets, leftCell) != find(sets, rightCell)) { // Check if not in the same set
            maze->ptr_arr[chosenWall] = 0; // Remove the wall
            union_(sets, leftCell, rightCell); // Union the sets of the two cells
        }
    }
}



void printMaze(PrintDisjointSets *maze, int n) {
    // Print top boundary
    printf("*");  // Top left corner always starts with *
    for (int j = 0; j < n - 1; j++) printf("-*");
    printf("-*\n");  // End of the top boundary

    for (int i = 0; i < n; i++) {
        // Print the left wall of the maze or open space for the entrance
        if (i == 0) printf(" ");  // Open the first cell of the first row
        else printf("|");

        // Print the internal cells separated by vertical walls or spaces
        for (int j = 0; j < n - 1; j++) {
            int rightWall = i * (n - 1) + j;
            printf(" ");  // Space for each cell
            if (maze->ptr_arr[rightWall] == 1) printf("|");  // Vertical wall if exists
            else printf(" ");  // No vertical wall
        }

        // Open the last cell of the last row or close it with a wall
        if (i == n - 1) printf("  \n");  // Open the exit
        else printf(" |\n");  // Close the row with a wall

        // Print the bottom boundary of the current row if not the last row
        if (i < n - 1) {
            printf("*");  // Start the bottom boundary of the row
            for (int j = 0; j < n; j++) {
                int bottomWall = n * (n - 1) + i * n + j;
                if (maze->ptr_arr[bottomWall] == 1) printf("-*");  // Horizontal wall if exists
                else printf(" *");  // No horizontal wall
            }
            printf("\n");  // End of the current row
        }
    }

    // Print the bottom border of the maze
    printf("*");  // Start the bottom border
    for (int j = 0; j < n - 1; j++) printf("-*");  // Continue the bottom border
    printf("-*\n");  // End the bottom border
}



void freeMaze(DisjointSets *sets, PrintDisjointSets *maze) {
    if (sets != NULL) {
        free(sets->ptr_arr);  // Free the array inside the DisjointSets structure
        free(sets);          // Free the DisjointSets structure itself
    }

    if (maze != NULL) {
        free(maze->ptr_arr); // Free the array inside the PrintDisjointSets structure
        free(maze);          // Free the PrintDisjointSets structure itself
    }
}