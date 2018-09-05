#ifndef K_NEAREST_NEIGHBORS_BRUTE_FORCE_H
#define K_NEAREST_NEIGHBORS_BRUTE_FORCE_H

#include <Eigen/Core>

// Compute the $k$-nearest neighbors for the query to the set of $n$ points
// (rows of `points`). This should be a **_slow reference implementation_**. Aim
// for a computational complexity of $O(nk)$ but focus on correctness. It's safe
// to assume K <= #points.
//
// Inputs:
//   points  #points by 3 list of points to search within
//   query  3D position fo the query
//   K  number of neighbors to find
// Outputs:
//   I  K-list of indices into points, each row sorted from closest
//     to $k$-th closest
//   sqrD  K-list of corresponding squared distances 
//
void k_nearest_neighbors_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  const int K,
  Eigen::RowVectorXi & I,
  Eigen::RowVectorXd & sqrD);

#endif
