#ifndef CLOUD_POINT_H
#define CLOUD_POINT_H
#include "Object.h"
#include <Eigen/Core>
#include <memory>

struct CloudPoint final : public Object
{
  int i;
  const Eigen::MatrixXd & points;
  CloudPoint(const Eigen::MatrixXd & a_points, int a_i) : 
    points(a_points),
    i(std::move(a_i)) 
  { 
    box = BoundingBox(points.row(i),points.row(i));
  }
  // Object implementations (see Object.h)
  inline bool ray_intersect(
    const Ray& ray,
    const double min_t,
    const double max_t,
    double & t,
    std::shared_ptr<Object> & descendant) const override;
  inline bool point_squared_distance(
    const Eigen::RowVector3d & query,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant) const override;
};

// Implementation

inline bool CloudPoint::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const
{
  //Eigen::RowVector3d v = points.row(i)-ray.origin;
  //t = v.dot(ray.direction);
  //return t == v.norm()*ray.direction.norm();
  // "100% chance" a hit will not happen
  return false;
}

inline bool CloudPoint::point_squared_distance(
  const Eigen::RowVector3d & query,
  const double min_sqrd,
  const double max_sqrd,
  double & sqrd,
  std::shared_ptr<Object> & descendant) const
{
  const auto projection = points.row(i);
  // descendant doesn't make sense so it's not touched
  sqrd = (query-projection).squaredNorm();
  return (sqrd >= min_sqrd && sqrd < max_sqrd);
}

#endif
