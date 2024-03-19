#include <stdio.h>
#include <stdlib.h>

struct instr {
    int cmd;
    int n;
};

int execute(struct instr* program, int lines, int *return_val) {
    long signed int acc = 0;
    int visited[lines];
    for (int i=0; i < lines; i++) {
        visited[i] = 0;
    }
    int index = 0;

    while (!visited[index]) {
        visited[index] = 1;

        if (program[index].cmd == 0) {
            acc += program[index].n;
            index++;
        } else if (program[index].cmd == 1) {
            index += program[index].n;
        } else {
            index++;
        }

        if (index == lines) {
            *return_val = 0;
            return acc;
        } else if (index > lines || index < 0) {
            *return_val = -2;
            return acc;
        }
    }
    *return_val = -1;
    return acc;
}

void part_one(FILE* fp) {
    int chars_read = 0;
    char *buf = NULL;
    size_t len = 0;
    int lines = 0;

    while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp, "%*c"))) {
        ++lines;
    }
    rewind(fp);

    struct instr program[lines];
    int count = 0;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        char cmd[4];
        int x = 0;

        sscanf(buf, "%s %d", cmd, &x);

        if (cmd[0] == 'a') {
            program[count].cmd = 0;
        } else if (cmd[0] == 'j') {
            program[count].cmd = 1;
        } else {
            program[count].cmd = 2;
        }
        program[count].n = x;
        count++;
    }

    int r;
    long signed int result = execute(program, lines, &r);
    printf("Part one completed. The value is %li.\n", result);
}

void part_two(FILE *fp) {
    int chars_read = 0;
    char *buf = NULL;
    size_t len = 0;
    int lines = 0;

    while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp, "%*c"))) {
        ++lines;
    }
    rewind(fp);

    struct instr program[lines];
    int count = 0;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        char cmd[4];
        int x = 0;

        sscanf(buf, "%s %d", cmd, &x);

        if (cmd[0] == 'a') {
            program[count].cmd = 0;
        } else if (cmd[0] == 'j') {
            program[count].cmd = 1;
        } else {
            program[count].cmd = 2;
        }
        program[count].n = x;
        count++;
    }

    long signed int result = 0;
    signed int r = 0;

    for (int i=0; i < lines; i++) {
        if (program[i].cmd == 1) {
            program[i].cmd = 2;
            result = execute(program, lines, &r);
            if (r == 0) {
                break;
            } else {
                program[i].cmd = 1;
            }
        } else if (program[i].cmd == 2) {
            program[i].cmd = 1;
            result = execute(program, lines, &r);
            if (r == 0) {
                break;
            } else {
                program[i].cmd = 2;
            }
        }
    }

    printf("Part two completed. The value is %li.\n", result);
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