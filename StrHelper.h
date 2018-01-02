#pragma once
/////////////////////////////////////////////////////////////////////
// StrHelper.h - trim utilities for std::string                    //
// ver 1.1                                                         //
// Source: Evan Teran                                              //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////
/*
 * Source from consultation with Dr. Google: 
 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 *
 * Note:
 * - isspace(char), used below, fails with exception on certain non-ascii 
 *   characters. For example, some of the Chinese characters will do that.
 * - To fix need to use isspace(char, std::locale). You can't directly
 *   do that with the code below, due to the way it's using std algorithms,
 *   but it's not too hard to do.
 * - For our purposes this should not cause a problem.
 * ToDo:
 * - convert to using isspace(char, std::locale)
 * - add cpp file with test stub and test.
 */
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>

// trim from start
static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
    std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
    std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
  try { return ltrim(rtrim(s)); }
  catch (...) { return std::string("trimming error"); }
}
