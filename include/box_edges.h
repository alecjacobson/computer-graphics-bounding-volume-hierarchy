#ifndef BOX_EDGES_H
#define BOX_EDGES_H

#include "AABBTree.h"
#include <Eigen/Core>
#include <memory> //std::shared_ptr
#include <limits> //std::numeric_limits

inline void box_edges(
  const std::shared_ptr<AABBTree> & tree,
  const int min_depth,
  const int max_depth,
  Eigen::MatrixXd & EV,
  Eigen::MatrixXi & EE);
inline void box_edges(
  const std::shared_ptr<AABBTree> & tree,
  Eigen::MatrixXd & EV,
  Eigen::MatrixXi & EE)
{ return box_edges(tree,0,std::numeric_limits<int>::max(),EV,EE); }
inline void box_edges(
  const std::vector<std::shared_ptr<Object> > & objects,
  Eigen::MatrixXd & EV,
  Eigen::MatrixXi & EE);

// Implementation

#include <igl/list_to_matrix.h>
#include <vector>

inline void box_edges(
  const std::shared_ptr<AABBTree> & tree,
  const int min_depth,
  const int max_depth,
  Eigen::MatrixXd & EV,
  Eigen::MatrixXi & EE)
{
  std::vector<std::shared_ptr<Object> > objects;

  std::list<std::shared_ptr<Object> > nodes;
  nodes.push_front(tree);
  while(!nodes.empty())
  {
    std::shared_ptr<Object> node = nodes.front();
    nodes.pop_front();
    std::shared_ptr<AABBTree> subtree =
      std::dynamic_pointer_cast<AABBTree>(node);
    if(!subtree || (subtree->depth >= min_depth && subtree->depth <= max_depth))
    {
      objects.emplace_back(node);
    }

    if(subtree)
    {
      if(subtree->left) nodes.push_back(subtree->left);
      if(subtree->right) nodes.push_back(subtree->right);
    }
  }
  return box_edges(objects,EV,EE);
}

inline void box_edges(
  const std::vector<std::shared_ptr<Object> > & objects,
  Eigen::MatrixXd & EV,
  Eigen::MatrixXi & EE)
{
  // This is a dumb way to visualize a lot of boxes.
  std::vector<std::vector<double> >  vEV;
  std::vector<std::vector<int> > vEE;
  for(const auto & node : objects)
  {
    const int n = vEV.size();
    vEE.push_back({n+0,n+1});
    vEE.push_back({n+0,n+2});
    vEE.push_back({n+0,n+6});
    vEE.push_back({n+1,n+3});
    vEE.push_back({n+1,n+7});
    vEE.push_back({n+2,n+3});
    vEE.push_back({n+2,n+4});
    vEE.push_back({n+3,n+5});
    vEE.push_back({n+4,n+5});
    vEE.push_back({n+4,n+6});
    vEE.push_back({n+5,n+7});
    vEE.push_back({n+6,n+7});
    const auto & min_corner = node->box.min_corner;
    const auto & max_corner = node->box.max_corner;
    vEV.push_back({min_corner(0),min_corner(1),min_corner(2)});
    vEV.push_back({min_corner(0),max_corner(1),min_corner(2)});
    vEV.push_back({max_corner(0),min_corner(1),min_corner(2)});
    vEV.push_back({max_corner(0),max_corner(1),min_corner(2)});
    vEV.push_back({max_corner(0),min_corner(1),max_corner(2)});
    vEV.push_back({max_corner(0),max_corner(1),max_corner(2)});
    vEV.push_back({min_corner(0),min_corner(1),max_corner(2)});
    vEV.push_back({min_corner(0),max_corner(1),max_corner(2)});
  }
  igl::list_to_matrix(vEV,EV);
  igl::list_to_matrix(vEE,EE);
}

#endif
