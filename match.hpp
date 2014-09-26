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
  
  // This function takes a single argument that it will treat as the scrutinee
  //   in a pattern match. This function returns a Match object that can
  //   perform pattern matching using the Match::with function.
  template<class T>
  Match<T> match(const T& scrutinee);
  
  // A Match object provides the with function that performs pattern matching.
  template<class T>
  class Match {
  public:
    template <class... Us>
    void with(Case<Us>&...);
  private:
    explicit Match(const T&);
    T scrutinee_;
    
    // Let's give match() access to the constructor.
    friend Match<T> match(const T&);
  };
}

#include "match_private.hpp"

#endif
