#include <stdio.h>
#include <stdlib.h>

const int STARTING_POS = 50; 

typedef struct{
  char dir;
  int value;
} Rotation;

Rotation parse_rotation(const char* input) {
    Rotation rotation;
    rotation.dir = input[0];
    rotation.value = atoi(&input[1]);
    return rotation;
}

uint rotate(Rotation current_pos, Rotation rotation) {
  for(int i = 0; i < rotation.value; i++) {
    if(rotation.dir == 'L') {
      current_pos.value--;
      if(current_pos.value < 0) {
        current_pos.value = 99; 
      }
    } else if(rotation.dir == 'R') {
      current_pos.value++;
      if(current_pos.value > 99) {
        current_pos.value = 0; 
      }
    }
  }

  return current_pos.value;
}


int main() {
    Rotation current_pos = { 'L', STARTING_POS };
    uint current_value = STARTING_POS;
    uint result = 0;

    char filename[] = "input.txt";

    char buffer[10];
    FILE *file = fopen(filename, "r");
    if (file) { 
        while (fgets(buffer, sizeof(buffer), file)) {
            Rotation rot = parse_rotation(buffer);
            current_pos.value = rotate(current_pos, rot);
            current_value = current_pos.value;
            if(current_pos.value == 0) {
              result++;
            }
        }
        fclose(file);
    } 
    printf("Result: %d\n", result);
    return 0;
}




