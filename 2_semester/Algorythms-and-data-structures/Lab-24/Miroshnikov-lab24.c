#include <stdio.h>
#include <malloc.h>
#define NMAX 100

typedef struct stack {
    char elem[NMAX];
    int top;  
} block;

//Инициализация стэка
void InitStack(block* stk) {
    stk->top = 0;
}

//Добавление элемента в стэк
void PushStack(block* stk, char value) {
    if (stk->top < NMAX) {
        stk->elem[stk->top] = value;
        stk->top++;
    } else {
        printf("Stack overflow!!!\n");
    }
}

//Удаление элемента из стэка
char PopStack(block* stk) {
    char elem;
    if ((stk->top) > 0) {
        stk->top--;
        elem = stk->elem[stk->top];
        return elem;
    } else {
        printf("Stack is empty\n");
        return 0;
    }
}

//Обращение к верхнему элементу стэка
char StackTop(block* stk) {
    if ((stk->top) > 0) {
        return stk->elem[stk->top-1];
    } else {
        return 0;
    }
}

//Провекра стэка на пустоту
int StackIsEmpty(block* stk) {
    if (stk->top == 0) {
        return 1;
    } else {
        return 0;
    }
}

//Вывод элементов стэка
void StackPrint(block* stk) {
    int i;
    i = stk->top;
    if(StackIsEmpty(stk) == 1) {
        return;
    }
    while (i > 0) {
        --i;
        printf("%c ", stk->elem[i]);
    }
}

//Структура узла списка
typedef struct list {
    char value;
    struct list *next;
    struct list *parent;
} node;

//Инициализация списка
node* InitList(char value) {
    node* root = (node*)malloc(sizeof(node));
    root->value = value;
    root->next = NULL;
    root->parent = NULL;
    return root;
}

