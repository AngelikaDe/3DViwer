#include "s21_parser.h"
void printData(const data *d) {
  printf("Vertices:\n");
  for (unsigned i = 0; i < d->vertices_count; i++) {
    printf("Vertex %u: %.1f %.1f %.1f\n", i, d->vertices[i * 3],
           d->vertices[i * 3 + 1], d->vertices[i * 3 + 2]);
  }

  printf("\nTriangle Coordinates:\n");
  for (unsigned i = 0; i < d->triangle_cnt; i++) {
    printf("Triangle %u: %d %d %d\n", i, d->triangle_coord[i * 3],
           d->triangle_coord[i * 3 + 1], d->triangle_coord[i * 3 + 2]);
  }

  printf("\nSquare Coordinates:\n");
  for (unsigned i = 0; i < d->square_cnt; i++) {
    printf("Square %u: %u %u %u %u\n", i, d->square_coord[i * 4],
           d->square_coord[i * 4 + 1], d->square_coord[i * 4 + 2],
           d->square_coord[i * 4 + 3]);
  }
}

int parser(int num_arg, const char *file_name) {
  if (num_arg < 2) {
    return 0;
  }
  FILE *fptr;

  fptr = fopen(file_name, "r");

  if (fptr == NULL) {
    fclose(fptr);
    printf("Error!");
    return 1;
  }
  data data = {.vertices_count = 0,
               .triangle_cnt = 0,
               .square_cnt = 0,
               .triangle_coord = NULL,
               .square_coord = NULL,
               .vertices = NULL};

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      data.vertices_count += 1;
      data.vertices = (double *)realloc(data.vertices, 3 * sizeof(double));
      double x, y, z;
      if (sscanf(buffer + 2, "%lf %lf %lf", &x, &y, &z) == 3) {
        data.vertices[(data.vertices_count - 1) * 3] = x;
        data.vertices[(data.vertices_count - 1) * 3 + 1] = y;
        data.vertices[(data.vertices_count - 1) * 3 + 2] = z;
      } else {
        return 1;
      }
    } else if (buffer[0] == 'f' && buffer[1] == ' ') {
      const char *delim = " ";
      char *tok = strtok(buffer, delim);
      int i = 0;
      int extracted_number[4] = {0};
      while (tok != NULL) {
        if (sscanf(tok, "%d", &extracted_number[i]) == 1) {
          i += 1;
        }

        tok = strtok(NULL, delim);
      }
      if (i == 3) {
        data.triangle_cnt += 1;
        data.triangle_coord = (unsigned int *)realloc(
            data.triangle_coord, data.triangle_cnt * 3 * sizeof(unsigned int));

        if (data.triangle_coord == NULL) {
          printf("Memory allocation failed.\n");
          fclose(fptr);
          return 1;
        }
        for (int j = 0; j < 3; j++) {
          data.triangle_coord[(data.triangle_cnt - 1) * 3 + j] =
              extracted_number[j];
        }
      } else if (i == 4) {
        data.square_cnt += 1;
        data.square_coord = (unsigned int *)realloc(
            data.square_coord, data.square_cnt * 4 * sizeof(unsigned int));

        if (data.square_coord == NULL) {
          printf("Memory allocation failed.\n");
          fclose(fptr);
          return 1;
        }

        for (int j = 0; j < 4; j++) {
          data.square_coord[(data.square_cnt - 1) * 4 + j] =
              extracted_number[j];
        }
      } else {
        return 1;
      }
      i = 0;
    }
  }
  fclose(fptr);
  centralize(&data);

  // printData(&data);
  fclose(fptr);
  free(data.vertices);
  free(data.triangle_coord);
  free(data.square_coord);
  return 0;
}

int main(int argc, char *argv[]) {
  parser(argc, argv[1]);
  return 0;
}