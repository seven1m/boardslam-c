#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../boardslam.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("You must supply 3 numbers.\n");
    return 1;
  }
  int n1 = atoi(argv[1]);
  int n2 = atoi(argv[2]);
  int n3 = atoi(argv[3]);
  if (n1 < 1 || n1 > 6 || n2 < 1 || n2 > 6 || n3 < 1 || n3 > 6) {
    printf("You must supply 3 numbers, each between 1 and 6.\n");
    return 2;
  }
  Answer *answers = boardslam_results(n1, n2, n3);
  for (size_t i=0; i<36; i++) {
    if (answers[i].x.number != 0) {
      char x_buf[10], y_buf[10], z_buf[10], op1_buf[2], op2_buf[2];
      sprintval(x_buf, answers[i].x);
      sprintval(y_buf, answers[i].y);
      sprintval(z_buf, answers[i].z);
      sprintop(op1_buf, answers[i].op1);
      sprintop(op2_buf, answers[i].op2);
      printf("%s %s %s %s %s = %lu\n", x_buf, op1_buf, y_buf, op2_buf, z_buf, i+1);
    }
  }
  printf("\nmissing: ");
  int comma = 0;
  for (size_t i=0; i<36; i++) {
    if (answers[i].x.number == 0) {
      if (comma) printf(", ");
      comma = 1;
      printf("%lu", i+1);
    }
  }
  printf("\n");
}