//Добавление элемента в список
node* AddList(node* root, char value) {
    node* temp;
    temp = (node*)malloc(sizeof(node));
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
node* DeleteList(node* root, char value) {
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
        printf("%c", p ->value);
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
void ListToArray(node *root, char *mas, int count) {
    for (int i = 0; i < count; ++i) {
        mas[i] = root->value;
        root = root->next;
    }
}

typedef struct tree {
    char value;
    struct tree* left;
    struct tree* right;
    struct tree* parent; 
} node_tree;

node_tree* CreateTree(char value) {
    node_tree* root_tree = (node_tree*)malloc(sizeof(node_tree));
    root_tree->value = value;
    root_tree->parent = NULL;
    root_tree->left = root_tree->right = NULL;
    return root_tree;
}

void Tree_Vis(node_tree *root, int count) {
    if (root != NULL) {
        for (int i = 0; i < count; ++i) {
            printf("|");
        }
    }
    printf("%c\n", root->value);
    if (root->left != NULL) {
        Tree_Vis(root->left, count + 1);
    }
    if (root->right != NULL) {
        Tree_Vis(root->right, count + 1);
    }
}

void Tree_Print(node_tree *root) {
    Tree_Vis(root, 0);
}

typedef struct stakc_node {
    node_tree* elem[NMAX];
    int top;
} block_node;

void InitStackNode(block_node* stk) {
    stk->top = 0;
}

void PushStackNode(block_node* stk, node_tree* node) {
    if (stk->top < NMAX) {
        stk->elem[stk->top] = node;
        stk->top++;
    } else {
        printf("Stack overflow!!!\n");
    }
}

node_tree* PopStackNode(block_node* stk) {
    node_tree* elem;
    if ((stk->top) > 0) {
        stk->top--;
        elem = stk->elem[stk->top];
        return elem;
    } else {
        printf("Stack is empty\n");
        return NULL;
    }
}

node_tree* StackTopNode(block_node* stk) {
    if ((stk->top) > 0) {
        return stk->elem[stk->top-1];
    } else {
        return NULL;
    }
}

int IsOperator(char a) {
    if ((a == '+') || (a == '-') || (a == '*') || (a == '/') || (a == '^') || (a == '?')) {
        return 1;
    }
    return 0;
}

int IsDigit(char a) {
    if ((a == '1') || (a == '2') || (a == '3') || (a == '4') || (a == '5') || (a == '6') || (a == '7') || (a == '8') || (a == '9') || (a == '0')) {
        return 1;
    }
    return 0;
}

void TreeToInfix(node_tree* root) {
    if (root == NULL) {
        return;
    }
    if (IsOperator(root->value)) {
        printf("(");
    }
    TreeToInfix(root->left);
    printf("%c", root->value);
    TreeToInfix(root->right);
    if (IsOperator(root->value)) {
        printf(")");
    }
}

//Построение дерева выражений
node_tree* Construct(int count, block_node* stk, char *mas) {
    if (count - 1 == 0) {
        return NULL;
    }
    for (int i = 0; i < count; ++i) {
        if (IsOperator(mas[i])) {
            node_tree* node = NULL;
            node_tree* x = StackTopNode(stk);
            PopStackNode(stk);
            node_tree* y = StackTopNode(stk);
            PopStackNode(stk);
            node = CreateTree(mas[i]);
            node->left = y;
            node->right = x;
            PushStackNode(stk, node);
        } else {
            node_tree* node = NULL;
            node = CreateTree(mas[i]);
            node->value = mas[i];
            PushStackNode(stk, node);
        }
    }
    return StackTopNode(stk);
}

void Solve(node_tree* root) {
    if (root == NULL) {
        return;
    }
    Solve(root->left);
    Solve(root->right);
    if (IsOperator(root->value)) {
        if (root->left->value == '*') {
        if (root->left->left->value == '1') {
            root->left->left = NULL;
            root->left = root->left->right;
        } else {
                if (root->left->right->value == '1') {
                    root->left->right = NULL;
                    root->left = root->left->left;
                }
            }
        }
        if (root->right->value == '*') {
            if (root->right->left->value == '1') {
                root->right->left = NULL;
                root->right = root->right->right;
            } else {
                if (root->right->right->value == '1') {
                    root->right->right == NULL;
                    root->right = root->right->left;
                }
            }
        }
    }
}

int main() {
    node* root = NULL;
    block* stk1 = (block*)malloc(sizeof(block));
    InitStack(stk1);
    char a = 0;
    int flag = 1;
    while(flag) {
        a = getchar();
        if (a == '\n') {
            if (StackIsEmpty(stk1) != 1) {
                AddList(root, StackTop(stk1));
                PopStack(stk1);
            }
            flag = 0;
        } else {
            if ((a == '0') || (a == '1') || (a == '2') || (a == '3') || (a == '4') || (a == '5') || (a == '6') || (a == '7') || (a == '8') || (a == '9')) {
                if (root == NULL) {
                    root = InitList(a);
                } else {
                    AddList(root, a);
                }
            } else {
                if (a == ')') {
                    while (StackTop(stk1) != '(') {
                        AddList(root, StackTop(stk1));
                        PopStack(stk1);
                    }
                    PopStack(stk1);
                }
                if (((a == '*') || (a == '/') || (a == '^') || (a == '('))) {
                    PushStack(stk1, a);
                }
                if ((a == '+') || (a == '-')) {
                    while (((StackTop(stk1) == '*') || (StackTop(stk1) == '/') || (StackTop(stk1) == '^')) && (StackIsEmpty(stk1) != 1)) {
                        AddList(root, StackTop(stk1));
                        PopStack(stk1);
                    }
                    PushStack(stk1, a);
                }
            }
        }
    }
    int count = Count(root);
    char mas[count];
    ListToArray(root, mas, count);
    PrintList(root);
    printf("\n");
    block_node* stk2 = (block_node*)malloc(sizeof(block_node));
    InitStackNode(stk2);
    Construct(count, stk2, mas);
    node_tree* root_tree = StackTopNode(stk2);
    node_tree* l = NULL;
    Tree_Print(root_tree);
    printf("\n");
    if ((root_tree->value == '*') && (root_tree->left->value == '1')) {
        root_tree->left = NULL;
        root_tree = root_tree->right;
    } else if ((root_tree->value == '*') && (root_tree->right->value == '1')) {
        root_tree->right = NULL;
        root_tree = root_tree->left;
    }
    Solve(root_tree);
    Tree_Print(root_tree);
    printf("\n");
    TreeToInfix(root_tree);
    return 0;
}