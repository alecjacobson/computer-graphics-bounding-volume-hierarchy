#include "MeshTriangle.h"
#include "triangle_triangle_intersection.h"
#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "Object.h"
#include "AABBTree.h"
#include "warnings.h"
#include "tictoc.h"
#include "visualize_aabbtree.h"
#include <igl/read_triangle_mesh.h>
#include <Eigen/Core>
#include <iostream>
#include <iomanip> // std::setw
#include <memory> // std::shared_ptr

int main(int argc, char * argv[])
{
  /////////////////////////////////////////////////////////////////////////////
  // TRIANGLE MESH INTERSECTION DETECTION
  /////////////////////////////////////////////////////////////////////////////
  std::cout<<"# Triangle Mesh Intersection Detection"<<std::endl;
  // Read in a triangle mesh
  Eigen::MatrixXd VA;
  Eigen::MatrixXi FA;
  igl::read_triangle_mesh(argc>1?argv[1]:"../data/knight.obj",VA,FA);
  std::cout<<"  |VA| "<<VA.rows()<<"  "<<std::endl;
  std::cout<<"  |FA| "<<FA.rows()<<"  "<<std::endl<<std::endl;
  Eigen::MatrixXd VB;
  Eigen::MatrixXi FB;
  igl::read_triangle_mesh(argc>2?argv[2]:"../data/cheburashka.obj",VB,FB);
  std::cout<<"  |VB| "<<VB.rows()<<"  "<<std::endl;
  std::cout<<"  |FB| "<<FB.rows()<<"  "<<std::endl<<std::endl;

  tic(); // Start the clock!
  std::vector<std::pair<int, int> > bf_pairs;
  // Brute force
  for(int fa = 0;fa<FA.rows();fa++)
  {
    for(int fb = 0;fb<FB.rows();fb++)
    {
      if(triangle_triangle_intersection(
          VA.row(FA(fa,0)),
          VA.row(FA(fa,1)),
          VA.row(FA(fa,2)),
          VB.row(FB(fb,0)),
          VB.row(FB(fb,1)),
          VB.row(FB(fb,2))))
      {
        bf_pairs.emplace_back(fa,fb);
      }
    }
  }
  std::cout<<"  | Method      | Time in seconds |"<<std::endl;
  std::cout<<"  |:------------|----------------:|"<<std::endl;
  std::cout<<"  | brute force | " << FLOAT15 << toc() << " |"<<std::endl;
  
  // Build trees for each
  tic();
  std::vector<std::pair<int, int> > tree_pairs;
  const auto triangle_tree = [](
      const Eigen::MatrixXd & V,
      const Eigen::MatrixXi & F)->std::shared_ptr<AABBTree>
  {
    // Because we use shared_ptrs it's OK that this list is destroyed
    std::vector<std::shared_ptr<Object> > triangles;
    triangles.reserve(F.rows());
    // Create a box for each triangle
    for(int f = 0;f<F.rows();f++)
    {
      triangles.emplace_back( std::make_shared<MeshTriangle>(V,F,f) );
    }
    return std::make_shared<AABBTree>(triangles);
  };
  std::shared_ptr<AABBTree> rootA = triangle_tree(VA,FA);
  std::shared_ptr<AABBTree> rootB = triangle_tree(VB,FB);
  std::cout<<"  | build trees | " << FLOAT15 << toc() << " |"<<std::endl;

  tic();
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > >
    leaf_pairs;
  // Broad phase
  find_all_intersecting_pairs_using_AABBTrees(rootA,rootB,leaf_pairs);
  for(const auto & pair : leaf_pairs)
  {
    std::shared_ptr<MeshTriangle> triangleA =
      std::static_pointer_cast<MeshTriangle>(pair.first);
    std::shared_ptr<MeshTriangle> triangleB =
      std::static_pointer_cast<MeshTriangle>(pair.second);
    const int fa = triangleA->f;
    const int fb = triangleB->f;
    // Narrow phase
    if(triangle_triangle_intersection(
        VA.row(FA(fa,0)),
        VA.row(FA(fa,1)),
        VA.row(FA(fa,2)),
        VB.row(FB(fb,0)),
        VB.row(FB(fb,1)),
        VB.row(FB(fb,2))))
    {
      tree_pairs.emplace_back(fa,fb);
    }
  }
  std::cout<<"  | use trees   | " << FLOAT15 << toc() << " |"<<std::endl;
  std::cout<<std::endl;

  // See if lists match
  diff_and_warn(  bf_pairs,"brute force",tree_pairs,"tree");
  diff_and_warn(tree_pairs,"tree",       bf_pairs,  "brute force");

  visualize_aabbtree(VA,FA,VB,FB,leaf_pairs);
}
