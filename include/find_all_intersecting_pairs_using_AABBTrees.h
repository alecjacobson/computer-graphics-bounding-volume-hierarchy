#ifndef FIND_ALL_INTERSECTING_PAIRS_USING_AABBTREES_H
#define FIND_ALL_INTERSECTING_PAIRS_USING_AABBTREES_H
#include "AABBTree.h"
#include <memory>// std::shared_ptr
#include <utility>// std::pair
#include <vector>

// Find all intersecting pairs of _leaf boxes_ between one AABB tree and another
//
// Inputs:
//   rootA  root of first AABB Tree
//   rootB  root of second AABB Tree
// Output:
//   leaf_pairs  list of pairs {leaf_A,leaf_B} indicating that the box of leaf_A
//     intersects the box of leaf_B
void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs);
#endif
