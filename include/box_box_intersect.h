#ifndef BOX_BOX_INTERSECT_H
#define BOX_BOX_INTERSECT_H
#include "BoundingBox.h"
// Determine if two bounding boxes intersect
//
// Inputs:
//   A  first bounding box
//   B  second bounding box
// Returns true iff bounding boxes overlap
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B);
#endif
