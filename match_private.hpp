// Author: James Jonsson
// Date: 9-26-2014
//
// Users should not rely on the specific implentation within this file. It is
//   subject to change.

#ifdef CPM_MATCH_PRIVATE_HPP
#define CPM_MATCH_PRIVATE_HPP

#include <type_traits>

namespace cpm {
  
  template<class T>
  Match<T> match(const T& scrutinee)
  {
    return Match<T>{scrutinee};
  }
  
  
  template <class T>
  template <class U, class... Us>
  void Match<T>::with(Case<U>& head, Case<Us>&... tail)
  {
    bool result = head.match_against(scrutinee_);
    if (result) {  // We have a match.
      head.bind_from(scrutinee_);
    }
    else {  // Move on to the rest.
      with(tail...);
    }
  }
  
  template <class T>
  template <class U>
  void Match<T>::with(Case<U>& head)
  {
    bool result = head.match_against(scrutinee_);
    if (result) {  // We have a match.
      head.bind_from(scrutinee_);
    }
  }
  
  template <class T>
  explicit Match<T>::Match(const T& scrutinee) : scrutinee_(scrutinee)
  {
    // There's nothing else to be done.
  }
}

#endif
