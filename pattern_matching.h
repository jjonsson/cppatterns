// Author: James Jonsson
// Date: 9/18/14
// Use -std=c++11 (or C++14)

#ifndef JPJ_CPM_PATTERN_MATCHING_H
#define JPJ_CPM_PATTERN_MATCHING_H

// Starts an if statement so that each case can be an if else.
#define MATCH(X) auto jpj_cpm_match_value = (X); if (false) {}

// Calls case_helper to assign the match value to Y iff Y is an lvalue.
#define CASE(Y) else if (jpj::cpm::case_helper(jpj_cpm_match_value, (Y)))
#define ENDMATCH else {}

namespace jpj {
  namespace cpm {

    // We use function overloading so that the compiler will differentiate between
    //   lvalues and rvalues for us.
    template <typename T, typename U>
    bool case_helper(const T& match_value, U&& case_value) {
      return match_value == case_value;
    }

    // We can't assign to a const case value, of course.
    template <typename T, typename U>
    bool case_helper(const T& match_value, const U& case_value) {
      return match_value == case_value;
    }

    // If the case value is an lvalue, we can assign to it.
    template <typename T, typename U>
    bool case_helper(const T& match_value, U& case_value) {
      T* pointer = &case_value;
      *pointer = match_value;
      return true;
    }
  }
}

#endif
