#ifndef INSERT_TRIANGLE_INTO_BOX_H
#define INSERT_TRIANGLE_INTO_BOX_H
#include "BoundingBox.h"
#include <Eigen/Core>
// Grow a box `B` by inserting a triangle with corners `a`,`b`, and `c`.
//
// Inputs:
//   a  first corner position of the triangle
//   b  second corner position of the triangle
//   c  third corner position of the triangle
//   B  bounding box to be grown
// Outputs:
//   B  bounding box grown to include original contents and A
void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B);
#endif
