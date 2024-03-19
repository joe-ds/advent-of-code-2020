#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_char(char * password, char c) {
    int l = strnlen(password, 24);
    int count = 0;

    for (int i=0; i < l; i++) {
        if (password[i] == c) {
            count++;
        }
    }

    return count;
}

void part_1(FILE * fp) {
    int s, e;
    char c;
    char password[24] = {"0"};

    int count = 0;
    while (fscanf(fp, "%d-%d %c: %24s", &s, &e, &c, password) != EOF) {
        int r = count_char(password, c);
        if (r >= s && r <= e) {
            count++;
        }
    }
    printf("Answer to part 1: %d passwords valid.\n", count);
}

void part_2(FILE * fp) {
    int s, e;
    char c;
    char password[24] = {"0"};

    int count = 0;
    while (fscanf(fp, "%d-%d %c: %s", &s, &e, &c, password) != EOF) {
        s = s-1;
        e = e-1;
        if (password[s] == c || password[e] == c) {
            if (password[s] != password[e]) {
                count++;
            }
        }
    }
    printf("Answer to part 2: %d passwords valid.\n", count);
}

int main(void) {
    FILE *fp;

    if ((fp = fopen("input", "r")) == NULL) {
        exit(EXIT_FAILURE);
    }

    part_1(fp);
    rewind(fp);
    part_2(fp);

    fclose(fp);
    exit(EXIT_SUCCESS);
}