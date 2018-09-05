#ifndef WARNINGS_H
#define WARNINGS_H

// Three warning helper functions:
//
// WARN_IF_NOT_EQUAL
// WARN_IF_NOT_APPROX
// diff_and_warn
//
// One printer helper macro
//
// FLOAT15
//

#include <iostream>
#include <iomanip> // std::setw, std::setprecision, std::fixed
// Macro for prettier printing of numbers
#define FLOAT15 std::fixed << std::setw(15) << std::setprecision(11)
// Macros to help debug Eigen matrices
// if A(r) != B(r) print a warning
#define WARN_IF_NOT_EQUAL(A,B,r) \
  do { \
  if(A(r) != B(r)) \
  { \
    std::cout<<"Error: "<< \
      #A"("<<r<<") ("<<A(r)<<")"<< \
      " != "<< \
      #B"("<<r<<") ("<<B(r)<<")"<<std::endl; \
    continue; \
  } \
  } while (0)
// if |A(r)-B(r)|>epsilon print a warning
#define WARN_IF_NOT_APPROX(A,B,r) \
  do { \
  if(std::abs(A(r)-B(r))>1e-10) \
  { \
    std::cout<<"Error: "<< \
      #A"("<<r<<") ("<<A(r)<<")"<< \
      " != "<< \
      #B"("<<r<<") ("<<B(r)<<")"<<std::endl; \
    continue; \
  } \
  } while (0)

#include <vector>
#include <algorithm>
#include <string>
#include <utility>
inline void diff_and_warn(
  std::vector<std::pair<int, int> > X_pairs,
  const std::string X_name,
  std::vector<std::pair<int, int> > Y_pairs,
  const std::string Y_name)
{
  // http://www.cplusplus.com/reference/algorithm/set_symmetric_difference/
  std::vector<std::pair<int,int> > diff(X_pairs.size());
  std::sort (X_pairs.begin(),X_pairs.end());
  std::sort (Y_pairs.begin(),Y_pairs.end());
  std::vector<std::pair<int,int> >::iterator it = 
    std::set_difference(
      X_pairs.begin(), X_pairs.end(),
      Y_pairs.begin(), Y_pairs.end(),
      diff.begin());
  diff.resize(it-diff.begin());
  if(diff.size() > 0)
  {
    std::cout<<"Error: Intersecting pairs found using "<<X_name<<
      " but not "<<Y_name<<":"<<std::endl;
    for (it=diff.begin(); it!=diff.end(); ++it)
    {
      std::cout << "  "<<it->first << "," << it->second << std::endl;
    }
  }
}
#endif 
