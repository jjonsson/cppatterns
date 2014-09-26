// Author: James Jonsson
// Date: 9-26-2014
//
// This file provides a Case class which contains a pattern to be matched
//   against a scrutinee and code to be executed upon a match. The 

#ifdef CPM_CASE_HPP
#define CPM_CASE_HPP

#include <functional>
#include <tuple>

namespace cpm {
  // This function takes a pattern to match against the scrutinee and a
  //   function object to be executed upon a successful match. This function
  //   returns a Case object that has been properly constructed to work
  //   correctly when passed to a match withing an initializer list.
  template <class T>
  CaseBuilder<T> case(T&& pattern);  

  
  // This class exists to provide the overloaded operator |= for the purpose
  //   of defining each case in a readable way.
  template <class T>
  class CaseBuilder {
  public:
    // Used to build a Case object by combining a CaseBuilder and a function.
    Case<T> operator|=(std::function<void()>&&) const;
    Case<T> operator|=(const std::function<void()>&) const;
    
  private:
    CaseBuilder(Tuple<T>&& pattern);
    
    Tuple<T> pattern_;
    
    friend CaseBuilder<T> case(T&& pattern);
  };
  
  
  // This class represents one of multiple cases to be considered in a pattern
  //   match.
  template <class T>
  class Case;
}

#endif
