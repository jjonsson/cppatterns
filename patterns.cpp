// Author: James Jonsson
// Date: 8/26/14
//
// Compile with -std=c++11 (or C++14)
// Compiled successfully under Clang 3.4


#include <iostream>
#include <type_traits>


// These macros will be used later to make this library usable.
#define MATCH(P) undefined
#define CASE(T) undefined


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
  
  // Check to make sure that every item of the input is a subclass of the corresponding
  //   class in the pattern.
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
  // All pattern matching is done at compile time, so these can be static_asserts.
  static_assert(Matcher<Pattern<Parent>, Pattern<Child> >::is_match_type::value, "Fail!");
  static_assert(!Matcher<Pattern<Parent>, Pattern<Other> >::is_match_type::value, "Fail!");
  static_assert(Matcher<Pattern<Parent,Other>, Pattern<Child,Other> >::is_match_type::value, "Fail!");
  static_assert(!Matcher<Pattern<Parent,Parent>, Pattern<Other> >::is_match_type::value, "Fail!");
  
  std::cout << Matcher<Pattern<Parent>, Pattern<Child> >::is_match_type::value << std::endl;
  std::cout << Matcher<Pattern<Parent>, Pattern<Other> >::is_match_type::value << std::endl;
  std::cout << Matcher<Pattern<Parent,Other>, Pattern<Child,Other> >::is_match_type::value << std::endl;
  std::cout << Matcher<Pattern<Parent,Parent>, Pattern<Other> >::is_match_type::value << std::endl;
  
  return 0;
}