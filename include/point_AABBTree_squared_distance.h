#ifndef POINT_AABBTREE_SQUARED_DISTANCE_H
#define POINT_AABBTREE_SQUARED_DISTANCE_H
#include "AABBTree.h"
#include "Object.h"
#include <memory> // std::shared_ptr
#include <Eigen/Core>

// Compute the distrance from a query point to the objects stored in a AABBTree
// using a priority queue. **_note:** this function is _not_ meant to be called
// recursively._
//
// Inputs:
//   query  3D query point
//   root  pointer to root of an AABB tree 
//   min_sqrd  minimum squared distance to consider (often 0)
//   max_sqrd  maximum squared distance to consider (often infinity)
// Outputs
//   sqrd  squared distance 
//   descendant  if minimal distance was found at a descendant, pass along a
//     pointer to that descendant (only necessary for hierarchical Objects)
bool point_AABBTree_squared_distance(
  const Eigen::RowVector3d & query,
  const std::shared_ptr<AABBTree> & root,
  const double min_sqrd,
  const double max_sqrd,
  double & sqrd,
  std::shared_ptr<Object> & descendant);

#endif
