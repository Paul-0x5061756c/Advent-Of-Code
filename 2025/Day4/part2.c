#include <stdio.h>
#include <string.h>

int check_accessible(char rows[][512], int width, int height, int x, int y) {
    if (rows[y][x] != '@')
        return 0;

    int directions[8][2] = {
        {-1, -1}, { 0, -1}, { 1, -1},
        {-1,  0},           { 1,  0},
        {-1,  1}, { 0,  1}, { 1,  1}
    };

    int count = 0;

    for (int i = 0; i < 8; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        if (nx < 0 || ny < 0 || nx >= width || ny >= height)
            continue;

        if (rows[ny][nx] == '@')
            count++;
    }

    return count < 4;
}

const int directions[8][2] = {
  {-1, -1}, { 0, -1}, { 1, -1},
  {-1,  0},           { 1,  0},
  {-1,  1}, { 0,  1}, { 1,  1}
};

int main() {
    char buffer[512];
    char filename[] = "input.txt";

    char rows[512][512];
    int rowCount = 0;
    int width = 0;

    FILE *file = fopen(filename, "r");
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        strncpy(rows[rowCount], buffer, sizeof(rows[rowCount]) - 1);
        rows[rowCount][sizeof(rows[rowCount]) - 1] = '\0';
        rowCount++;

        if (width == 0)
            width = (int)strlen(buffer);
    }

    fclose(file);

    int result = 0;

    while (1) {
        int removed = 0;

        char to_remove[512][512] = {0};

        for (int y = 0; y < rowCount; y++) {
            for (int x = 0; x < width; x++) {
                if (check_accessible(rows, width, rowCount, x, y)) {
                    to_remove[y][x] = 1;
                    removed++;
                }
            }
        }

        if (removed == 0)
            break;

        for (int y = 0; y < rowCount; y++) {
            for (int x = 0; x < width; x++) {
                if (to_remove[y][x])
                    rows[y][x] = '.'; 
            }
        }

        result += removed;
    }

    printf("%d", result);
    return 0;
}

