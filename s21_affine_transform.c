#include "s21_parser.h"

void centralize(data *d) {
  double max_value = 0.0;
  double scaling = 0.0;
  for (unsigned int i = 0; i < d->vertices_count * 3; i++) {
    if (d->vertices[i] > max_value) {
      max_value = d->vertices[i];
    }
  }
  printf("MAX_V %.1f\n", max_value);
  if (max_value > 1) {
    scaling = 1.0 / max_value;
  } else {
    scaling = 0.9;
  }

  for (unsigned int i = 0; i < d->vertices_count * 3; i++) {
    d->vertices[i] *= scaling;
    printf("HERE, %.1f\n", d->vertices[i]);
  }
}