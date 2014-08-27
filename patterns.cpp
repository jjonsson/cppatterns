#include <iostream>
#include <type_traits>

#define MATCH(P) undefined

#define CASE(T) undefined


template<typename... Ts>
class Pattern;

template<typename U, typename... Us>
class Helper {
public:
  typedef U first_type;
  typedef Pattern<Us...> rest_type;
};

template<>
class Pattern<> {
public:
  constexpr static std::size_t size() { return 0; }
  typedef void first_type;
  typedef void rest_type;
};

template<typename... Ts>
class Pattern {
  
public:
  constexpr static std::size_t size() { return sizeof... (Ts); }
  typedef
    typename std::conditional<(sizeof... (Ts)) == 0, std::true_type, std::false_type>::type
    is_empty_type;
  typedef
    typename std::conditional<
      is_empty_type::value,
      void,
      typename Helper<Ts...>::first_type
    >::type
    first_type;
  typedef
    typename std::conditional<
      is_empty_type::value,
      void,
      typename std::enable_if<(size() > 0), typename Helper<Ts...>::rest_type
    >::type>::type
    rest_type;
};

// T and U should both be Pattern types.
template<typename T, typename U>
class Matcher {
public:
  typedef typename
  std::conditional<(T::size() != U::size()), std::false_type, 
    typename std::conditional<(T::size() == 0), std::true_type, 
      typename std::conditional<(std::is_base_of<typename T::first_type, typename U::first_type>::value),
        typename Matcher<typename T::rest_type, typename U::rest_type>::is_match_type,
        std::false_type>::type>::type>::type is_match_type;
};

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
  // Parent* x = new Parent();
  // MATCH(x) {
  //   CASE(Child) std::cout << "child" << std::endl;
  //   CASE(Other) std::cout << "other" << std::endl;
  //   std::cout << "default" << endl;
  // }
  std::cout << Matcher<Pattern<Parent>, Pattern<Child> >::is_match_type::value << std::endl;
  std::cout << Matcher<Pattern<Parent>, Pattern<Other> >::is_match_type::value << std::endl;
  std::cout << Matcher<Pattern<Parent,Other>, Pattern<Child,Other> >::is_match_type::value << std::endl;
  std::cout << Matcher<Pattern<Parent,Parent>, Pattern<Other> >::is_match_type::value << std::endl;
  
  return 0;
}