#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void part_one(FILE *fp) {
    int departure;
    if (fscanf(fp, "%d ", &departure) == -1) {
        printf("Failed to read departure.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    char *buf = NULL;
    size_t l = 0;
    if (getline(&buf, &l, fp) == -1) {
        printf("Failed to read buses.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    char *token = strtok(buf, ",");

    int answer;
    int wait = INT_MAX;
    while (token != NULL) {
        char x;
        if (sscanf(token, "%c", &x) != -1) {
            if (x != 'x') {
                int id;
                if (sscanf(token, "%3d", &id) != -1) {
                    int closest = (id * ((departure / id) + 1)) - departure;
                    if (closest < wait) {
                        wait = closest;
                        answer = closest * id;
                    }
                }
            }
        }
        token = strtok(NULL, ",");
    }
    printf("Part one completed. The answer is %d.\n", answer);
}

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// -+ From Rosetta Code
// -+ https://rosettacode.org/wiki/Chinese_remainder_theorem#C
// -+ Access Date: 20/12
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

// returns x where (a * x) % b == 1
long int mul_inv(long int a, long int b)
{
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
 
long int chinese_remainder(long int *n, long int *a, int len)
{
	long int p, i, prod = 1, sum = 0;
 
	for (i = 0; i < len; i++) prod *= n[i];
 
	for (i = 0; i < len; i++) {
		p = prod / n[i];
		sum += a[i] * mul_inv(p, n[i]) * p;
	}
 
	return sum % prod;
}
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// -+ END Rosetta Code Code
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

void part_two(FILE *fp) {
    int departure;
    if (fscanf(fp, "%d ", &departure) == -1) {
        printf("Failed to read departure.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    char *buf = NULL;
    size_t l = 0;
    if (getline(&buf, &l, fp) == -1) {
        printf("Failed to read buses.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    char *token = strtok(buf, ",");

    long int answer;
    int gap = 0;
    int count = 0;
    long int a[16] = {0};
    long int m[16] = {0};
    while (token != NULL) {
        char x;
        if (sscanf(token, "%c", &x) != -1) {
            if (x != 'x') {
                if (sscanf(token, "%3li", &a[count]) != -1) {
                    m[count] = a[count] - gap;
                    count++;
                }
            }
            gap++;
        }
        token = strtok(NULL, ",");
    }
    answer = chinese_remainder(a, m, count);
    printf("Part two completed. The answer is %lu.\n", answer);
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