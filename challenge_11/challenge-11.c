#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_seats(int *seats, int row_len, int rows) {
    int count = 0;
    for (int i=0; i < row_len * rows; i++) {
        count += (seats[i] == 2);
    }
    return count;
}

void print_seats(int *seats, int row_len, int rows) {
    for (int i=0; i < rows; i++) {
        for (int j=0; j < row_len; j++) {
            switch (seats[(i*row_len)+j]) {
                case 0:
                    printf(".");
                    break;
                case 1:
                    printf("L");
                    break;
                default:
                    printf("#");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int apply(int *seats, int* new_seats, int col_len, int rows) {
    int changed = 0;
    for (int i =0; i < (col_len * rows); i++) {
        int adj = 0;
        int col = i % col_len;

        // Before and after.
        adj += col - 1 < 0 ? 0 : (seats[i - 1] == 2);
        adj += col + 1 >= col_len ? 0 : (seats[i + 1] == 2);

        // Above and below.
        adj += i - col_len < 0 ? 0 : (seats[i - col_len] == 2);
        adj += i + col_len >= rows * col_len ? 0 : (seats[i + col_len] == 2);

        // Diagonals
        adj += (col - 1 < 0) || (i - col_len < 0) ? 0 : (seats[i - 1 - col_len] == 2);
        adj += (col + 1 >= col_len) || (i - col_len < 0) ? 0 : (seats[i + 1 - col_len] == 2);
        adj += (col - 1 < 0) || (i + col_len >= rows * col_len) ? 0 : (seats[i - 1 + col_len] == 2);
        adj += (col + 1 >= col_len) || (i + col_len >= rows * col_len) ? 0 : (seats[i + 1 + col_len] == 2);
        
        if (adj >= 4 && seats[i] == 2) {
            new_seats[i] = 1;
            changed |= 1;
        } else if (adj == 0 && seats[i] == 1) {
            new_seats[i] = 2;
            changed |= 1;
        } else {
            new_seats[i] = seats[i];
        }
    }
    return changed;
}

int apply_long(int *seats, int* new_seats, int col_len, int rows) {
    int changed = 0;

    for (int i = 0; i < (col_len * rows); i++) {
        int adj = 0;
        int col = i % col_len;
        int row = i / col_len;

        // Before and after.
        for (int j=1; j < col_len - col; j++) {
            if (seats[i+j] == 2) {
                adj++;
                break;
            } else if (seats[i+j] == 1) {
                break;
            } else {
                continue;
            }
        }

        for (int j=col - 1; j >= 0; j--) {
            if (seats[i-(col - j)] == 2) {
                adj++;
                break;
            } else if (seats[i-(col - j)] == 1) {
                break;
            } else {
                continue;
            }
        }

        // Above and below.
        for (int j=1; j < rows - row; j++) {
            if (seats[i+(j*col_len)] == 2) {
                adj++;
                break;
            } else if (seats[i+(j*col_len)] == 1) {
                break;
            } else {
                continue;
            }
        }

        for (int j=row - 1; j >=0; j--) {
            if (seats[i-((row- j)*col_len)] == 2) {
                adj++;
                break;
            } else if (seats[i-((row- j)*col_len)] == 1) {
                break;
            } else {
                continue;
            }
        }

        //// Diagonals

        // Top-Right
        for (int j=i - (col_len - 1); (j > 0) && ((j % col_len) > col); j -= col_len - 1) {
            if (seats[j] == 2) {
                adj++;
                break;
            } else if (seats[j] == 1) {
                break;
            } else {
                continue;
            }
        }

        // Top-Left
        for (int j=i - (col_len + 1); (j >= 0) && ((j % col_len) < col); j -= col_len + 1) {
            if (seats[j] == 2) {
                adj++;
                break;
            } else if (seats[j] == 1) {
                break;
            } else {
                continue;
            }
        }

        // Bottom-Left
        for (int j=i + (col_len - 1); (j < (rows * col_len) && (j % col_len) < col); j += col_len - 1) {
            if (seats[j] == 2) {
                adj++;
                break;
            } else if (seats[j] == 1) {
                break;
            } else {
                continue;
            }
        }

        // Bottom-Right
        for (int j=i + (col_len + 1); (j < (rows * col_len)) && ((j % col_len) > col); j += col_len + 1) {
            if (seats[j] == 2) {
                adj++;
                break;
            } else if (seats[j] == 1) {
                break;
            } else {
                continue;
            }
        }
        if (adj >= 5 && seats[i] == 2) {
            new_seats[i] = 1;
            changed |= 1;
        } else if (adj == 0 && seats[i] == 1) {
            new_seats[i] = 2;
            changed |= 1;
        } else {
            new_seats[i] = seats[i];
        }
    }
    return changed;
}

void part_one(FILE *fp) {
    int chars_read = 0;
    char *buf = NULL;
    size_t len = 0;
    int lines = 1;
    int row_length = getline(&buf, &len, fp) - 1;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        lines++;
    }

    rewind(fp);
    int* seats = malloc(lines * row_length * sizeof(int));

    lines = 0;
    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        for (int i=0; i < chars_read; i++) {
            switch (buf[i]) {
                case '.':
                    seats[lines*row_length + i] = 0;
                    break;
                case 'L':
                    seats[lines*row_length + i] = 1;
                    break;
                case '#':
                    printf("Assumption that there are no '#''s false!\n");
                    seats[lines*row_length + i] = 2;
                    break;
                default:
                    continue;
            }
        }
        lines++;
    }
    free(buf);
    int changed = 1;
    while (changed) {
        int* new_seats = malloc(lines * row_length * sizeof(int));
        changed = apply(seats, new_seats, row_length, lines);
        memcpy(seats, new_seats, lines * row_length * sizeof(int));
        free(new_seats);
    }
    printf("Part one completed. %d seats are occupied.\n", count_seats(seats, row_length, lines));
    free(seats);
}

void part_two(FILE *fp) {
    int chars_read = 0;
    char *buf = NULL;
    size_t len = 0;
    int lines = 1;
    int row_length = getline(&buf, &len, fp) - 1;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        lines++;
    }

    rewind(fp);
    int* seats = malloc(lines * row_length * sizeof(int));

    lines = 0;
    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        for (int i=0; i < chars_read; i++) {
            switch (buf[i]) {
                case '.':
                    seats[lines*row_length + i] = 0;
                    break;
                case 'L':
                    seats[lines*row_length + i] = 1;
                    break;
                case '#':
                    printf("Assumption that there are no '#''s false!\n");
                    seats[lines*row_length + i] = 2;
                    break;
                default:
                    continue;
            }
        }
        lines++;
    }
    free(buf);

    int changed = 1;
    while (changed) {
        int* new_seats = malloc(lines * row_length * sizeof(int));
        changed = apply_long(seats, new_seats, row_length, lines);
        memcpy(seats, new_seats, lines * row_length * sizeof(int));
        free(new_seats);
    }
    printf("Part two completed. %d seats are occupied.\n", count_seats(seats, row_length, lines));
    free(seats);
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