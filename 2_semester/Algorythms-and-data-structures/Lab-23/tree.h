#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} node;

node *Create(int value) {
    node *root = (node *) malloc(sizeof(node)); //Выделение памяти под корень дерева
    root->value = value; //Присваивание значения ключу
    root->parent = NULL; //Присваивание указателю на родителя значения NULL
    root->left = root->right = NULL; //Присваивание указателю на левое и правое поддерево значен
    return root;
}

//Добавление узла в дерево
node *Add(node *root, int value) {
    node *root2 = root; // Указатель для сохранения родителя вставляемого узла
    node *root3 = NULL;
    node *temp = (node*)malloc(sizeof(node)); //Выделение памяти под узел дерева
    temp->value = value; //Присваивание значения ключу
    //Поиск нужной позиции для вставки
    while (root2 != NULL) {
        root3 = root2;
        if (value < root2->value) {
            root2 = root2->left;
        } else {
            root2 = root2->right;
        }
    }
    temp->parent = root3;
    temp->left = NULL;
    temp->right = NULL;
    if (value < root3->value) {
        root3->left = temp;
    } else {
        root3->right = temp;
    }
    return root;
}

//Добавление узла в  отражённое дерево
node *Add_Refl(node *root, int value) {
    node *root2 = root;
    node *root3 = NULL;
    node *temp = (node*)malloc(sizeof(node));
    temp->value = value;
    //Поиск нужной позиции для вставки
    while (root2 != NULL) {
        root3 = root2;
        if (value >= root2->value) {
            root2 = root2->left;
        } else {
            root2 = root2->right;
        }
    }
    temp->parent = root3;
    temp->left = NULL;
    temp->right = NULL;
    if (value >= root3->value) {
        root3->left = temp;
    } else {
        root3->right = temp;
    }
    return root;
}

//Поиск заданного узла
node *Search(node *root, int value) {
    if ((root == NULL) || (root->value == value)) {
        return root;
    }
    if (value < root->value) {
        return Search(root->left, value);
    } else {
        return Search(root->right, value);
    }
}

//Поиск заданного узла у отражённого дерева
node *Search_Refl(node *root, int value) {
    if ((root == NULL) || (root->value == value)) {
        return root;
    }
    if (value < root->value) {
        return Search_Refl(root->right, value);
    } else {
        return Search_Refl(root->left, value);
    }
}

//Минимальный элемент дерева
node *Min(node *root) {
    node *l = root;
    while (l->left != NULL) {
        l = l->left;
    }
    return l;
}

//Минимальный элемент отражённого дерева
node *Min_Refl(node *root) {
    node *l = root;
    while (l->right != NULL) {
        l = l->right;
    }
    return l;
}

//Поиск следующего эл-та по значению за удаляемым(случай когда у узла два поддерева)
node *Succ(node *root) {
    node *p = root;
    if (p->right != NULL) {
        return Min(p->right);
    }
}

//Поиск следующего эл-та по значению за удаляемым в отражённом дереве
node *Succ_Refl(node *root) {
    node *p = root;
    if (p->left != NULL) {
        return Min_Refl(p->left);
    }
}

//Удаление узла
node *Delete(node *root, int value) {
    node *p = root;
    node *l = NULL;
    node *m = NULL;
    l = Search(root, value);
    //1 случай (нет поддеревьев)
    if ((l->left == NULL) && (l->right == NULL)) {
        m = l->parent;
        if (l == m->right) {
            m->right = NULL;
        } else {
            m->left = NULL;
        }
        free(l);
        return root;
    }
    //2 случай, вар 1 (поддерево справа)
    if ((l->left == NULL) && (l->right != NULL)) {
        m = l->parent;
        if (l == m->right) {
            m->right = l->right;
        } else {
            m->left = l->right;
        }
        free(l);
        return root;
    }
    //2 случай, вар 2 (поддерево слева)
    if ((l->left != NULL) && (l->right == NULL)) {
        m = l->parent;
        if (l = m->right) {
            m->right = l->left;
        } else {
            m->left = l->left;
        }
        free(l);
        return root;
    }
    //3 случай (2 поддерева)
    if ((l->left != NULL) && (l->right != NULL)) {
        m = Succ(l);
        l->value = m->value;
        if (m->right == NULL) {
            m->parent->left = NULL;
        } else {
            m->parent->left = m->right;
        }
        free(m);
        return root;
    }
}

//Удаление узла отражённого дерева
node *Delete_Refl(node *root, int value) {
    node *p = root;
    node *l = NULL;
    node *m = NULL;
    l = Search_Refl(root, value);
    //1 случай (нет поддеревьев)
    if ((l->left == NULL) && (l->right == NULL)) {
        m = l->parent;
        if (l == m->right) {
            m->right = NULL;
        } else {
            m->left = NULL;
        }
        free(l);
        return root;
    }
    //2 случай, вар 1 (поддерево справа)
    if ((l->left == NULL) && (l->right != NULL)) {
        m = l->parent;
        if (l == m->right) {
            m->right = l->right;
        } else {
            m->left = l->right;
        }
        free(l);
        return root;
    }
    //2 случай, вар 2 (поддерево слева)
    if ((l->left != NULL) && (l->right == NULL)) {
        m = l->parent;
        if (l = m->right) {
            m->right = l->left;
        } else {
            m->left = l->left;
        }
        free(l);
        return root;
    }
    //3 случай (2 поддерева)
    if ((l->left != NULL) && (l->right != NULL)) {
        m = Succ_Refl(l);
        l->value = m->value;
        if (m->left == NULL) {
            m->parent->right = NULL;
        } else {
            m->parent->right = m->left;
        }
        free(m);
        return root;
    }
}

//Текстовая визуализация дерева
void Tree_Vis(node *root, int count) {
    if (root != NULL) {
        for (int i = 0; i < count; ++i) {
            printf("|");
        }
    }
    printf("%d\n", root->value);
    if (root->left != NULL) {
        Tree_Vis(root->left, count + 1);
    }
    if (root->right != NULL) {
        Tree_Vis(root->right, count + 1);
    }
}

//Вывод визуализированного дерева
void Tree_Print(node *root) {
    Tree_Vis(root, 0);
}

//Проверка дерева на самоподобие(подобие своему отражению)
int Check(node *root_base, node *root_refl) {
    if ((root_base == NULL) && (root_refl == NULL)) {
        return 1;
    } else {
    if (((root_base->left == NULL) && (root_refl->left != NULL)) || ((root_base->left != NULL) && (root_refl->left == NULL)) || ((root_base->right == NULL) && (root_refl->right != NULL)) || ((root_base->right != NULL) && (root_refl->right == NULL))) {
        printf("NO\n");
        exit(0);       
    }
    if ((root_base->left != NULL) && (root_refl->left != NULL)) {
        Check(root_base->left, root_refl->left);
    }
    if ((root_base->right != NULL) && (root_refl->right != NULL)) {
        Check(root_base->right, root_refl->right);
    }
    return 1;
    }
}