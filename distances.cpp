#include "nearest_neighbor_brute_force.h"
#include "point_AABBTree_squared_distance.h"
#include "CloudPoint.h"
#include "Object.h"
#include "AABBTree.h"
#include "warnings.h"
#include "VectorXb.h"
#include "tictoc.h"
#include "visualize_aabbtree.h"
#include <igl/read_triangle_mesh.h>
#include <Eigen/Core>
#include <iostream>
#include <string> // std::stoi
#include <iomanip> // std::setw
#include <memory> // std::shared_ptr

int main(int argc, char * argv[])
{
  /////////////////////////////////////////////////////////////////////////////
  // POINT CLOUD DISTANCE QUERY
  /////////////////////////////////////////////////////////////////////////////
  std::cout<<"# Point Cloud Distance Queries"<<std::endl;
  // Prepare a random list of points in our set and random queries
  Eigen::MatrixXd points =  
    Eigen::MatrixXd::Random(argc>1?std::stoi(argv[1]):100000,3);
  Eigen::MatrixXd queries = 
    Eigen::MatrixXd::Random(argc>2?std::stoi(argv[2]):10000,3);

  std::cout<<"    |points|: "<< points.rows()<<std::endl;
  std::cout<<"  |querires|: "<<queries.rows()<<std::endl<<std::endl;
  // Brute Force
  tic(); // Start the clock!
  Eigen::VectorXd bf_sqrD(queries.rows());
  Eigen::VectorXi bf_I   (queries.rows());
  // Loop over queries
  for(int i = 0;i < queries.rows(); i++)
  {
    nearest_neighbor_brute_force(points,queries.row(i),bf_I(i),bf_sqrD(i));
  }
  std::cout<<"  | Method      | Time in seconds |"<<std::endl;
  std::cout<<"  |:------------|----------------:|"<<std::endl;
  std::cout<<"  | brute force | " << FLOAT15 << toc() << " |"<<std::endl;

  tic();
  // Build a tree
  std::vector<std::shared_ptr<Object> > point_indices;
  // Put a reference to each point in a boxable object
  point_indices.reserve(points.rows());
  for(int i = 0;i<points.rows();i++)
  {
    point_indices.emplace_back(std::make_shared<CloudPoint>(points,i));
  }
  // Build tree
  std::shared_ptr<AABBTree> root = std::make_shared<AABBTree>(point_indices);
  std::cout<<"  | build tree  | " << FLOAT15 << toc() << " |"<<std::endl;

  tic();
  Eigen::VectorXd tree_sqrD(queries.rows());
  Eigen::VectorXi tree_I   (queries.rows());
  // Loop over queries
  for(int i = 0;i < queries.rows(); i++)
  {
    Eigen::RowVector3d query = queries.row(i);
    std::shared_ptr<Object> closest_object;
    const double inf = std::numeric_limits<double>::infinity();
    point_AABBTree_squared_distance(
      query,root,0,inf,tree_sqrD(i),closest_object);
    if(closest_object)
    {
      tree_I(i) = std::static_pointer_cast<CloudPoint>(closest_object)->i;
    }else
    {
      tree_I(i) = -1;
    }
  }
  std::cout<<"  | use tree    | " << FLOAT15 << toc() << " |"<<std::endl;
 
  // Check that solutions match.
  for(int i = 0;i < queries.rows(); i++)
  {
    WARN_IF_NOT_EQUAL(bf_I,tree_I,i);
    WARN_IF_NOT_APPROX(bf_sqrD,tree_sqrD,i);
  }
  visualize_aabbtree(points,root);
  
}
