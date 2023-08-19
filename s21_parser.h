#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  unsigned vertices_count;
  unsigned triangle_cnt;
  unsigned square_cnt;
  unsigned *triangle_coord;
  unsigned *square_coord;
  double *vertices;
} data;
int parser(int num_arg, const char *file_name);
void centralize(data *d);
void printData(const data *d);  // delete later
