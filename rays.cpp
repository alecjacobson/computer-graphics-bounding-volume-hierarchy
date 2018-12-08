#include "ray_intersect_triangle_mesh_brute_force.h"
#include "Ray.h"
#include "MeshTriangle.h"
#include "Object.h"
#include "AABBTree.h"
#include "warnings.h"
#include "VectorXb.h"
#include "tictoc.h"
#include "visualize_aabbtree.h"
#include <igl/read_triangle_mesh.h>
#include <Eigen/Core>
#include <string> // std::stoi
#include <iostream>
#include <iomanip> // std::setw
#include <memory> // std::shared_ptr

int main(int argc, char * argv[])
{
  /////////////////////////////////////////////////////////////////////////////
  // RAY TRIANGLE MESH INTERSECTION
  /////////////////////////////////////////////////////////////////////////////
  std::cout<<"# Ray Triangle Mesh Intersection"<<std::endl;
  // Read in a triangle mesh
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  igl::read_triangle_mesh(argc>1?argv[1]:"../data/rubber-ducky.obj",V,F);
  std::cout<<"  |V| "<<V.rows()<<"  "<<std::endl;
  std::cout<<"  |F| "<<F.rows()<<"  "<<std::endl<<std::endl;
  // Make a bunch of random rays
  std::vector<Ray> rays;
  rays.reserve(argc>2?std::stoi(argv[2]):1000);
  // Default bounds on ray
  double min_t = 0;
  double max_t = std::numeric_limits<double>::infinity();
  for(int r = 0;r<rays.capacity();r++)
  {
    rays.emplace_back( Eigen::Vector3d::Random(), Eigen::Vector3d::Random());
  }
  std::cout<<"  Firing "<<rays.size()<<" rays..."<<std::endl<<std::endl;

  // Brute Force
  tic(); // Start the clock!
  Eigen::VectorXb bf_hit(rays.size());
  Eigen::VectorXd bf_t(rays.size());
  Eigen::VectorXi bf_I(rays.size());
  // loop over rays
  for(int r = 0;r<rays.size();r++)
  {
    bf_hit(r) = 
      ray_intersect_triangle_mesh_brute_force(
      rays[r], V, F, min_t, max_t, bf_t(r), bf_I(r));
  }
  std::cout<<"  | Method      | Time in seconds |"<<std::endl;
  std::cout<<"  |:------------|----------------:|"<<std::endl;
  std::cout<<"  | brute force | " << FLOAT15 << toc() << " |"<<std::endl;

  // Build a tree
  tic();
  std::vector<std::shared_ptr<Object> > triangles;
  triangles.reserve(F.rows());
  // Create a box for each triangle
  for(int f = 0;f<F.rows();f++)
  {
    triangles.emplace_back( std::make_shared<MeshTriangle>(V,F,f) );
  }
  std::shared_ptr<AABBTree> root = std::make_shared<AABBTree>(triangles);
  std::cout<<"  | build tree  | " << FLOAT15 << toc() << " |"<<std::endl;

  // Shoot rays at tree
  tic();
  Eigen::VectorXb tree_hit(rays.size());
  Eigen::VectorXd tree_t(rays.size());
  Eigen::VectorXi tree_I(rays.size());
  {
    // loop over rays
    for(int r = 0;r<rays.size();r++)
    {
      std::shared_ptr<Object> hit_object;
      tree_hit(r) = 
        root->ray_intersect(rays[r],min_t,max_t,tree_t(r),hit_object);
      if(tree_hit(r))
      {
        const std::shared_ptr<MeshTriangle> hit_triangle = 
          std::static_pointer_cast<MeshTriangle>(hit_object);
        tree_I(r) = hit_triangle->f;
      }
    }
    std::cout<<"  | use tree    | " << FLOAT15 << toc() << " |"<<std::endl;
  }

  // Check that solutions match.
  for(int r = 0;r<rays.size();r++)
  {
    WARN_IF_NOT_EQUAL(bf_hit,tree_hit,r);
    if(bf_hit(r) && tree_hit(r))
    {
      WARN_IF_NOT_APPROX(bf_t,tree_t,r);
      WARN_IF_NOT_EQUAL(bf_I,tree_I,r);
    }
  }

  // Visualize the tree
  visualize_aabbtree(V,F,root);
}
