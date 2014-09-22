// Author: James Jonsson
// Date: 9/20/2014
//
// This header provides a tuple class that can be used in pattern matching.
//   When a tuple was constructed using variables, those variables will be
//   assigned to upon a successful pattern match.

#ifndef CPM_TUPLE_H
#define CPM_TUPLE_H

namespace cpm
{
  template <typename... Ts>
  class Tuple;
  
  template <typename... Ts>
  Tuple<Ts&&...> tuple(Ts&&...);
}

#include "tuple_private.h"

#endif