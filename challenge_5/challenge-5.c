#include <stdio.h>
#include <stdlib.h>

void part_one(FILE* fp) {
    int chars_read = 0;
    char *buf = NULL;
    size_t len = 0;
    int row = 0;
    int col = 0;
    int highest = 0;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        for (int i=0; i < 7; i++) {
            row <<= 1;
            row |= (buf[i] == 'B');
        }

        for (int i= 7; i < 10; i++) {
            col <<= 1;
            col |= (buf[i] == 'R');
        }
        if ((row * 8 + col) > highest) {
            highest = row * 8 + col;
        }
        row = 0;
        col = 0;
    }
    printf("Part one completed. The highest ID is %d.\n", highest);
}

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int cmp_int(const void* a, const void* b) {
    return *(int *) a - *(int *) b;
}

void part_two(FILE* fp) {
    int chars_read = 0;
    char *buf = NULL;
    size_t len = 0;
    int row = 0;
    int col = 0;
    int ids[782] = {0};
    int count = 0;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        for (int i=0; i < 7; i++) {
            row <<= 1;
            row |= (buf[i] == 'B');
        }

        for (int i= 7; i < 10; i++) {
            col <<= 1;
            col |= (buf[i] == 'R');
        }
        ids[count] = row * 8 + col; 
        count++;
        row = 0;
        col = 0;
    }
    qsort(ids, sizeof(ids)/sizeof(*ids), sizeof(*ids), cmp_int);

    for (int i=1; i<782; i++) {
        if (ids[i-1] != ids[i] - 1) {
            printf("Part two completed. Your seat ID is %d.\n", ids[i] - 1);
        }
    }
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