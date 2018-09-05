#ifndef RAY_INTERSECT_TRIANGLE_H
#define RAY_INTERSECT_TRIANGLE_H
#include "Ray.h"
#include <Eigen/Core>

// Intersect a ray with a triangle
//
// Inputs:
//   ray  ray to consider
//   A  first triangle corner position
//   B  second triangle corner position
//   C  third triangle corner position
//   min_t  minimum parameteric distance along ray to consider for hits
//   max_t  maximum parameteric distance along ray to consider for hits
// Outputs:
//   t  parametric distance along ray to hit
// Returns true if ray intersects the triangle between min_t and max_t
bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t);
#endif

