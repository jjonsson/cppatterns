// Author: James Jonsson
// Date: 9/20/2014
//
// Matcher is a utility class that provides the function that actually does
//   the pattern matching.

#include "tuple.h"

#ifndef CPM_MATCHER_H
#define CPM_MATCHER_H

namespace cpm
{

  // Determines if a pattern is a match and assigns variables to the values they matched.
  // We use function overloading so that the compiler will differentiate between
  //   lvalues and rvalues for us.
  class Matcher
  {
  public:
    template <typename... Ts, typename... Us>
    static bool match(Tuple<Ts...> scrutinee, Tuple<Us...> pattern);
    
    template <typename T, typename U>
    static bool match(const T& scrutinee, const U& pattern);
    
    template <typename T, typename U>
    static bool match(const T& scrutinee, U&& pattern);
    
    template <typename T, typename U>
    static bool match(const T& scrutinee, U& pattern);
  };

}

#include "matcher_private.h"

#endif