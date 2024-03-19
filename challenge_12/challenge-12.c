#include <stdio.h>
#include <stdlib.h>

void part_one(FILE *fp) {
    char four_ways[5] = "ESWN";
    char d; int m;
    int direction = 0;
    int md[2] = {0};

    while (fscanf(fp, "%c%d ", &d, &m) != EOF) {
        if (d == 'F') {
            d = four_ways[direction];
        }

        switch (d) {
            case 'N':
                md[0] += m;
                break;
            case 'S':
                md[0] -= m;
                break;
            case 'E':
                md[1] += m;
                break;
            case 'W':
                md[1] -= m;
                break;
            case 'R':
                direction = (direction + (m / 90)) % 4;
                break;
            case 'L':
                direction = (direction + (4 - (m / 90))) % 4;
                break;
            default:
                printf("Parse error! Invalid entry: %c%d.\n", d, m);
        }
    }
    printf("Part one is finished. The distance is %d.\n", abs(md[0] + md[1]));
}

void part_two(FILE *fp) {
    char d; int m;
    long signed int md[2] = {0};
    long signed int waypoint[2] = {10, 1};

    while (fscanf(fp, "%c%d ", &d, &m) != EOF) {
        switch (d) {
            case 'N':
                waypoint[1] += m;
                break;
            case 'S':
                waypoint[1] -= m;
                break;
            case 'E':
                waypoint[0] += m;
                break;
            case 'W':
                waypoint[0] -= m;
                break;
            case 'L':
                m = 360 - m;
            case 'R':
                for (int i = 0; i < (m / 90); i++) {
                    waypoint[0] = waypoint[0] ^ waypoint[1];
                    waypoint[1] = waypoint[0] ^ waypoint[1];
                    waypoint[0] = waypoint[0] ^ waypoint[1];
                    waypoint[1] *= -1;
                }
                break;
            case 'F':
                md[0] += m * waypoint[0];
                md[1] += m * waypoint[1];
                break;
            default:
                printf("Parse error! Invalid entry: %c%d.\n", d, m);
        }
    }
    printf("Part two is finished. The distance is %li.\n", labs(md[0]) + labs(md[1]));
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