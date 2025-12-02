#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char delimiter = '-';

char* int_to_char_array(long number, char* buffer, size_t bufferSize) {
    snprintf(buffer, bufferSize, "%ld", number);
    return buffer;
}

int find_repeating_patterns(char* c) {
    int length = strlen(c);
    if(length < 2 || (length & 1)) return 0;
    size_t half = length >> 1;
    return memcmp(c, c + half, half) == 0;
}

long get_invalid_id(char* input){
    char *dash = strchr(input, delimiter);
    if (!dash) return 0;
    *dash = '\0';

    long a = strtoll(input, NULL, 10);
    long b = strtoll(dash + 1, NULL, 10);

    long result = 0;
    char buf[50];

    for(long i = a; i <= b; i++){
        int_to_char_array(i, buf, sizeof(buf));
        if(find_repeating_patterns(buf)){
            result += i;
        }
    }

    return result;
}

int main() {
    char buffer[50];
    char filename[] = "input.txt";
    long sum_of_invalid_ids = 0;

    FILE *file = fopen(filename, "r");
    if (file) { 
        while (fgets(buffer, sizeof(buffer), file)) {
            long result = get_invalid_id(buffer);
            sum_of_invalid_ids += result;
        }
        fclose(file);
    } 
    printf("Sum of invalid IDs: %ld\n", sum_of_invalid_ids);
}

