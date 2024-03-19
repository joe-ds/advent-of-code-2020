#include <stdio.h>
#include <stdlib.h>

int sum_and_zero(int* n) {
    int sum = 0;
    for (int i=0; i < 26; i++) {
        sum += n[i];
        n[i] &= 0;
    }
    return sum;
}

void part_one(FILE* fp) {
    int chars_read;
    char *buf = NULL;
    size_t len = 0;
    int qs[26] = {0};
    int count = 0;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        if (buf[0] == '\n') {
            count += sum_and_zero(qs);
        }
        else {
            for (int i=0; i < chars_read; i++) {
                if (buf[i] >= 97 && buf[i] <= 122) {
                    qs[buf[i] - 97] |= 1;
                }
           }
        }
    }
    count += sum_and_zero(qs);
    printf("Part one completed. The answer is %d.\n", count);
}

int all_sum_and_zero(int* n, int people) {
    int sum = 0;
    for (int i=0; i < 26; i++) {
        if (n[i] == people) {
            sum++;
        }
        n[i] &= 0;
    }
    return sum;
}

void part_two(FILE* fp) {
    int chars_read;
    char *buf = NULL;
    size_t len = 0;
    int qs[26] = {0};
    int count = 0;
    int people = 0;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        if (buf[0] == '\n') {
            count += all_sum_and_zero(qs, people);
            people = 0;
        }
        else {
            people++;
            for (int i=0; i < chars_read; i++) {
                if (buf[i] >= 97 && buf[i] <= 122) {
                    qs[buf[i] - 97] += 1;
                }
           }
        }
    }
    count += all_sum_and_zero(qs, people);
    printf("Part two completed. The answer is %d.\n", count);
}

int main(void) {
    FILE* fp;

    fp = fopen("input", "r");

    if (fp == NULL) {
        printf("Failed to read file.\n");
        exit(EXIT_FAILURE);
    }

    part_one(fp);
    rewind(fp);
    part_two(fp);

    fclose(fp);
    exit(EXIT_SUCCESS);
}