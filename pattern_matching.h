// Author: James Jonsson
// Date: 9/18/14
// 
// Include this file to use pattern matching.

#include "matcher.h"


#ifndef CPM_PATTERN_MATCHING_H
#define CPM_PATTERN_MATCHING_H


// Starts an if statement so that each case can be an if else.
#define MATCH(X) auto cpm_match_value = (X); if (false) {}

// Calls case_helper to assign the match value to Y iff Y is an lvalue.
#define CASE(Y) else if (cpm::Matcher::match(cpm_match_value, (Y)))
#define ENDMATCH else {}



#endif
