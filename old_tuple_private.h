// Author: James Jonsson
// Date: 9/20/2014
//
// Private. Do not rely on this specific implementation.

#include <type_traits>

#ifndef CPM_TUPLE_PRIVATE_H
#define CPM_TUPLE_PRIVATE_H

namespace cpm
{
  using std::enable_if_t;
  using std::nullptr_t;
  using std::is_lvalue_reference;
  using std::is_rvalue_reference;
  using std::is_const;
  
  // Predeclare Item to use it in Tuple.
  template <typename T, typename... Ts>
  class Item;
  
  
  template <>
  class Tuple<>
  {
  public:
    // Every empty tuple is equal to every other empty tuple.
    bool match(const Tuple<> pattern) {
      return true;
    }
    
    // Nothing to be done.
    void assign(Tuple<> pattern) {}
  };
  
  template <typename... Ts>
  class Tuple
  {
  public:
    Tuple(Ts... args) : first_(args...) {
      // Nothing else to do
    }
    
    // Accessor method.
    Item<Ts...>& first() {
      return first_;
    }
    
    // Check if this matches the pattern.
    template <typename... Us>
    bool match(Tuple<Us...> scrutinee) {
      return first().template match<Us...>(scrutinee.first());
    }
    
    // Assign values from this to variables in other.
    template <typename... Us>
    void assign(Tuple<Us...> scrutinee) {
      first().template assign<Us...>(scrutinee.first());
    }
    
  private:
    Item<Ts...> first_;
  };
  
  // Behaves differently based on whether T is an lvalue or not.
  template <typename T, typename Enable = void>
  class RLReference {};
  
  
  template <typename T>
  class RLReference<T, enable_if_t<((!is_lvalue_reference<T>::value) || is_const<T>::value)> >
  {
    T data_;
    
  public:
    explicit RLReference(T data) : data_(data) {
      // Nothing else to do
    }
    
    // Accessor method
    T data() {
      return data_;
    }
    
    template <typename U>
    bool match(RLReference<U> other) {
      return data() == other.data();
    }
    
    template <typename U>
    void assign(RLReference<U> other) {
      // Nothing to do here
    }
    

  };  

  template <typename T>
  class RLReference<T, enable_if_t<(is_lvalue_reference<T>::value && (!is_const<T>::value))> >
  {
    T data_;
    
  public:
    explicit RLReference(T data) : data_(data) {
      // Nothing else to do
    }

    // Accessor method
    T data() {
      return data_;
    }
    
    template <typename U>
    bool match(RLReference<U> other) {
      return true;
    }
    
    template <typename U>
    void assign(RLReference<U> other) {
      data() = other.data();
    }  
  };
  
  template <typename T, typename... Ts>
  class Item
  {
  public:
    Item(T data, Ts... rest) : data_(data), rest_(rest...) {
      // Nothing else to do
    }
    
    // Accessor methods
    RLReference<T>& data() {
      return data_;
    }
    Item<Ts...>& rest() {
      return rest_;
    }

    template <typename U, typename... Us>
    bool match(Item<U, Us...> other) {
      bool result = data().match(other.data());
      if (result) {  // If this item is not a match, no need to check the rest.
        result = rest().template match<Us...>(other.rest());
      }
      return result;
    }
    
    template <typename U, typename... Us>
    void assign(Item<U, Us...> other) {
      data().assign(other.data());
      rest().template assign<Us...>(other.rest());
    }
    
  private:
    RLReference<T> data_;
    Item<Ts...> rest_;
  };
  
  
  // If T is non-const and an lvalue reference, we can assign to it.
  template <typename T>
  class Item<T>
  {
  public:
    // Since the argument is a non-const lvalue reference, we store its pointer,
    //   so we can assign to it later.
    explicit Item(T data) : data_(data) {
      // Nothing else to do
    }
    
    // Accessor method
    RLReference<T>& data() {
      return data_;
    }
    
    // A variable counts as a match
    template <typename U>
    bool match(Item<U> other) {
      return data().match(other.data());
    }
    
    template <typename U>
    void assign(Item<U> other) {
      data().assign(other.data());
    }
    
  private:
    RLReference<T> data_;
  };
  

  template <typename... Ts>
  Tuple<Ts...> tpl(Ts... args) {
    return Tuple<Ts...>(args...);
  }

}

#endif
