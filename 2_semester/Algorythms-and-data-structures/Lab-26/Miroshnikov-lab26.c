#include <stdio.h>
#include <malloc.h>

typedef struct list {
    int value;
    struct list *next;
    struct list *parent;
} node;

//Инициализация корня списка
node* Init(int value) {
    node* root = (node*) malloc(sizeof(node)); //Выделение памяти под корень списка
    root->value = value;
    root->next = NULL;
    root->parent = NULL;
    return root;
}

//Добавление узла в линейный список
node* Add(node* root, int value) {
    node* temp;
    temp = (node*) malloc(sizeof(node)); //Выделение памяти под узел
    while (root->next != NULL) {
        root = root->next;
    }
    root->next = temp;
    temp->value = value;
    temp->parent = root;
    temp->next = NULL;
    return temp;
}

//Удаление узла в списке
node* Delete(node* root, int value) {
    node* item;
    node* temp;
    temp = root;
    if (temp->value == value) {
        temp = temp->next;
    }
    //Пока след элемент не будет удаляемым идем к след. элементу
    while (temp->next->value != value) {
        temp = temp->next;
    }
    item = temp->next;
    if (item->next == NULL) {
        temp->next = NULL;
    } else {
        temp->next = item->next;
        item->next->parent = temp;
    }
    free(item);
    return temp;
}

//Вывод элементов списка
void PrintList(node* root) {
    node* p;
    p = root;
    while (p != NULL) {
        if (p->next != NULL) {
            printf("%d <-> ", p->value);
        } else {
            printf("%d", p->value);
        }
        p = p->next;
    }
}

//Число узлов двусвязного списка
int Count(node* root) {
    node* temp = root;
    int count = 1;
    while (temp->next != NULL) {
        count += 1;
        temp = temp->next;
    }
    return count;
}

//Преобоазование списка в массив
void ListToArray(node *root, int *mas, int count) {
    for (int i = 0; i < count; ++i) {
        mas[i] = root->value;
        root = root->next;
    }
}

//Сортировка
void BubbleSort(int *mas, int count) {
    for (int i = 0; i < count - 1; ++i)  {
        for (int j = 0; j < count - i - 1; ++j) {
            if (mas[j] > mas[j + 1]) {
                int temp = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = temp;
            }
        }
    }
}

//Преобразование массива в список
void ArrayToList(node *root, int *mas, int count) {
    for (int i = 0; i < count; ++i) {
        root->value = mas[i];
        root = root->next;
    }
}

int main() {
    node* root = NULL;
    int flag = 1;
    printf("1. Create root, 2. Add node, 3. Delete node, 4. Bubble Sort, 5. Print List, 0. Quit\n");
    while (flag) {
        int variant, value;
        printf("Enter the variant\n");
        scanf("%d", &variant);
       if (variant == 1) {
            printf("Enter root value\n");
            scanf("%d", &value);
            root = Init(value);
       } else if (variant == 2) {
            printf("Add node value\n");
            scanf("%d", &value);
            if (root == NULL) {
                printf("List is empty\n");
            } else {
                Add(root, value);
            }
       } else if (variant == 3) {
            printf("Add node value\n");
            scanf("%d", &value);
            if (root == NULL) {
                printf("Tree is empty\n");
            } else {
                Delete(root, value);
            }
       } else if (variant == 4) {
            int count = Count(root);
            int mas[count];
            ListToArray(root, mas, count);
            BubbleSort(mas, count);
            ArrayToList(root, mas, count);
            printf("Bubble Sort completed\n");
       } else if (variant == 5) {
            PrintList(root);
            printf("\n");
       } else if (variant == 0) {
            printf("Work finished\n");
            flag = 0;
       }
    }
    return 0;
}