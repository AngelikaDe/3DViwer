#include "s21_parser.h"

void centr(model_data *d) {
  double max_value = 0.0;
  double scaling = 0.0;
  for (unsigned int i = 0; i < d->vertices_count * 3; i++) {
    if (d->vertices[i] > max_value) {
      max_value = d->vertices[i];
    }
  }
  if (max_value > 1) {
    scaling = 1.0 / max_value;
  } else {
    scaling = 0.9;
  }

  for (unsigned int i = 0; i < d->vertices_count * 3; i++) {
    d->vertices[i] *= scaling;
  }
}

void move(model_data *d, double value_x, double value_y, double value_z) {
  for (unsigned int i = 0; i < d->vertices_count * 3; i += 3) {
    d->vertices[i] += value_x;
    d->vertices[i + 1] += value_y;
    d->vertices[i + 2] += value_z;
  }
}

void scaling(model_data *d, double value) {
  for (unsigned int i = 0; i < d->vertices_count * 3; i++) {
    d->vertices[i] *= value;
  }
}

void rotate(model_data *d, double value_angle, int flag) {
  if (flag == 1) {  // X
    for (unsigned int i = 0; i < d->vertices_count * 3; i += 3) {
      d->vertices[i + 1] = cos(value_angle) * d->vertices[i + 1] +
                           (-cos(value_angle)) * d->vertices[i + 2];
      d->vertices[i + 2] = sin(value_angle) * d->vertices[i + 1] +
                           cos(value_angle) * d->vertices[i + 2];
    }
  } else if (flag == 2) {  // Y
    for (unsigned int i = 0; i < d->vertices_count * 3; i += 3) {
      d->vertices[i] = cos(value_angle) * d->vertices[i] +
                       sin(value_angle) * d->vertices[i + 2];
      d->vertices[i + 2] = -sin(value_angle) * d->vertices[i] +
                           cos(value_angle) * d->vertices[i + 2];
    }
  } else if (flag == 3) {  // Z
    for (unsigned int i = 0; i < d->vertices_count * 3; i += 3) {
      d->vertices[i] = cos(value_angle) * d->vertices[i] +
                       (-sin(value_angle)) * d->vertices[i + 1];
      d->vertices[i + 1] = sin(value_angle) * d->vertices[i] +
                           cos(value_angle) * d->vertices[i + 1];
    }
  }
}