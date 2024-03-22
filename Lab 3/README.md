# Lab 3

Status: In progress
Course: Data Structures (https://www.notion.so/Data-Structures-559c55dbecd54ff3a57c68e911f63a2b?pvs=21)
Due date: March 24, 2024 11:59 PM (GMT+9)

# Singly Linked List Implementation in C

<aside>
💡 This documentation provides an overview and explanation of a simple singly linked list implementation in C. The code includes functionalities for creating a list, adding and removing elements, and utility functions for finding elements and printing the list content.

</aside>

- The core of the linked list is defined by a `Node` structure, which contains an integer `element` and a pointer to the next node.

```c
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node {
    ElementType element;
    Position next;
};
```

- **`PtrToNode`**: A pointer to a **`Node`**.
- **`List`**: Represents the linked list itself, essentially a pointer to the first **`Node`** (the header in this case).
- **`Position`**: Used to denote a specific position within the list.

## **Core Functions**

### **MakeEmptyList**

Initializes a new list by creating a header node. This node does not store any actual data relevant to the list's content but serves as a starting point.

```c
List MakeEmptyList() {
    List l = (List)malloc(sizeof(struct Node));
    l->element = -1;  // Header node's element is set to -1 as a placeholder.
    l->next = NULL;   // Initially, the list is empty, so the next pointer is NULL.
    return l;
}
```

### **Insert**

Inserts a new element **`x`** after the specified position **`p`** in the list **`l`**.

```c
void Insert(ElementType x, Position p, List l) {
    Position new_node = (Position)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    new_node->element = x;   // Assign the element to the new node.
    new_node->next = p->next;  // Link the new node into the list.
    p->next = new_node;
}
```

### **Delete**

Removes the first occurrence of **`x`** from the list **`l`**.

```c
void Delete(ElementType x, List l) {
    Position p = FindPrevious(x, l);  // Find the node preceding the node to delete.
    if (!isLast(p)) {  // Verify that we're not at the end of the list.
        Position tmp = p->next;   // Temporary pointer to the node to be deleted.
        p->next = tmp->next;   // Remove the node from the list.
        free(tmp);   // Free the memory of the node.
    }
}

```

### **Find and FindPrevious**

**`Find`** searches for and returns the position of the first occurrence of **`x`** in the list **`l`**.

```c
Position Find(ElementType x, List l) {
    Position p = l->next;
    while (p != NULL && p->element != x) {
        p = p->next;
    }
    return p;
}
```

**`FindPrevious`** returns the position of the node immediately before the first occurrence of **`x`**.

```c
Position FindPrevious(ElementType x, List l) {
    Position p = l;
    while (p->next != NULL && p->next->element != x) {
        p = p->next;
    }
    return p;
}
```

### **PrintList**

Displays the elements of the list **`l`**.

```c
void PrintList(List l) {
    Position tmp = l->next;
    if (tmp == NULL) {
        printf("The list is empty.\n");
    } else {
        while (tmp != NULL) {
            printf("key: %d\t", tmp->element);
            tmp = tmp->next;
        }
        printf("\n");
    }
}
```

### **DeleteList**

Frees all nodes in the list **`l`**, including the header, to prevent memory leaks.

```c
void DeleteList(List l) {
    Position p = l->next;
    while (p != NULL) {
        Position tmp = p->next;
        free(p);
        p = tmp;
    }
    free(l);  // Don't forget to free the header node as well.
}
```

## **Main Function**

Demonstrates reading commands from a file and executing operations on the linked list accordingly.

```c
int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Please enter an input file.\n");
        return 0;
    }

    FILE *input = fopen(argv[1], "r");
    Position header = Make
```

## Input .txt file

```
i 3 -1
i 4 3
i 7 -1
i 5 8
d 3
i 2 7
d 9
f 3
f 7
f 2
p
```