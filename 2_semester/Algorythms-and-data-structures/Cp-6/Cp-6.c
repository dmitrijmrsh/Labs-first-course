#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    char midname[50];
    char surname[50];
    char gender[1];
    char scholnumb[5];
    char medal[1];
    char russian[3];
    char maths[3];
    char informatics[3];
    char essay[1];
} student;

int main(int argc, char* argv[]) {
    int p1 = atoi(argv[1]);
    int p2 = atoi(argv[2]);

    FILE* file = fopen("test3.csv", "r");
    FILE* out = fopen("result.bin","wb");
    char str[255];
    int stringnumber = 0;
    while(fgets(str, 255, file)) {
        int column = 0;
        ++stringnumber;
        if (stringnumber == 1) {
            continue;
        }
        student* s = (student*)malloc(sizeof(student));
        for (int m = 0; m < 50; ++m) {
            s->name[m] = '*';
            s->midname[m] = '*';
            s->surname[m] = '*';
        }
        for (int m = 0; m < 5; ++m) {
            s->scholnumb[m] = '*';
        }
        for (int m = 0; m < 3; ++m) {
            s->russian[m] = '*';
            s->maths[m] = '*';
            s->informatics[m] = '*';
        }
        int index = 0;
        for (int i = 0; i < 255; ++i) {
            if (str[i] == '\n') {
                break;
            }
            if (str[i] == ';') {
                ++column;
                index = 0;
                continue;
            }
            if (column == 0) {
                s->name[index] = str[i];
            }
            if (column == 1) {
                s->midname[index] = str[i];
            }
            if (column == 2) {
                s->surname[index] = str[i];
            }
            if (column == 3) {
                s->gender[index] = str[i];
            }
            if (column == 4) {
                s->scholnumb[index] = str[i];
            }
            if (column == 5) {
                s->medal[index] = str[i];
            }
            if (column == 6) {
                s->russian[index] = str[i];
            }
            if (column == 7) {
                s->maths[index] = str[i];
            }
            if (column == 8) {
                s->informatics[index] = str[i];
            }
            if (column == 9) {
                s->essay[index] = str[i];
                break;
            }
            ++index;
        }
        fwrite(s, sizeof(student), 1, out);
    }
    fclose(file);
    fclose(out);
    FILE* written = fopen("result.bin", "rb");
    student* s = (student*)malloc(sizeof(student));
    int sum1, sum2, sum3;
    while (fread(s, sizeof(student), 1, written) == 1) {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        for (int m = 0; m < 3; ++m) {
            if (s->russian[m] != '*') {
                sum1 = sum1 * 10 + (s->russian[m] - '0');
            }
            if (s->maths[m] != '*') {
                sum2 = sum2 * 10 + (s->maths[m] - '0');
            }
            if (s->informatics[m] != '*') {
                sum3 = sum3 * 10 + (s->informatics[m] - '0');
            }
        }
        if (((sum1 + sum2 + sum3) >= p1) && ((sum1 + sum2 + sum3) <= p2)) {
            for (int k = 0; k < 50; ++k) {
                if (s->name[k] != '*') {
                    printf("%c", s->name[k]);
                }
            }
            printf(";");
            for (int k = 0; k < 50; ++k) {
                if (s->midname[k] != '*') {
                    printf("%c", s->midname[k]);
                }
            }
            printf(";");
            for (int k = 0; k < 50; ++k) {
                if (s->surname[k] != '*') {
                    printf("%c", s->surname[k]);
                }
            }
            printf(";");
            printf("%c", s->gender[0]);
            printf(";");
            for (int k = 0; k < 5; ++k) {
                if (s->scholnumb[k] != '*') {
                    printf("%c", s->scholnumb[k]);
                }
            }
            printf(";");
            printf("%c", s->medal[0]);
            printf(";");
            for (int k = 0; k < 3; ++k) {
                if (s->russian[k] != '*') {
                    printf("%c", s->russian[k]);
                }
            }
            printf(";");
            for (int k = 0; k < 3; ++k) {
                if (s->maths[k] != '*') {
                    printf("%c", s->maths[k]);
                }
            }
            printf(";");
            for (int k = 0; k < 3; ++k) {
                if (s->informatics[k] != '*') {
                    printf("%c", s->informatics[k]);
                }
            }
            printf(";");
            printf("%c",s->essay[0]);
            printf("\n");
        }
    }
    return 0;
}