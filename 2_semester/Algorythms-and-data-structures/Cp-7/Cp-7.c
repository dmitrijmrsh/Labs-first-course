#include <stdio.h>

int Abs(int a) {
    return (a >= 0) ? a : -a;
}

int main() {
    int n, m;
    printf("Enter the matrix size: ");
    scanf("%d %d", &n, &m);
    printf("\n");
    int matrix[n][m];
    int matrixans[n][m];
    int nonullcount = 0;
    int nonullrowcount = 0;
    printf("Enter the matrix elements: \n");
    for (int i = 0; i < n; ++i) {
        int flag = 0;
        for (int j = 0; j < m; ++j) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] != 0) {
                ++nonullcount;
                flag = 1;
            }
        }
        if (flag) {
            ++nonullrowcount;
        }
    }
    int row = nonullcount + nonullrowcount + 1;
    printf("The matrix is\n");
    int vector[row][2];
    int vectorans[row][2];
    int index = 0;
    for (int i = 0; i < n; ++i) {
        int flaginput = 0;
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] != 0) {
                if (index == 0) {
                    vector[index][0] = 0;
                    vector[index][1] = i + 1;
                    ++index;
                    vector[index][0] = j + 1;
                    vector[index][1] = matrix[i][j];
                    ++index;
                    flaginput = 1;
                } else {
                    if (flaginput == 0) {
                        vector[index][1] = i + 1;
                        ++index;
                        vector[index][0] = j + 1;
                        vector[index][1] = matrix[i][j];
                        ++index;
                        flaginput = 1;
                    } else {
                        vector[index][0] = j + 1;
                        vector[index][1] = matrix[i][j];
                        ++index;
                    }
                }
            }
        }
        vector[index][0] = 0;
        vector[index][1] = 0;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < 2; ++j) {
            vectorans[i][j] = vector[i][j];
            printf("%d ", vector[i][j]);
        }
        printf("\n");
    }

    printf("Enter the value\n");
    int value;
    scanf("%d", &value);
    int mindiff, nulldiff, minvalue;
    nulldiff = Abs(0 - value);
    mindiff = nulldiff;
    minvalue = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (vector[i][0] != 0) {
                if (Abs(vector[i][1] - value) <= mindiff) {
                    mindiff = Abs(vector[i][1] - value);
                    minvalue = vector[i][1];
                }
            }
        }
    }
    printf("Min value is: %d\n", minvalue);

    for (int i = 0; i  < row; ++i) {
        int rowpos, columnpos;
        int flag2 = 0;
        if (vector[i][0] != 0) {
            if (vector[i][1] == minvalue) {
                columnpos = vector[i][0];
                int d = i - 1;
                while(!flag2) {
                    if (vector[d][0] == 0) {
                        rowpos = vector[d][1];
                        flag2 = 1;
                    }
                    --d;
                }
                for (int k = 0; k < row; ++k) {
                    if ((vectorans[k][0] == 0) && (vectorans[k][1] == rowpos)) {
                        int index2 = k + 1;
                        while (vectorans[index2][0] != 0) {
                            vectorans[index2][1] = vectorans[index2][1] / minvalue;
                            ++index2;
                        }
                    }
                    if (vectorans[k][0] == columnpos) {
                        vectorans[k][1] = vectorans[k][1] / minvalue;
                    }
                }
                for (int k = 0; k < row; ++k) {
                    if ((vectorans[k][0] == columnpos) && (vectorans[k][1] == 0)) {
                        vectorans[k][1] = 1;
                    }
                }
            }
        }
    }
    
    printf("The answer is\n");
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%d ", vectorans[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrixans[i][j] = 0;
        }
    }

    if ((vectorans[0][0] == 0) && (vectorans[0][1] == 0)) {
        printf("\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("0 ");
            }
            printf("\n");
        }
    } else {
        int countrow, index3 = 0;
        while (countrow != m) {
            if ((vectorans[index3][0] == 0) && (vectorans[index3][1]) != 0) {
                while (countrow != vectorans[index3][1] - 1) {
                    ++countrow;
                }
                ++index3;
            }
            if (vectorans[index3][0] != 0) {
                while(vectorans[index3][0] != 0) {
                    matrixans[countrow][vectorans[index3][0] - 1] = vectorans[index3][1];
                    ++index3;
                }
            }
            ++countrow;
        }

        printf("\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("%d ", matrixans[i][j]);
            }
            printf("\n");   
        }
    }
}