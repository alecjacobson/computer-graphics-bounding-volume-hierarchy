#ifndef POINT_TRIANGLE_SQUARED_DISTANCE_H
#define POINT_TRIANGLE_SQUARED_DISTANCE_H
#include <Eigen/Core>
// Compute the squared distance of a query point to a triangle, output the
// closest point on the triangle in barycentric coordinates.
//
// Inputs:
//   query  3D position of query point
//   A  first corner position of the triangle
//   B  second corner position of the triangle
//   C  third corner position of the triangle
// Outputs:
//   bary  3-vector so that the closest point on the triangle to the query is
//     given as A*bary(0) + B*bary(1) + C*bary(2)
// Returns squared distance of query to closest point on triangle
double point_triangle_squared_distance(
  const Eigen::RowVector3d & query,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  Eigen::RowVector3d & bary);
#endif

