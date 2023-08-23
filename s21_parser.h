#include <math.h>
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
} model_data;
int parser(model_data *data, const char *file_name);
void centr(model_data *d);
void move(model_data *d, double value_x, double value_y, double value_z);
void scaling(model_data *d, double value);
void rotate(model_data *d, double value_angle, int flag);
void printData(const model_data *d);  // delete later
