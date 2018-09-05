#ifndef RAY_INTERSECT_BOX_H
#define RAY_INTERSECT_BOX_H
#include "BoundingBox.h"
#include "Ray.h"
#include <Eigen/Core>

// Intersect a ray with a **_solid_** box (careful: if the ray or `min_t` lands
// _inside_ the box this could still hit something stored inside the box, so
// this counts as a hit).
//
// Inputs:
//   ray  ray to consider
//   box  Axis-aligned solid box (presumably bounding some thing(s)
//   min_t  minimum parameteric distance along ray to consider for hits
//   max_t  maximum parameteric distance along ray to consider for hits
//// Outputs:
////   t  parametric distance along ray to hit
////   n  surface normal of hit (can use box face normal or set to (0,0,0) for
////     interior hits.
// Returns true if ray intersects the box between min_t and max_t

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t,
  double & t);
  //Eigen::Vector3d & n);
#endif
