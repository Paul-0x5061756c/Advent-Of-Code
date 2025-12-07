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

int compare_ranges(const void *a, const void *b) {
  const long long *ra = a;
  const long long *rb = b;

  if (ra[0] < rb[0])
    return -1;
  if (ra[0] > rb[0])
    return 1;
  return 0;
}

int main() {
  char buffer[256];
  char filename[] = "input.txt";
  long long ranges[5000][2];
  int range_count = 0;

  FILE *file = fopen(filename, "r");
  if (file) {
    while (fgets(buffer, sizeof(buffer), file)) {
      if (buffer[0] == '\n' || buffer[0] == '\0')
        break;

      long long *parts = parseLine(buffer);

      long long a = parts[0];
      long long b = parts[1];
      if (a > b) {
        long long tmp = a;
        a = b;
        b = tmp;
      }

      ranges[range_count][0] = a;
      ranges[range_count][1] = b;
      range_count++;
    }

    fclose(file);
  }

  qsort(ranges, range_count, sizeof(ranges[0]), compare_ranges);

  long long merged[5000][2];
  int merged_count = 0;

  merged[0][0] = ranges[0][0];
  merged[0][1] = ranges[0][1];
  merged_count = 1;

  for (int i = 1; i < range_count; i++) {
    long long start = ranges[i][0];
    long long end = ranges[i][1];

    long long *last = merged[merged_count - 1];

    if (start <= last[1] + 1) {
      if (end > last[1])
        last[1] = end;
    } else {
      merged[merged_count][0] = start;
      merged[merged_count][1] = end;
      merged_count++;
    }
  }

  long long total_fresh = 0;

  for (int i = 0; i < merged_count; i++) {
    total_fresh += (merged[i][1] - merged[i][0] + 1);
  }

  printf("fresh_count: %lld\n", total_fresh);
  return 0;
}
