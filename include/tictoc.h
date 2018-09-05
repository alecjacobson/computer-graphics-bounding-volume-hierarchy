#ifndef TIC_TOC_H
#define TIC_TOC_H
#include <igl/get_seconds.h>

static double g_time;
inline void tic()
{
  g_time = igl::get_seconds();
}
inline double toc()
{
  return igl::get_seconds() - g_time;
}

#endif
