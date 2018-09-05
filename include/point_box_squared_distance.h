#ifndef POINT_BOX_SQUARED_DISTANCE_H
#define POINT_BOX_SQUARED_DISTANCE_H
#include "BoundingBox.h"
#include <Eigen/Core>
// Compute the squared distance between a query point and a box
//
// Inputs:
//   query  3D position of query point
//   box  3D axis-aligned bounding box
// Returns squared distance to closest point on bounding box to query
double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box);
#endif
