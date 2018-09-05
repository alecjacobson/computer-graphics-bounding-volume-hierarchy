#ifndef TRIANGLE_TRIANGLE_INTERSECTION_H
#define TRIANGLE_TRIANGLE_INTERSECTION_H
#include <Eigen/Core>

// Determine whether two triangles intersect.
//
// Inputs:
//   A0  3D position of first corner of first triangle
//   A1  3D position of second corner of first triangle
//   A2  3D position of third corner of first triangle
//   B0  3D position of first corner of second triangle
//   B1  3D position of second corner of second triangle
//   B2  3D position of third corner of second triangle
// Returns true iff the two triangles intersect
bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2);
#endif
