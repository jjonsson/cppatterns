// Author: James Jonsson
// Date: 9-26-2014
//
// Users should not rely on the specific implentation within this file. It is
//   subject to change.

#ifdef CPM_MATCH_PRIVATE_HPP
#define CPM_MATCH_PRIVATE_HPP

namespace cpm {
  template<class T, class U>
  std::function<void(case_list_t<U>)> match(const T& scrutinee);
  {
    return [](case_list_t<U> cases) {
      for (auto& c : cases) {
        bool result = c.match_against(scrutinee);
        if (result) {
          c.assign_from(scrutinee);
          
          // If there is a match, we don't need to look at anything else.
          break;
        }
      };
    };
  }
}

#endif
