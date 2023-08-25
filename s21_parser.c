#include "s21_parser.h"

int parser(model_data *data, const char *file_name) {
  FILE *fptr = NULL;
  fptr = fopen(file_name, "r");
  if (fptr == NULL) {
    fclose(fptr);
    return 1;
  }
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      data->vertices_count += 1;
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
        data->triangle_cnt += 1;
      } else if (i == 4) {
        data->square_cnt += 1;

      } else {
        i = 0;
      }
      i = 0;
    }
  }
  fclose(fptr);
  data->vertices = calloc(data->vertices_count, 3 * sizeof(double));
  data->square_coord = calloc(data->square_cnt, 4 * sizeof(int));
  data->triangle_coord = calloc(data->triangle_cnt, 3 * sizeof(int));

  fptr = fopen(file_name, "r");
  int new_vertices_count = 0;
  int new_square_count = 0;
  int new_triangles_count = 0;
  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      double x, y, z;
      if (sscanf(buffer + 2, "%lf %lf %lf", &x, &y, &z) == 3) {
        data->vertices[new_vertices_count] = x;
        data->vertices[new_vertices_count + 1] = y;
        data->vertices[new_vertices_count + 2] = z;
        new_vertices_count += 3;
      } else {
        return 1;
      }
    } else if (buffer[0] == 'f' && buffer[1] == ' ') {
      const char *delim = " ";
      char *tok = strtok(buffer, delim);
      int i = 0;
      int extracted_number[50] = {0};
      while (tok != NULL) {
        if (sscanf(tok, "%d", &extracted_number[i]) == 1) {
          i += 1;
        }

        tok = strtok(NULL, delim);
      }
      if (i == 3) {
        for (int j = 0; j < 3; j++) {
          data->triangle_coord[new_triangles_count] = extracted_number[j] - 1;
          new_triangles_count += 1;
        }

      } else if (i == 4) {
        for (int j = 0; j < 4; j++) {
          data->square_coord[new_square_count] = extracted_number[j] - 1;
          new_square_count += 1;
        }
      } else {
        i = 0;
      }
      i = 0;
    }
  }
  centr(data);
  return 0;
}

// int main() {
//   model_data data = {.vertices_count = 0,
//                      .triangle_cnt = 0,
//                      .square_cnt = 0,
//                      .triangle_coord = NULL,
//                      .square_coord = NULL,
//                      .vertices = NULL};
//   const char *objFileName = "./obj_files/hydrant.obj";

//   parser(&data, objFileName);
//   return 0;
// }