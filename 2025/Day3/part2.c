#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_best_12(const char *c, char *out)
{
    int len = strlen(c);

    if (c[len - 1] == '\n') len--;

    int needed = 12;
    int pos = 0;  
    int outpos = 0;

    while (needed > 0) {
        int maxDigit = -1;
        int maxIndex = pos;

        int limit = len - needed;

        for (int i = pos; i <= limit; i++) {
            int d = c[i] - '0';
            if (d > maxDigit) {
                maxDigit = d;
                maxIndex = i;
            }
        }

        out[outpos++] = c[maxIndex];

        pos = maxIndex + 1;
        needed--;
    }

    out[outpos] = '\0'; 
}

int main()
{
    char line[512];
    char best12[13];
    long long total = 0;

    FILE *f = fopen("input.txt", "r");
    if (!f) return 1;

    while (fgets(line, sizeof(line), f)) {
        find_best_12(line, best12);
        total += atoll(best12);
    }

    printf("\nTotal joltage: %lld\n", total);

    fclose(f);
    return 0;
}

