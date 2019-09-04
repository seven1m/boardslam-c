#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../boardslam.h"

void print_form(int n1, int n2, int n3) {
  if (n1 != 0 && n2 != 0 && n3 != 0) {
    printf(
      "<form>"
        "n1: "
        "<input name='n1' size='2' value='%d'> "
        "n2: "
        "<input name='n2' size='2' value='%d'> "
        "n3: "
        "<input name='n3' size='2' value='%d'> "
        "<input type='submit' value='Go!'>"
      "</form>",
      n1,
      n2,
      n3
    );
  } else {
    printf(
      "<form>"
        "n1: "
        "<input name='n1' size='2' value=''> "
        "n2: "
        "<input name='n2' size='2' value=''> "
        "n3: "
        "<input name='n3' size='2' value=''> "
        "<input type='submit' value='Go!'>"
      "</form>"
    );
  }
}

int main() {
  printf("Content-Type: text/html\n\n");
  printf(
    "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">"
    "<html>"
      "<head>"
        "<title>Board Slam / N2K Calculator</title>"
      "</head>"
      "<body>"
        "<p><a href='/'>seven1m.sdf.org</a></p>"
        "<h1>Board Slam / N2K Math Game Calculator</h1>"
        "<p><em>written April 2018 (updated September 2019)</em></p>"
        "<p>"
          "Classical Conversations (Homeschool) communities all over play a math game in the classroom called \"Board Slam\" "
          "or \"National Number Knockout\" (N2K). Participants try to use 3 numbers determined by dice roll along with "
          "various mathematical operations to calculate the answers to fill a grid (the board) of one (1) through "
          "thirty-six (36) slots. This is great fun!"
        "</p>"
        "<p>"
          "But sometimes, students and parents alike get stuck, wondering if they've truly exhaused all possibilities. "
          "This page will show you possible ways to calculate the answers using the numbers given, and at the bottom of the "
          "page, it will tell you which answers seem to be impossible (if any)."
        "</p>"
        "<p>"
          "This tool only tries powers up to 4 and does not attempt fractional exponents. "
          "The sourcecode <a href='https://github.com/seven1m/boardslam-c'>is available</a> in case you want to help improve it!"
        "</p>"
  );
  char *q = getenv("QUERY_STRING");
  char *n1_buf, *n2_buf, *n3_buf;
  if (strlen(q) >= 20) {
    printf("You must supply 3 numbers.\n");
  } else {
    char *pair, *part;
    while ((pair = strsep(&q, "&"))) {
      part = strsep(&pair, "=");
      if (strcmp(part, "n1") == 0) {
        n1_buf = strsep(&pair, "=");
      } else if (strcmp(part, "n2") == 0) {
        n2_buf = strsep(&pair, "=");
      } else if (strcmp(part, "n3") == 0) {
        n3_buf = strsep(&pair, "=");
      }
    }
    if (strcmp(n1_buf, "") != 0 && strcmp(n2_buf, "") != 0 && strcmp(n3_buf, "") != 0) {
      int n1 = atoi(n1_buf);
      int n2 = atoi(n2_buf);
      int n3 = atoi(n3_buf);
      if (n1 >= 1 && n1 <= 6 && n2 >= 1 && n2 <= 6 && n3 >= 1 && n3 <= 6) {
        print_form(n1, n2, n3);
        Answer *answers = boardslam_results(n1, n2, n3);
        printf("<pre>");
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
        int at_least_one = 0;
        for (size_t i=0; i<36; i++) {
          if (answers[i].x.number == 0) {
            if (at_least_one) printf(", ");
            at_least_one = 1;
            printf("%lu", i+1);
          }
        }
        if (!at_least_one) {
          printf("none");
        }
        printf("</pre>");
      } else {
        print_form(0, 0, 0);
        printf("<p>You must supply 3 numbers, each between 1 and 6.</p>");
      }
    } else {
      print_form(0, 0, 0);
    }
  }
  printf(
    "<hr>"
    "<p><i>Hosting for this site is provided by</i></p>"
    "<p><a href='http://sdf.org'><img src='https://sdf.org/sdfbanner.png'></a></p>"
    "<p><a href='http://sdf.org'>The SDF Public Access UNIX System</a></p>"
    "<p><a href='http://validator.w3.org/check?uri=http://seven1m.sdf.org/experiments/boardslam.cgi'><img src='https://www.w3.org/Icons/valid-html20'></a></p>"
    "</body></html>"
  );
  return 0;
}
