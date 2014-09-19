// Author: James Jonsson
// Date: 8/26/14
//
// Compile with -std=c++11 (or C++14)
// Compiled successfully under Clang 3.4


#include <iostream>
#include <type_traits>
#include "pattern_matching.h"


// // Starts an if statement so that each case can be an if else.
// #define MATCH(X) auto _match_value = (X); if (false) {}
//
// // Calls case_helper to assign the match value to Y iff Y is an lvalue.
// #define CASE(Y) else if (case_helper(_match_value, (Y)))
// #define ENDMATCH else {}
//
// // We use function overloading so that the compiler will differentiate between
// //   lvalues and rvalues for us.
// template <typename T, typename U>
// bool case_helper(const T& match_value, U&& case_value) {
//   return match_value == case_value;
// }
//
// // We can't assign to a const case value, of course.
// template <typename T, typename U>
// bool case_helper(const T& match_value, const U& case_value) {
//   return match_value == case_value;
// }
//
// // If the case value is an lvalue, we can assign to it.
// template <typename T, typename U>
// bool case_helper(const T& match_value, U& case_value) {
//   T* pointer = &case_value;
//   *pointer = match_value;
//   return true;
// }


// Forward declare Pattern so that Helper can reference it.
template<typename... Ts>
class Pattern;


// Helper is useful as it gives easy access to the first element (that is, T).
//   Pattern cannot be formed the same way as it needs to be able to be empty.
template<typename T, typename... Ts>
class Helper {
public:
  typedef T first_type;
  typedef Pattern<Ts...> rest_type;
};


// The empty Pattern.
template<>
class Pattern<> {
public:
  constexpr static std::size_t size() { return 0; }
  typedef void first_type;
  typedef void rest_type;
};

// Pattern uses Helper to provide access to the first element and the tail elements.
template<typename... Ts>
class Pattern {
  
public:
  constexpr static std::size_t size() { return sizeof... (Ts); }
  
  // We know that this Pattern is not empty because an empty Pattern
  //   would have instantiated the previous definition (Pattern<>).
  typedef typename std::false_type is_empty_type;
  typedef typename Helper<Ts...>::first_type first_type;
  typedef typename Helper<Ts...>::rest_type rest_type;
};

// T and U must both be Pattern types.
template<typename T, typename U>
class Matcher {
public:
  
  // Check to make sure that every item of the input ,U, is a subclass of the corresponding
  //   class in the pattern, T.
  typedef typename
    std::conditional<(std::is_base_of<typename T::first_type, typename U::first_type>::value),
      typename Matcher<typename T::rest_type, typename U::rest_type>::is_match_type,
      std::false_type>::type
    is_match_type;
};

// The less specialized version of Matcher must not be instantiated,
//   as it will attempt to call "first" and "rest" on empty Patterns.
//   Hence, these more specialized versions correctly handle empty Patterns.
template<>
class Matcher<Pattern<>, Pattern<> > {
public:
  typedef typename std::true_type is_match_type;
};

template<typename T>
class Matcher<T, Pattern<> > {
public:
  typedef typename std::false_type is_match_type;
};

template<typename T>
class Matcher<Pattern<>, T > {
public:
  typedef typename std::false_type is_match_type;
};


// Test classes.
class Parent {
  virtual void f() {
    std::cout << "spam" << std::endl;
  }
};

class Child : public Parent {
  void f() {
    std::cout << "spam, spam, eggs, and spam" << std::endl;
  }
};

class Other {
  void f() {
    std::cout << "I don't like spam" << std::endl;
  }
};

int main() {
  
  // Some quick and dirty tests.
  static_assert(Matcher<Pattern<Parent>, Pattern<Child> >::is_match_type::value, "Fail!");
  static_assert(!Matcher<Pattern<Parent>, Pattern<Other> >::is_match_type::value, "Fail!");
  static_assert(Matcher<Pattern<Parent,Other>, Pattern<Child,Other> >::is_match_type::value, "Fail!");
  static_assert(!Matcher<Pattern<Parent,Parent>, Pattern<Other> >::is_match_type::value, "Fail!");
  
  
  int x, y, z = 1;
  std::string s, t;
  while (z) { 
  std::cout << "Enter a number. Enter 0 to proceed." << std::endl;
  std::cin >> x;
  MATCH(x)
    CASE(0) z = 0;
    CASE(1) {
      std::cout << "You entered 1. That's close to 0, but not close enough.";
      std::cout << std::endl;
    }
    CASE(y) std::cout << "y now equals " << y << std::endl;
  ENDMATCH
  }
  
  z = 1;
  while (z) { 
  std::cout << "Enter a string. Enter 'end' to quit." << std::endl;
  std::cin >> s;
  MATCH(s)
    CASE("end") z = 0;
    CASE(t) std::cout << "t now equals " << t << std::endl;
  ENDMATCH
  }  
  
  
  std::cout << "test complete." << std::endl;
  
  return 0;
}
