#include <stdio.h>
#include <stdlib.h>

int count_lines(FILE *fp) {
    int x;
    int count = 0;
    while (fscanf(fp, "%d", &x) != EOF) {
        count++;
    }
    rewind(fp);
    return count;
}

int cmp_int(const void* a, const void* b) {
    return *(int *) a - *(int *) b;
}

void part_one(FILE *fp) {
    int *list = malloc(count_lines(fp) * sizeof(int));

    int line = 0;
    while (fscanf(fp, "%d", &list[line]) != EOF) {
        line++;
    }

    qsort(list, line, sizeof(int), cmp_int);

    long int one_j = 0;
    long int three_j = 1;
    int last = 0;

    for (int i = 0; i < line; i++) {
        int c = list[i] - last;

        switch (c) {
            case 0:
                last = list[i];
                break;
            case 1:
                one_j++;
                last = list[i];
                break;
            case 2:
                printf("==:: Assumption that there are no gaps of length 2 false. ::==\n");
                last = list[i];
                break;
            case 3:
                three_j++;
                last = list[i];
                break;
            default:
                i = line;
        }
    }

    printf("Part one completed. The answer is %li.\n", one_j * three_j);
}

// This part was a bit harder. A sequence suggested itself, but it needed
// looking at discussions to find that the sequence is the Tribonacci sequence.
// Credit to LieutenantSwr2d2 on Reddit for his illuminating comment.
// It was observed there's only gaps of 1 and 3, so continuous runs, or a jump
// of 3, which means that only the last number in a run can connect.
// Then, when the smaller example given is looked at, we can see something interesting:
// [16, 10, 15, 5, 1, 11, 7, 19, 6, 12, 4]
// Sorted, the list is:
// [1, 4, 5, 6, 7, 10, 11, 12, 15, 16, 19]
// We can see in the first run, [4, 5, 6, 7], only 4 and 7 are 'needed'.
// This means the possibilities are four: [4, 7], [4, 5, 7], [4, 6, 7] and
// [4, 5, 6, 7]. Looking at the other runs of length 3, 4, 5, and 6 we can see
// they all produce combinations of 2, 4, 5, 13, etc.
// This sequence is the Tribonacci sequence, which is just like the Fibonacci,
// but with three numbers.

void part_two(FILE *fp) {
    int *list = malloc((count_lines(fp) + 2) * sizeof(int));

    list[0] = 0;
    int line = 1;
    while (fscanf(fp, "%d", &list[line]) != EOF) {
        line++;
    }
    list[line+1] = list[line] + 3;
    line++;

    qsort(list, line, sizeof(int), cmp_int);

    long long unsigned int combo = 1;
    int run = 0;
    const int tribonacci[19] = {1, 1, 2, 4, 7, 13, 24, 44, 81, 149, 274, 504, 927, 1705, 3136, 5768, 10609, 19513, 35890};

    for (int i=0; i < line; i++) {
        if (list[i] == list[i+1] - 1) {
            run++;
        } else {
            combo *= tribonacci[run];
            run = 0;
        }
    }

    printf("Part two completed. The answer is %llu.\n", combo);
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