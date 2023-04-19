#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef enum {
    white,
    red,
    green,
    blue,
    yellow
} color;

typedef struct list {
    color value;
    struct list* next;
} node;

node* InitList(color value) {
    node* root = (node*)malloc(sizeof(node));
    root->value = value;
    root->next = NULL;
    return root;
}

node* AddList(node* root, color value, int number) {
    int count = 1;
    while (count != number) {
        if (root->next != NULL) {
            root = root->next;
            ++count;
        } else {
            printf("There are no such number near you want to add node :(\n");
            return root;
        }
    }
    node* temp;
    node* p;
    p = root->next;
    temp = (node*)malloc(sizeof(node));
    root->next = temp;
    temp->value = value;
    temp->next = p;
    return temp;
}

node* DeleteList(node* root, int number) {
    int count = 1;
    node* item;
    node* temp;
    temp = root;
    while (count != number - 1) {
        if (temp->next->next != NULL) {
            temp = temp->next;
            ++count;
        } else {
            break;
        }
    }
    item = temp->next;
    if (item->next == NULL) {
        temp->next = NULL;
    } else {
        temp->next = item->next;
    }
    free(item);
    return temp;
}

void PrintList(node* root) {
    while(root != NULL) {
        switch(root->value) {
            case white:
                printf("white ");
                break;
            case red:
                printf("red ");
                break;
            case green:
                printf("green ");
                break;
            case blue:
                printf("blue ");
                break;
            case yellow:
                printf("yellow ");
                break;
        }
        root = root->next;
    }
}

int CountList(node* root) {
    int count = 1;
    while (root->next != NULL) {
        ++count;
        root = root->next;
    }
    return count;
}

void Swap(node* root, int number1, int number2) {
    int count = 1;
    color temp;
    node* item;
    while (count != number1) {
        root = root->next;
        ++count;
    }
    item = root;
    temp = root->value;
    while (count != number2) {
        root = root->next;
        ++count;
    }
    item->value = root->value;
    root->value = temp;
    return;
}

void Solve(node* root, int count) {
    int number = 1;
    if (count % 2 == 0) {
        while (number != (count / 2 + 1)) {
            Swap(root, number, number + count / 2);
            ++number;
        }
    } else {
       while (number != (count / 2 + 1)) {
            Swap(root, number, number + count / 2 + 1);
            ++number;
        } 
    }
    return;
}

int main() {
    node* root = NULL;
    root = InitList(white);
    AddList(root, yellow, 1);
    AddList(root, blue, 2);
    AddList(root, red, 3);
    AddList(root, green, 4);
    AddList(root, white, 5);
    PrintList(root);
    printf("\n");
    int count = CountList(root);
    Solve(root, count);
    PrintList(root);
}