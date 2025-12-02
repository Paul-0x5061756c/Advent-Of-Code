#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char delimiter = '-';

char* int_to_char_array(long long number, char* buffer, size_t bufferSize) {
    snprintf(buffer, bufferSize, "%lld", number);
    return buffer;
}

int find_repeating_patterns(char* char_array) {
    int length = strlen(char_array);

    if(length < 2) return 0;

    if(length % 2 == 0){
        int half_length = length / 2;
        if(strncmp(char_array, char_array + half_length, half_length) == 0){
            return 1;
        }
    }

    return 0;
}

long long get_invalid_id(char* input){
    input[strcspn(input, "\r\n")] = '\0';
    char *dash = strchr(input, delimiter);
    if (!dash) return 0;

    *dash = '\0';
    long long a = strtoll(input, NULL, 10);
    long long b = strtoll(dash + 1, NULL, 10);

    long long result = 0;
    char buf[50];

    for(long long i = a; i <= b; i++){
        int_to_char_array(i, buf, sizeof(buf));
        if(find_repeating_patterns(buf)){
            result += i;
        }
    }

    return result;
}

int main() {
    char buffer[200];
    char filename[] = "input.txt";
    long long sum_of_invalid_ids = 0;

    FILE *file = fopen(filename, "r");
    if (file) { 
        while (fgets(buffer, sizeof(buffer), file)) {
            long long result = get_invalid_id(buffer);
            sum_of_invalid_ids += result;
        }
        fclose(file);
    } 
    printf("Sum of invalid IDs: %lld\n", sum_of_invalid_ids);
}

