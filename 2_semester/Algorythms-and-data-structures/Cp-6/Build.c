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

int main() {
    FILE* file = fopen("test1.csv", "r");
    FILE* out = fopen("result.bin","wb");
    char str[255];
    int stringnumber = 0;
    while(fgets(str, 255, file)) {
        int column = 0;
        ++stringnumber;
        if (stringnumber == 1) {
            continue;
        } else {
            student* s = (student*)malloc(sizeof(student));
            int index = 0;
            for (int i = 0; i < 255; ++i) {
                if (str[i] == '\n') {
                    break;
                } else if (str[i] == ';') {
                    ++column;
                    index = 0;
                    continue;
                } else if (column == 0) {
                    s->name[index] = str[i];
                    if (index + 1 != 50) {
                        s->name[index+1] = '\0';
                    }
                } else if (column == 1) {
                    s->midname[index] = str[i];
                    if (index + 1 != 50) {
                        s->midname[index+1] = '\0';
                    }
                } else if (column == 2) {
                    s->surname[index] = str[i];
                    if (index + 1 != 50) {
                        s->surname[index+1] = '\0';
                    }
                } else if (column == 3) {
                    s->gender[index] = str[i];
                } else if (column == 4) {
                    s->scholnumb[index] = str[i];
                    if (index + 1 != 5) {
                        s->scholnumb[index+1] = '\0';
                    }
                } else if (column == 5) {
                    s->medal[index] = str[i];
                } else if (column == 6) {
                    s->russian[index] = str[i];
                    if (index + 1 != 3) {
                        s->russian[index+1] = '\0';
                    }
                } else if (column == 7) {
                    s->maths[index] = str[i];
                    if (index + 1 != 3) {
                        s->maths[index+1] = '\0';
                    }
                } else if (column == 8) {
                    s->informatics[index] = str[i];
                    if (index + 1 != 3) {
                        s->informatics[index+1] = '\0';
                    }
                } else if (column == 9) {
                    s->essay[index] = str[i];
                    break;
                }
                ++index;
            }
            fwrite(s, sizeof(student), 1, out);
        }
    }
    fclose(file);
    fclose(out);
    return 0;
}