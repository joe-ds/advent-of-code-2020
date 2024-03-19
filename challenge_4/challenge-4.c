#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void part_one(FILE* fp) {
    int count = 0;
    int found = 0;
    int chars_read = 0;
    char *buf = NULL;
    size_t len = 0;
    const char *fields[8];
    fields[0] = "byr";
    fields[1] = "iyr";
    fields[2] = "eyr";
    fields[3] = "hgt";
    fields[4] = "hcl";
    fields[5] = "ecl";
    fields[6] = "pid";
    fields[7] = "cid";
    
    int lines_read = 0;
    int total = 0;

    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        lines_read++;
        if (chars_read < 3) {
            total++;
            if (found == 7) {
                count++;
            }
            found = 0;
        } else {
            char *token;
            token = strtok(buf, " ");

            while (token != NULL) {
                for (int i=0; i < 7; i++) {
                    if (strncmp(token, fields[i], 3) == 0) {
                        found++;
                        break;
                    }
                }
                token = strtok(NULL, " ");
            }
        }
    }
    total++;
    found == 7 ? count++: count;
    printf("Part one completed. %d/%d passports valid.\n", count, total);
}

int which_token(char *x) {
    const char *fields[7];
    fields[0] = "byr";
    fields[1] = "iyr";
    fields[2] = "eyr";
    fields[3] = "hgt";
    fields[4] = "hcl";
    fields[5] = "ecl";
    fields[6] = "pid";
    // fields[7] = "cid";

    for (int i=0; i < 7; i++) {
        if (strncmp(x, fields[i], 3) == 0) {
            return i;
        }
    }
    return -1;
}

int part_two(FILE* fp) {
    int count = 0;
    int found = 0;
    int chars_read = 0;
    char *buf = NULL;
    size_t len = 0;
    
    int lines_read = 0;
    int total = 0;
    regex_t* regexes[7];

    regex_t byr_reg;
    if (regcomp(&byr_reg, "byr:(19[2-9][0-9])|byr:(200[0-2])", REG_EXTENDED) != 0) {
        printf("Error compiling byr regex.");
        return -1;
    }
    regexes[0] = &byr_reg;

    regex_t iyr_reg;
    if (regcomp(&iyr_reg, "iyr:(201[0-9])|iyr:(2020)", REG_EXTENDED) != 0) {
        printf("Error compiling iyr regex.");
        return -1;
    }
    regexes[1] = &iyr_reg;

    regex_t eyr_reg;
    if (regcomp(&eyr_reg, "eyr:(202[0-9])|eyr:(2030)", REG_EXTENDED) != 0) {
        printf("Error compiling eyr regex.");
        return -1;
    }
    regexes[2] = &eyr_reg;

    regex_t hgt_reg;
    if (regcomp(&hgt_reg, "hgt:(1[5-8][0-9])cm|hgt:(19[0-3])cm|hgt:(59)in|hgt:(6[0-9])in|hgt:(7[0-6])in", REG_EXTENDED) != 0) {
        printf("Error compiling hgt_reg.");
        return -1;
    }
    regexes[3] = &hgt_reg;

    regex_t hcl_reg;
    if (regcomp(&hcl_reg, "hcl:(#[0-9a-f]{6})\\s?$", REG_EXTENDED) != 0) {
        printf("Error compiling hcl_reg.");
        return -1;
    }
    regexes[4] = &hcl_reg;

    regex_t ecl_reg;
    if (regcomp(&ecl_reg, "ecl:(amb|blu|brn|gry|grn|hzl|oth)", REG_EXTENDED) != 0) {
        printf("Error compiling ecl_reg.");
        return -1;
    }
    regexes[5] = &ecl_reg;

    regex_t pid_reg;
    if (regcomp(&pid_reg, "pid:([0-9]{9})\\s?$", REG_EXTENDED) != 0) {
        printf("Error compiling pid_reg.");
        return -1;
    }
    regexes[6] = &pid_reg;
    
    while ((chars_read = getline(&buf, &len, fp)) != -1) {
        lines_read++;
        if (chars_read < 3) {
            total++;
            if (found == 7) {
                count++;
            }
            found = 0;
        } else {
            char *token;
            token = strtok(buf, " ");

            while (token != NULL) {
                int w;
                if ((w = which_token(token)) != -1) {
                    if (regexec(regexes[w], token, 0, NULL, 0) == 0) {
                        found++;
                    }
                }
                token = strtok(NULL, " ");
            }
        }
    }
    total++;
    found == 7 ? count++: count;
    printf("Part two completed. %d/%d passports valid.\n", count, total);
    return 0;
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