#include <stdio.h>
#include <string.h>


int max_joltage(char *c)
{
    int len = strlen(c);
    int res = 0;

    for (int i = 0; i < len - 1; i++) {
        int d1 = c[i] - '0';
        for (int j = i + 1; j < len; j++) {
            int d2 = c[j] - '0';
            int value = d1 * 10 + d2;
            if (value > res) res = value;
        }
    }
    return res;
}

int main() {
    long sum = 0;
    char buffer[256];
    char filename[] = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file) { 
        while (fgets(buffer, sizeof(buffer), file)) {
            sum += max_joltage(buffer);
        }
        printf("Sum: %ld\n", sum);
        fclose(file);
    } 
}
