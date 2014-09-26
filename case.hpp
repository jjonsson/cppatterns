// Author: James Jonsson
// Date: 9-26-2014
//
// This file provides a Case class which contains a pattern to be matched
//   against a scrutinee and code to be executed upon a match. The 

#ifdef CPM_CASE_HPP
#define CPM_CASE_HPP

#include <functional>

namespace cpm {
  template <class T>
  Case<T> case(T pattern, std::function<void()>);
  
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