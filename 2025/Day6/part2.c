#include <stdio.h>
#include <string.h>

#define ROWS 8
#define COLS 4096

void transpose(void *src, void *dst, size_t elem_size,
               size_t rows, size_t cols)
{
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            size_t src_index = r * cols + c;
            size_t dst_index = c * rows + r;

            memcpy(
                (char *)dst + dst_index * elem_size,
                (char *)src + src_index * elem_size,
                elem_size
            );
        }
    }
}

int main(void)
{
    FILE *file = fopen("input.txt", "r");
    char buf[ROWS][COLS] = {0};

    char buf_T[COLS][ROWS] = {0};

    for (size_t r = 0; r < ROWS; r++)
    {
        if (fgets(buf[r], COLS, file) == NULL)
            break;
    }

    fclose(file);

    transpose(buf, buf_T, sizeof(char), ROWS, COLS);

    unsigned long numbers[8] = {0};
    size_t num_count = 0;
    char op = '\0';
    unsigned long grand_total = 0;

    for (size_t i = 0; i < COLS; i++)
    {
        sscanf(buf_T[i], "%lu %c", &numbers[num_count], &op);

        if (numbers[num_count] != 0)
        {
            num_count++;
        }
        else
        {
            unsigned long subtotal = (op == '*') ? 1 : 0;

            if (op == '+')
            {
                for (size_t j = 0; j < num_count; j++)
                    subtotal += numbers[j];
            }
            else if (op == '*')
            {
                for (size_t j = 0; j < num_count; j++)
                    subtotal *= numbers[j];
            }

            if (subtotal == 0)
                break;

            grand_total += subtotal;

            memset(numbers, 0, sizeof(numbers));
            num_count = 0;
            op = '\0';
        }
    }

    printf("%lu\n", grand_total);
    return 0;
}
