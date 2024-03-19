#include <stdio.h>
#include <stdlib.h>

int part_one(int * nums, int count) {
    for (int i=0; i < count; i++) {
        for (int j=0; j < count; j++) {
            if (i == j) {
                continue;
            }

            if (nums[i] + nums[j] == 2020) {
                printf("Found %d + %d = 2020\n", nums[i], nums[j]);
                printf("Answer to part one: %d\n", nums[i] * nums[j]);
                return 0;
            }
        }
    }
    printf("Could not find answer. :(\n");
    return 1;
}

int part_two(int * nums, int count) {
    for (int i=0; i < count; i++) {
        for (int j=0; j < count; j++) {
            for (int k=0; k < count; k++) {
                if (i == j || j == k || k == i) {
                    continue;
                } else {
                    if (nums[i] + nums[j] + nums[k] == 2020) {
                        printf("Found %d + %d + %d = 2020\n", nums[i], nums[j], nums[k]);
                        printf("Answer to part two: %d\n", nums[i] * nums[j] * nums[k]);
                        return 0;
                    }
                }
            }
        }
    }

    printf("Could not find answer. :(\n");
    return 1;
}

int main(void) {
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int nums[201];

    if ((fp = fopen("input", "r")) == NULL) {
        exit(EXIT_FAILURE);
    }

    int count = 0;
    while (fscanf(fp, "%d\n", &nums[count]) == 1) {
        count += 1;
    }

    fclose(fp);
    printf("%d integers read.\n\n", count);

    part_one(nums, count);
    printf("\n");
    part_two(nums, count);

    exit(EXIT_SUCCESS);
}