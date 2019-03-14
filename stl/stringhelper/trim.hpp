#ifndef __STL_XFS_TRIM_HPP__
#define __STL_XFS_TRIM_HPP__

#include <string>
#include <algorithm>
#include <functional>

namespace stl {
	namespace stringhelper {

inline std::string& trim_left(std::string& s, char c = ' ')
{
	std::string::iterator itr =
		std::find_if(s.begin(), s.end(),
		std::not1(std::function<bool(char)>(
		std::bind(std::equal_to<char>(), std::placeholders::_1, c))));
	s.erase(s.begin(), itr);
	return s;
}

inline std::string& trim_right(std::string& s, char c = ' ')
{
	std::string::reverse_iterator itr =
		std::find_if(s.rbegin(), s.rend(),
		std::not1(std::function<bool(char)>(
		std::bind(std::equal_to<char>(), std::placeholders::_1, c))));
	s.erase(itr.base(), s.end());
	return s;
}

inline std::string& trim(std::string& s, char c = ' ')
{
	return trim_left(trim_right(s, c), c);
}
	
}}


#endif //__STL_XFS_TRIM_HPP__