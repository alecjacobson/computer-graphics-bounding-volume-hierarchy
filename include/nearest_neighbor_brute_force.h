#ifndef NEAREST_NEIGHBOR_BRUTE_FORCE_H
#define NEAREST_NEIGHBOR_BRUTE_FORCE_H

#include <Eigen/Core>

// Compute the nearest neighbor for a query in the set of $n$ points
// (rows of `points`). This should be a **_slow reference implementation_**. Aim
// for a computational complexity of $O(n)$ but focus on correctness. 
//
// Inputs:
//   points  #points by 3 list of points to search within
//   query  3D position fo the query
// Outputs:
//   I  index into points of closest point
//   sqrD  corresponding squared distance
//
void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD);

#endif

