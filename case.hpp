// Author: James Jonsson
// Date: 9-26-2014
//
// This file provides a Case class which contains a pattern to be matched
//   against a scrutinee and code to be executed upon a match. The 

#ifdef CPM_CASE_HPP
#define CPM_CASE_HPP

#include <functional>

namespace cpm {
  // This function takes a pattern to match against the scrutinee and a
  //   function object to be executed upon a successful match. This function
  //   returns a Case object that has been properly constructed to work
  //   correctly when passed to a match withing an initializer list.
  template <class T>
  Case<T> case(T pattern, std::function<void()> func_success);
  
  
  // This class represents one of multiple cases to be considered in a pattern
  //   match.
  template <class T>
  class Case {
  public:
    template <class U>
    bool match_against(const U& scrutinee);
    void assign_from(const U& scrutinee);
  private:
  };
}

#endif
