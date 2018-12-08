#ifndef OBJECT_H
#define OBJECT_H

// Empty "boxable" and hierarchical object class
//
#include "BoundingBox.h"
#include <Eigen/Core>
#include <memory>
struct Ray;
struct Object
{
  BoundingBox box;
  // Intersect this object with a ray
  //
  // Inputs:
  //   ray  ray being shot
  //   min_t  minimum parametric distance along ray to consider 
  //   max_t  maximum parametric distance along ray to consider 
  // Object:
  //   t  parameteric distance of hit along ray
  //   descendant  if the hit was found at a descendant, pass along a pointer to
  //     that descendant (only necessary for hierarchical Objects)
  // Returns true iff a valid hit was recorded
  virtual bool ray_intersect(
    const Ray& ray,
    const double min_t,
    const double max_t,
    double & t,
    std::shared_ptr<Object> & descendant) const = 0;
  // Compute squared distance from the given query point to this object.
  //
  // Inputs:
  //   query  3D query point
  //   min_sqrd  minimum squared distance to consider
  //   max_sqrd  maximim squared distance to consider
  // Outputs:
  //   sqrd  squared distance 
  //   descendant  if minimal distance was found at a descendant, pass along a
  //     pointer to that descendant (only necessary for hierarchical Objects)
  // Returns true iff a valid squared distance was recorded
  virtual bool point_squared_distance(
    const Eigen::RowVector3d & query,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant) const = 0;
};

#endif
