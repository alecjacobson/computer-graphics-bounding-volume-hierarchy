#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H

#include "Object.h"
#include <Eigen/Core>
#include <memory>

struct MeshTriangle : public Object
{
  public:
    // Pointer to mesh vertex position list
    const Eigen::MatrixXd & V;
    // Pointer to mesh indices list
    const Eigen::MatrixXi & F;
    // face index
    int f;
    // Record with vertex and face set this MeshTriangle references _and_
    // compute bounding box for this triangle.
    //
    // Inputs:
    //   V  pointer to mesh vertex list
    //   F  pointer to mesh face list
    //   f  index of triangle in _F
    // Side effects: inserts this triangle into .box (see Object.h)
    inline MeshTriangle(
      const Eigen::MatrixXd & V,
      const Eigen::MatrixXi & F,
      const int f);
    // Object implementations (see Object.h)
    inline bool ray_intersect(
      const Ray& ray,
      const double min_t,
      const double max_t,
      double & t,
      std::shared_ptr<Object> & descendant) const override;
    bool point_squared_distance(
      const Eigen::RowVector3d & query,
      const double min_sqrd,
      const double max_sqrd,
      double & sqrd,
      std::shared_ptr<Object> & descendant) const override
    {
      /* Not implemented, nor used in this assignment */
      assert(false);
      return false;
    }
};


// Implementation

#include "insert_triangle_into_box.h"
#include "ray_intersect_triangle.h"

inline MeshTriangle::MeshTriangle(
    const Eigen::MatrixXd & _V,
    const Eigen::MatrixXi & _F,
    const int _f): V(_V), F(_F), f(_f)
{
  insert_triangle_into_box(
    V.row(F(f,0)),
    V.row(F(f,1)),
    V.row(F(f,2)),
    box);
}

// Simple wrapper around `ray_intersect_triangle`
inline bool MeshTriangle::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const
{
  // descendant doesn't make sense so it's not touched
  return ray_intersect_triangle(
    ray,
    V.row(F(f,0)),
    V.row(F(f,1)),
    V.row(F(f,2)),
    min_t,
    max_t,
    t);
}


#endif
