#ifndef VISUALIZE_AABBTREE_H
#define VISUALIZE_AABBTREE_H

#include "AABBTree.h"
#include <Eigen/Core>
#include <igl/opengl/glfw/Viewer.h>

// Visualization of AABB tree around a mesh
inline void visualize_aabbtree(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const std::shared_ptr<AABBTree> & tree);

// Interactive vizualization of AABB tree around a point cloud
inline void visualize_aabbtree(
  const Eigen::MatrixXd & P,
  const std::shared_ptr<AABBTree> & tree);

// Visualization of boxes and intersecting triangles between two meshes
inline void visualize_aabbtree(
  const Eigen::MatrixXd & VA,
  const Eigen::MatrixXi & FA,
  const Eigen::MatrixXd & VB,
  const Eigen::MatrixXi & FB,
  const std::vector< std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & leaf_pairs);

// Implementation
#include "box_edges.h"

inline void visualize_aabbtree(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const std::shared_ptr<AABBTree> & tree)
{
  igl::opengl::glfw::Viewer v;
  v.data().set_mesh(V,F);
  v.data().set_face_based(true);
  Eigen::MatrixXd EV;
  Eigen::MatrixXi EE;
  box_edges(tree,EV,EE);
  v.data().set_edges(EV,EE,Eigen::RowVector3d(1,1,1));
  v.launch();
}

inline void visualize_aabbtree(
  const Eigen::MatrixXd & P,
  const std::shared_ptr<AABBTree> & tree)
{
  igl::opengl::glfw::Viewer v;
  int depth = 0;
  const auto update = [&P,&v,&tree,&depth]()
  {
    v.data().clear();
    v.data().point_size = 4;
    v.data().set_points(P,Eigen::RowVector3d(0,0,0));
    Eigen::MatrixXd EV;
    Eigen::MatrixXi EE;
    box_edges(tree,depth,depth,EV,EE);
    v.data().set_edges(EV,EE,Eigen::RowVector3d(1,1,1));
  };
  v.callback_key_pressed = [&v,&tree,&update,&depth](
    igl::opengl::glfw::Viewer & /*viewer*/,
    unsigned int key,
    int modifier)->bool
  {
    switch(key)
    {
      default:
        return false;
      case '.':
        depth++;
        break;
      case ',':
        depth = std::max(0,depth-1);
        break;
    }
    update();
    return true;
  };
  update();
  std::cout<<R"(
  ,/.      Decrease/Increase depth

)";
  v.launch();
}

inline void visualize_aabbtree(
  const Eigen::MatrixXd & VA,
  const Eigen::MatrixXi & FA,
  const Eigen::MatrixXd & VB,
  const Eigen::MatrixXi & FB,
  const std::vector< std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & leaf_pairs)
{
  //Eigen::MatrixXd V(VA.rows()+VB.rows(),3);
  //V<<VA,VB;
  //Eigen::MatrixXi F(FA.rows()+FB.rows(),3);
  //F<<FA, (FB.array()+VA.rows()).matrix();
  igl::opengl::glfw::Viewer v;
  std::vector<std::shared_ptr<Object> > BA,BB;
  BA.reserve(leaf_pairs.size());
  BB.reserve(leaf_pairs.size());
  //Eigen::MatrixXd CA(FA.rows(),3),CB(FB.rows(),3);
  const auto blue  = Eigen::RowVector3d(0.2,0.3,0.8);
  const auto orange = Eigen::RowVector3d(1,0.7,0.2);
  for(const auto & pair : leaf_pairs)
  {
    BA.emplace_back(pair.first);
    BB.emplace_back(pair.second);
    //// Hmm, these are the _candidate_ triangles so it's a bit deceiving to
    //// visualize them.
    //std::shared_ptr<MeshTriangle> triangleA =
    //  std::static_pointer_cast<MeshTriangle>(pair.first);
    //std::shared_ptr<MeshTriangle> triangleB =
    //  std::static_pointer_cast<MeshTriangle>(pair.second);
    //const int fa = triangleA->f;
    //const int fb = triangleB->f;
    //CA.row(fa) = Eigen::RowVector3d(1,0,0);
    //CB.row(fb) = Eigen::RowVector3d(0,1,1);
  }

  Eigen::MatrixXd EVA,EVB;
  Eigen::MatrixXi EEA,EEB;
  box_edges(BA,EVA,EEA);
  box_edges(BB,EVB,EEB);
  v.data().set_mesh(VA,FA);
  v.data().set_face_based(true);
  v.data().set_colors(Eigen::RowVector3d(244,165,130)/255.);
  v.data().set_edges(EVA,EEA,Eigen::RowVector3d(202,0,32)/255.);
  v.append_mesh();
  v.data().set_mesh(VB,FB);
  v.data().set_face_based(true);
  v.data().set_colors(Eigen::RowVector3d(146,197,222)/255.);
  v.data().set_edges(EVB,EEB,Eigen::RowVector3d(5,113,176)/255.);
  v.core.background_color.setConstant(0.8);
  v.launch();
}

#endif
