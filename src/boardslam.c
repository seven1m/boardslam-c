#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  Add,
  Subtract,
  Multiply,
  Divide
} Op;

typedef struct {
  int number;
  int power;
} Value;

typedef struct {
  Value x;
  Op op1;
  Value y;
  Op op2;
  Value z;
} Answer;

int op(int n1, Op op, int n2) {
  float r;
  switch(op) {
    case Add:
      return n1 + n2;
    case Subtract:
      return n1 - n2;
    case Multiply:
      return n1 * n2;
    case Divide:
      r = (float)n1 / (float)n2;
      if (r == (int)r) {
        return r;
      } else {
        return 0;
      }
    default:
      return 0;
  }
}

void sprintop(char *buf, Op op) {
  switch(op) {
    case Add:
      sprintf(buf, "+");
      break;
    case Subtract:
      sprintf(buf, "-");
      break;
    case Multiply:
      sprintf(buf, "*");
      break;
    case Divide:
      sprintf(buf, "/");
      break;
  }
}

void sprintval(char *buf, Value val) {
  if (val.power == 1) {
    sprintf(buf, "%d  ", val.number);
  } else {
    sprintf(buf, "%d^%d", val.number, val.power);
  }
}

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
  Op ops[] = { Add, Subtract, Multiply, Divide };
  int permutations[] = {
    n1, n2, n3,
    n1, n3, n2,
    n2, n1, n3,
    n2, n3, n1,
    n3, n1, n2,
    n3, n2, n1,
  };
  int powers[] = { 1, 0, 2, 3 };
  Answer answers[36] = { 0 };
  for (size_t op1i=0; op1i<4; op1i++) {
    Op op1 = ops[op1i];
    for (size_t op2i=0; op2i<4; op2i++) {
      Op op2 = ops[op2i];
      for (size_t ni=0; ni<18; ni+=3) {
        int n1 = permutations[ni];
        int n2 = permutations[ni+1];
        int n3 = permutations[ni+2];
        for (size_t xpi=0; xpi<4; xpi++) {
          int xpow = powers[xpi];
          int x = pow(n1, xpow);
          for (size_t ypi=0; ypi<4; ypi++) {
            int ypow = powers[ypi];
            int y = pow(n2, ypow);
            for (size_t zpi=0; zpi<4; zpi++) {
              int zpow = powers[zpi];
              int z = pow(n3, zpow);
              int result = op(op(x, op1, y), op2, z);
              if (result > 0 && result <= 36 && answers[result-1].x.number == 0) {
                Value v1 = { n1, xpow };
                Value v2 = { n2, ypow };
                Value v3 = { n3, zpow };
                Answer answer = { v1, op1, v2, op2, v3 };
                answers[result-1] = answer;
              }
            }
          }
        }
      }
    }
  }
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
  return 0;
}

