#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PREAMBLE_SIZE 25

int check(long long unsigned int *last, long long unsigned int check) {
    for (int i=0; i < PREAMBLE_SIZE; i++) {
        for (int j=0; j < PREAMBLE_SIZE; j++) {
            if (i == j) {
                continue;
            } else {
                if ((last[i] + last[j]) == check) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void shift(long long unsigned int *last, long long unsigned int check) {
    for (int i=1; i < PREAMBLE_SIZE; i++) {
        last[i-1] = last[i];
    }
    last[PREAMBLE_SIZE - 1] = check;
}

void part_one(FILE *fp) {
    long long unsigned int last[PREAMBLE_SIZE] = {0};
    
    for (int i=0; i < PREAMBLE_SIZE; i++) {
        long long unsigned int x;
        if (fscanf(fp, "%llu", &x) == EOF) {
            printf("Error!\n");
            fclose(fp);
            exit(1);
        } else {
            last[i] = x;
        }
    }

    long long unsigned int next = 0;
    while (fscanf(fp, "%llu", &next) != EOF) {
        if (check(last, next)) {
            shift(last, next);
        } else {
            break;
        }
    }
    printf("Part one completed. Answer is %llu.\n", next);
}

void part_two(FILE *fp) {
    long long unsigned int last[PREAMBLE_SIZE] = {0};
    size_t line_count = PREAMBLE_SIZE;
    
    for (int i=0; i < PREAMBLE_SIZE; i++) {
        long long unsigned int x;
        if (fscanf(fp, "%llu", &x) == EOF) {
            printf("Error!\n");
            fclose(fp);
            exit(1);
        } else {
            last[i] = x;
        }
    }

    long long unsigned int next = 0;
    long long unsigned int weak = 0;
    int found = 0;
    while (fscanf(fp, "%llu", &next) != EOF) {
        line_count++;

        if (found) {
            continue;
        }

        if (check(last, next)) {
            shift(last, next);
        } else {
            found = 1;
            weak = next;
        }
    }

    long long unsigned int *ptr = malloc(line_count * sizeof(long long unsigned int));

    rewind(fp);
    long long unsigned int c = 0;
    int i = 0;
    while (fscanf(fp, "%llu", &c) != EOF) {
        ptr[i] = c;
        i++;
    }

    long long unsigned int max;
    long long unsigned int min;

    for (int i=0; i < line_count; i++) {
        max = 0;
        min = INT_MAX;
        long long unsigned int sum = 0;
        int j = i;
        while (j < line_count && sum <= weak) {
            long long unsigned int c = ptr[j];
            sum += c;
            if (c > max) {
                max = c;
            }
            if (c < min) {
                min = c;
            }
            
            if (sum == weak) {
                i = line_count;
                break;
            }
            j++;
        }
    }
    free(ptr);
    printf("Part two complete. The answer is %llu.\n", max + min);
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