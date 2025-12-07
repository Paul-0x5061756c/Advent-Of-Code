#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long *parseLine(char *line) {
  static long long parts[2];
  char *token = strtok(line, "-");
  int index = 0;
  while (token != NULL && index < 2) {
    parts[index++] = strtoll(token, NULL, 10);
    token = strtok(NULL, "-");
  }
  return parts;
}

int input_is_within_ranges(long long input, long long ranges[][2],int range_count) {
  for (int i = 0; i < range_count; i++) {
    if (input >= ranges[i][0] && input <= ranges[i][1]) {
      return 1;
    }
  }
  return 0;
}

int main() {
  char buffer[256];
  char filename[] = "input.txt";
  uint test_input = 0;
  long long ranges[200][2];
  uint range_count = 0;
  uint valid_count = 0;

  FILE *file = fopen(filename, "r");
  if (file) {
    while (fgets(buffer, sizeof(buffer), file)) {
      if (test_input) {
        long long input = strtoll(buffer, NULL, 10);
        if (input_is_within_ranges(input, ranges, range_count)) {
          valid_count++;
        }
      } else {
        if (buffer[0] == '\n' || buffer[0] == '\0') {
          test_input = 1;
          continue;
        }
        long long *parts = parseLine(buffer);
        ranges[range_count][0] = parts[0];
        ranges[range_count][1] = parts[1];
        range_count++;
      }
    }
    fclose(file);
  }
  printf("valid_count: %u\n", valid_count);
  return 0;
}
