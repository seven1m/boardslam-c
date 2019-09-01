#ifndef __BOARDSLAM__
#define __BOARDSLAM__

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

int op(int n1, Op op, int n2);

void sprintop(char *buf, Op op);

void sprintval(char *buf, Value val);

Answer* boardslam_results(int n1, int n2, int n3);

#endif
