// Author: James Jonsson
// Date: 9-26-2014
//
// This file provides a function, match, which is meant to be called by the
//   user in order to perform pattern matching.

#ifdef CPM_MATCH_HPP
#define CPM_MATCH_HPP

#include <functional>
#include <initializer_list>
#include "case.hpp"

namespace cpm {  
  // A list of cases in curly braces passed to a match function.
  template<class T>
  using case_list_t = std::initializer_list< Case< T > >;
  
  // This function takes a single argument that it will treat as the scrutinee
  //   in a pattern match. This function returns a function object that takes
  //   an initializer list of Cases (each one containing a pattern) to match
  //   against the scrutinee.
  template<class T, class U>
  std::function<void(case_list_t<U>)> match(const T& scrutinee);
}

#include "match_private.hpp"

#endif
