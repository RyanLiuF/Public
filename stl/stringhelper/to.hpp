#ifndef __STL_STRINGHELPER_TO_HPP__
#define __STL_STRINGHELPER_TO_HPP__

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stl/lexical/as.hpp>

namespace stl {
	namespace stringhelper {
static 
	std::string 
	to(
	const std::string& str,
	const std::function<int(int)> & what) 
{
	std::string result = str;
	std::transform(str.begin(), str.end(), result.begin(), what);
	return result;
}

inline std::string toupper(const std::string& str) 
{
	return to(str, ::toupper);
}

inline std::string tolower(const std::string& str)
{
	return to(str, ::tolower);
}

template<typename _InIt>
inline std::string 
	stringify(_InIt first, _InIt last, const std::string& sep)
{
	std::string tmp;
	for(; first != last; first++)
	{
		tmp += stl::lexical::as((int)(*first&0xFF));
		tmp += sep;
	}
	return tmp;
}

template<typename T>
inline void
	hexify(const std::string& str, std::vector<T>& dest)
{
	for(size_t i=0; i<str.size(); i+=2)
	{
		dest.push_back((T)stl::lexical::as(str.substr(i, 2)));
	}
}

}}

#endif //__STL_STRINGHELPER_TO_HPP__