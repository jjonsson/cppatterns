// Author: James Jonsson
// Date: 9/18/14
//
// This file contains automated tests for pattern_matching.h
// Compiled successfully under Clang 3.4 with -std=c++1y

#include <string>
#include <iostream>
#include <list>
#include <functional>
#include <type_traits>
#include "pattern_matching.h"
#include "tuple.h"

using namespace std;

// Keep the tests in a list for easy access and scaling.
list<function<bool()> > tests =
{
  []{  // Test 1: integer matching
    MATCH(42)
      CASE(0) return false;
      CASE(42) return true;
    ENDMATCH
      return false;
  },
  []{  // Test 2: string matching
    MATCH("foo")
      CASE("bar") return false;
      CASE("baz") return false;
      CASE("foo") return true;
    ENDMATCH
    return false;
  },
  []{  // Test 3: multi-line blocks
    MATCH(12)
      CASE(11) {
        bool b = false;
        return b;
      }
      CASE(12) {
        bool b = true;
        return b;
      }
      CASE(13) return false;
    ENDMATCH
    return false;
  },
  []{  // Test 4: binding values to pattern variables
    char c = 'z';
    MATCH('j')
      CASE('a') return false;
      CASE(c) return c == 'j';
      CASE('j') return false;  // this case should not be reached
    ENDMATCH
    return false;
  },
  []{  // Test 5: tuples
    int x = 12;
    int y = 7;
    MATCH(cpm::tuple(42, 13, 'j'))
      CASE(cpm::tuple(42,  x, 'c')) return false;
      CASE(cpm::tuple(y, 11, 'j')) return false;
      CASE(cpm::tuple(x, y, 'j')) return (x == 42) && (y == 7);
      CASE(cpm::tuple(42, 13, 'j')) return false;  // should not be reached
    ENDMATCH
    return false;
  }
};

int main() {
  
  list<int> results;
  
  // Run the tests and save the results.
  int test_number = 1;
  for (auto& test : tests) {
    if (!test()) {
      results.push_back(test_number);
    }
    ++test_number;
  }
  
  if (results.empty()) {
    cout << "All tests passed!" << endl;
  }
  else {  // Print out which tests failed.
    string line = "Test";
    
    // Make "Test" plural if necessary.
    if (results.size() > 1) {
      line.push_back('s');
    }
    
    for (auto result : results) {
      line.append(" " + to_string(result) + ",");
    }
    
    // There's an extra comma at the end.
    cout << line.substr(0, line.size() - 1) << " failed." << endl;
  }
  
  return 0;
}
