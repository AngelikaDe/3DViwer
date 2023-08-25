#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct model_data
 * @brief Struct for storing model-related data.
 *
 * This struct holds information about a 3D model's vertices, triangles, and
 * squares.
 */
typedef struct data {
  unsigned vertices_count;  ///< Total count of vertices in the model.
  unsigned triangle_cnt;    ///< Count of triangles in the model.
  unsigned square_cnt;      ///< Count of squares in the model.
  unsigned
      *triangle_coord;  ///< Pointer to an array storing triangle coordinates.
  unsigned *square_coord;  ///< Pointer to an array storing square coordinates.
  double *vertices;        ///< Pointer to an array storing vertex coordinates.
} model_data;

/**
 * @brief Parses the model data from a file.
 *
 * This function reads a file and parses the model data from it,
 * populating the provided model_data struct.
 *
 * @param data A pointer to the model_data struct to populate.
 * @param file_name The name of the file to parse.
 * @return 0 if parsing is successful, 1 if there's an error.
 */
int parser(model_data *data, const char *file_name);

/**
 * @brief Centers the model vertices around the origin.
 *
 * This function scales the model vertices to center them around the origin.
 *
 * @param d A pointer to the model_data struct containing the vertices.
 */
void centr(model_data *d);

/**
 * @brief Moves the model object in 3D space.
 *
 * This function translates the model vertices by the specified values
 * along the X, Y, and Z axes.
 *
 * @param d A pointer to the model_data struct containing the vertices.
 * @param value_x The translation value along the X axis.
 * @param value_y The translation value along the Y axis.
 * @param value_z The translation value along the Z axis.
 */
void move_obj(model_data *d, double value_x, double value_y, double value_z);

/**
 * @brief Scales the model vertices uniformly.
 *
 * This function scales the model vertices by the specified scaling factor.
 *
 * @param d A pointer to the model_data struct containing the vertices.
 * @param value The scaling factor.
 */
void scaling(model_data *d, double value);

/**
 * @brief Rotates the model vertices around a specified axis.
 *
 * This function rotates the model vertices around the specified axis by the
 * given angle.
 *
 * @param d A pointer to the model_data struct containing the vertices.
 * @param value_angle The rotation angle in radians.
 * @param flag The rotation axis flag: 1 for X, 2 for Y, 3 for Z.
 */
void rotate(model_data *d, double value_angle, int flag);