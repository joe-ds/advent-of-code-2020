#include <stdio.h>
#include <stdlib.h>

void part_one(FILE *fp) {
    int index = 0;
    char* line = NULL;
    size_t n = 0;
    int tree_count = 0;

    // We don't want the first line.
    getline(&line, &n, fp);

    while((getline(&line, &n, fp)) != -1) {
        index = (index + 3) % 31;
        if (line[index] == '#') {
            tree_count++;
        }
    }

    printf("Part One completed. Found %d trees in path.\n", tree_count);
}

void part_two(FILE *fp) {
    int line_length = 31;
    int slope[5] = {0};
    int lc = 0;

    char* line = NULL;
    size_t n = 0;
    int tree_count[5] = {0};

    // We don't want the first line.
    getline(&line, &n, fp);

    while((getline(&line, &n, fp)) != -1) {
        lc++;

        slope[0] = (slope[0] + 1) % line_length;
        slope[1] = (slope[1] + 3) % line_length;
        slope[2] = (slope[2] + 5) % line_length;
        slope[3] = (slope[3] + 7) % line_length;

        if ((lc % 2) == 0) {
            slope[4] = (slope[4] + 1) % line_length;
            if (line[slope[4]] == '#') {
                tree_count[4] += 1;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (line[slope[i]] == '#') {
                tree_count[i] += 1;
            }
        }
    }

    unsigned long int answer = 1;
    for (int i = 0; i < 5; i++) {
        answer = answer * tree_count[i];
    }

    // Try to use %d here. (^_^)
    printf("Part Two completed. Answer: %lu.\n", answer);
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