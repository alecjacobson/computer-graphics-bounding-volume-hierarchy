#ifndef K_NEAREST_NEIGHBORS_USING_AABBTREE_H
#define K_NEAREST_NEIGHBORS_USING_AABBTREE_H
#include "AABBTree.h"
#include <Eigen/Core>
#include <memory>

void k_nearest_neighbors_using_AABBTree(
    const AABBTree & root,
    const Eigen::RowVector3d & query,
    const int K,
    Eigen::RowVectorXd & sqrD,
    Eigen::MatrixXd & projections,
    std::vector<std::shared_ptr<Object> > & descendants);
#endif
