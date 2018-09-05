#ifndef RAY_INTERSECT_TRIANGLE_MESH_BRUTE_FORCE_H
#define RAY_INTERSECT_TRIANGLE_MESH_BRUTE_FORCE_H
#include "Ray.h"
#include <Eigen/Core>
// Shoot a ray at a triangle mesh with $n$ faces and record the closest hit. Use
// a brute force loop over all triangles, aim for O(n) complexity but focus on
// correctness. This will be your reference solution.
//
// Inputs:
//   ray  ray being shot
//   V  #V by 3 list of mesh vertex positions
//   F  #F by 3 list of triangle indices into rows of V
//   min_t  minimum parametric distance along ray to consider 
//   max_t  maximum parametric distance along ray to consider 
// Outputs:
//   hit_t  parameteric distance of hit along ray
//   hit_f  index into F of triangle that was hit
// Returns true iff a valid hit was recorded
bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f);

#endif
