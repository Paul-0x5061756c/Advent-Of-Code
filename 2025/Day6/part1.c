#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 4
#define MAX_COLS 1024
#define LINE_SZ  4096

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        fprintf(stderr, "cannot open input.txt\n");
        return 1;
    }

    char line[LINE_SZ];
    unsigned long ns[MAX_ROWS][MAX_COLS] = {0};
    unsigned long total = 0;

    for (size_t row = 0; fgets(line, sizeof(line), f) != NULL; row++) {
        size_t col = 0;

        char *tok = strtok(line, " \n");
        for (; tok != NULL; tok = strtok(NULL, " \n"), col++) {

            if (strchr(tok, '+')) {
                unsigned long subtotal = 0;
                for (size_t r = 0; r < row && r < MAX_ROWS; r++)
                    subtotal += ns[r][col];
                total += subtotal;

            } else if (strchr(tok, '*')) {
                unsigned long subtotal = 1;
                for (size_t r = 0; r < row && r < MAX_ROWS; r++)
                    subtotal *= ns[r][col];
                total += subtotal;

            } else {
                if (row < MAX_ROWS && col < MAX_COLS) {
                    ns[row][col] = strtoul(tok, NULL, 10);
                }
            }
        }
    }

    fclose(f);

    printf("%lu\n", total);
    return 0;
}
