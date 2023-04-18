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

    FILE* written = fopen("result.bin", "rb");
    student* s = (student*)malloc(sizeof(student));
    int sum1, sum2, sum3;
    while (fread(s, sizeof(student), 1, written) == 1) {
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        for (int m = 0; m < 3; ++m) {
            if (s->russian[m] != '\0') {
                sum1 = sum1 * 10 + (s->russian[m] - '0');
            }
            if (s->maths[m] != '\0') {
                sum2 = sum2 * 10 + (s->maths[m] - '0');
            }
            if (s->informatics[m] != '\0') {
                sum3 = sum3 * 10 + (s->informatics[m] - '0');
            }
        }
        if (((sum1 + sum2 + sum3) >= p1) && ((sum1 + sum2 + sum3) <= p2)) {
            printf("%s", s->name);
            printf(";");
            printf("%s", s->midname);
            printf(";");
            printf("%s", s->surname);
            printf(";");
            printf("%c", s->gender[0]);
            printf(";");
            printf("%s", s->scholnumb);
            printf(";");
            printf("%c", s->medal[0]);
            printf(";");
            printf("%s", s->russian);
            printf(";");
            printf("%s", s->maths);
            printf(";");
            printf("%s", s->informatics);
            printf(";");
            printf("%c\n",s->essay[0]);
        }
    }
    return 0;
}