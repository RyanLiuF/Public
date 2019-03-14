#ifndef __STL_OS_PATH_IS_ABSOLUTE_HPP__
#define __STL_OS_PATH_IS_ABSOLUTE_HPP__

#include <regex>
#include <string>
#include <stl/stringhelper/begin_with.hpp>

namespace stl {
	namespace os {
		namespace path {
/** @ingroup path Function declaration
 * @brief verify the path is an absolute path or not.
 * @param[in] path path
 * @return 
 * 			- true  : absoulte path
 * 			- false : relative path
**/				
inline 
	bool 
	is_absolute(
	const std::string& path)
{
#ifdef __os_windows__
	return std::regex_match(path, std::regex("^[a-zA-Z]:(\\\\[^\\\\/:\\*\\?\"<>|]*)*$"));
#else
	return stl::stringhelper::begin_with(path, '/');
#endif

}

		}
	}
}

#endif //__STL_OS_PATH_IS_ABSOLUTE_HPP__