#ifndef __STL_OS_PATH_REVISE_HPP__
#define __STL_OS_PATH_REVISE_HPP__

#include <string>
#include <algorithm>
#include <stl/stringhelper/trim.hpp>

namespace stl {
	namespace os {
		namespace path {

/** @ingroup path Function declaration
 * @brief revise the seperator of path
 * @param[in] path path
 * @return path
**/
inline 
	std::string 
	revise(
	const std::string& path)
{
#ifdef __os_windows__
	const char originSep = '/';
	const char aimSep = '\\';
#else 
	const char originSep = '\\';
	const char aimSep = '/';
#endif 
	std::string ret = path;
	std::replace(ret.begin(), ret.end(), originSep, aimSep);
#ifdef __os_windows__
	::stl::stringhelper::trim_left(ret, '\\');
#endif
	return ret;
}

}}}

#endif //__STL_OS_PATH_REVISE_HPP__