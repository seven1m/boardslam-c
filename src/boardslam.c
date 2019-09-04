#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "boardslam.h"

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

Answer* boardslam_results(int n1, int n2, int n3) {
  Op ops[] = { Add, Subtract, Multiply, Divide };
  int permutations[] = {
    n1, n2, n3,
    n1, n3, n2,
    n2, n1, n3,
    n2, n3, n1,
    n3, n1, n2,
    n3, n2, n1,
  };
  int powers[] = { 1, 0, 2, 3, 4 };
  Answer *answers = calloc(36, sizeof(Answer));
  for (size_t op1i=0; op1i<4; op1i++) {
    Op op1 = ops[op1i];
    for (size_t op2i=0; op2i<4; op2i++) {
      Op op2 = ops[op2i];
      for (size_t ni=0; ni<18; ni+=3) {
        int n1 = permutations[ni];
        int n2 = permutations[ni+1];
        int n3 = permutations[ni+2];
        for (size_t xpi=0; xpi<5; xpi++) {
          int xpow = powers[xpi];
          int x = pow(n1, xpow);
          for (size_t ypi=0; ypi<5; ypi++) {
            int ypow = powers[ypi];
            int y = pow(n2, ypow);
            for (size_t zpi=0; zpi<5; zpi++) {
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
  return answers;
}

