// Author: James Jonsson
// Date: 9-26-2014
//
// Users should not rely on the specific implentation within this file. It is
//   subject to change.

#include <utility>

#ifdef CPM_CASE_PRIVATE_HPP
#define CPM_CASE_PRIVATE_HPP

namespace cpm {

  //
  // case helper function
  //

  template <class T>
  CaseBuilder<T> case(T&& pattern)
  {
    return CaseBuilder<T>(tpl(std::forward(pattern)));
  }
  
  
  
  //
  // CaseBuilder class
  //
  
  template <class T>
  Case<T> CaseBuilder<T>::operator|=(std::function<void()>&& func) const
  {
    return Case<T>(pattern_, std::forward(func));
  }

  template <class T>
  Case<T> CaseBuilder<T>::operator|=(const std::function<void()>& func) const
  {
    return Case<T>(pattern_, func);
  }
  
  template <class T>
  CaseBuilder<T>::CaseBuilder(Tuple<T>&& pattern)
    : pattern_(std::move(pattern))
  {
    // There's nothing else to do.
  }



  //
  // Case class
  //

  template <class T>
  class Case {
  private:
    // data members
    Tuple<T> pattern_;
    std::function<void()> func_;
    
    // constructors
    Case(const Tuple<T>& pattern, std::function<void()>&& func)
      : pattern_(pattern), func_(std::move(func))
    {
      // There's nothing else to do.
    }
    
    Case(const Tuple<T>& pattern, const std::function<void()>& func)
      : pattern_(pattern), func_(func)
    {
      // There's nothing else to do.
    }
    
    // Actually perform the match and return the result.
    template <class U>
    bool match_against(const U& scrutinee) const
    {
      // TODO: Implement function body after implementing Tuple.
      
      return false;
    }
    
    // Bind values to lvalue references.
    template <class U>
    void bind_from(const U& scrutinee)
    {
      // TODO: Implement function body after implementing Tuple.
    }
  };

}

#endif