#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "tree.h"

int main() {
    node* root_base = NULL;
    node *root_refl = NULL;
    int flag = 1;
    while (flag) {
        printf("1. Create root, 2. Add node, 3. Delete node, 4. Check, 5. Print tree, 0. Quit\n");
        int variant, value;
        scanf("%d", &variant);
        switch(variant) {
            case 1:
                printf("Enter root value\n");
                scanf("%d", &value);
                root_base = Create(value);
                root_refl = Create(value);
                break;
            case 2:
                printf("Enter node value\n");
                scanf("%d", &value);
                if (root_base == NULL) {
                    printf("Tree is empty\n");
                } else {
                    Add(root_base, value);
                    Add_Refl(root_refl, value);
                }
                break;
            case 3:
                printf("Enter value\n");
                scanf("%d", value);
                if (root_base == NULL) {
                    printf("Tree is empty\n");
                } else if (value != root_base->value) {
                    Delete(root_base, value);
                    Delete_Refl(root_refl, value);
                } else {
                    printf("You can't delete the root :(");
                }
                break;
            case 4:
                if (Check(root_base, root_refl)) {
                    printf("YES\n");
                } else {
                    Check(root_base, root_refl);
                }
                break;
            case 5:
                if (root_base == NULL) {
                    printf("Tree is empty\n");
                } else {
                    Tree_Print(root_base);
                }
                break;
            case 0:
                flag = 0;
                break;
        }
    }
    return 0;
}