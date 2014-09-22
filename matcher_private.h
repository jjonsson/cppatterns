// Author: James Jonsson
// Date: 9/20/2014
//
// Private. Do not rely on this specific implementation.

#ifndef CPM_MATCHER_PRIVATE_H
#define CPM_MATCHER_PRIVATE_H

namespace cpm {
  
  // Match tuples and assign variables within the tuple.
  template <typename... Ts, typename... Us>
  bool Matcher::match(Tuple<Ts...> scrutinee, Tuple<Us...> pattern) {
    bool result = pattern.match(scrutinee);
    if (result) {
      pattern.assign(scrutinee);
    }
    return result;
  }
  
  // We can't assign to a const pattern, of course.
  template <typename T, typename U>
  bool Matcher::match(const T& scrutinee, const U& pattern) {
    return scrutinee == pattern;
  }

  // Don't try to assign to an rvalue.
  template <typename T, typename U>
  bool Matcher::match(const T& scrutinee, U&& pattern) {
    return scrutinee == pattern;
  }

  // If the case value is an lvalue, we can assign to it.
  template <typename T, typename U>
  bool Matcher::match(const T& scrutinee, U& pattern) {
    pattern = scrutinee;
    return true;
  }
  
}

#endif
