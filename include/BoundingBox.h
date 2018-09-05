#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H
#include <Eigen/Core>

// Should change this name to AABB or AlignedBox
struct BoundingBox
{
  Eigen::RowVector3d min_corner;
  Eigen::RowVector3d max_corner;
  BoundingBox(
    Eigen::RowVector3d a_min_corner = 
      Eigen::RowVector3d::Constant(1,3, std::numeric_limits<double>::infinity()),
    Eigen::RowVector3d a_max_corner = 
      Eigen::RowVector3d::Constant(1,3,-std::numeric_limits<double>::infinity()))
    :
      min_corner(std::move(a_min_corner)),
      max_corner(std::move(a_max_corner))
  { }
  Eigen::RowVector3d center()
  {
    return 0.5*(max_corner + min_corner);
  }
};
#endif
