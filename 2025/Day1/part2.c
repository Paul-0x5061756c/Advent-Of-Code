#include <stdio.h>
#include <stdlib.h>

const int STARTING_POS = 50;

typedef struct {
  char dir;
  int value;
} Rotation;

typedef struct {
  Rotation rotation;
  int times_passed_zero;
} RotationResult;

Rotation parse_rotation(const char *input) {
  Rotation rotation;
  rotation.dir = input[0];
  rotation.value = atoi(&input[1]);
  return rotation;
}


RotationResult rotate(Rotation current_pos, Rotation rotation) {
    uint amount_of_times_passed_start = 0;

    for (int i = 0; i < rotation.value; i++) {
        if (rotation.dir == 'L') {
            current_pos.value--;
            if (current_pos.value < 0) {
                current_pos.value += 100; 
            }
        } else if (rotation.dir == 'R') {
            current_pos.value++;
            if (current_pos.value > 99) {
                current_pos.value -= 100;
            }
        }

        if (current_pos.value == 0) {
            amount_of_times_passed_start++;
        }
    }

    RotationResult result = { current_pos, amount_of_times_passed_start };
    return result;
}


int main() {
  Rotation current_pos = {'L', STARTING_POS};
  uint current_value = STARTING_POS;
  uint result = 0;

  char filename[] = "input.txt";

  char buffer[10];
  FILE *file = fopen(filename, "r");
  if (file) {
    while (fgets(buffer, sizeof(buffer), file)) {
      Rotation rot = parse_rotation(buffer);
      RotationResult rot_result = rotate(current_pos, rot);
      current_pos = rot_result.rotation;
      current_value = current_pos.value;
      result += rot_result.times_passed_zero;
    }
    fclose(file);
  }
  printf("Result: %d\n", result);
  return 0;
}
