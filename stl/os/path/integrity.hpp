#ifndef __STL_OS_PATH_INTEGRITY_HPP__
#define __STL_OS_PATH_INTEGRITY_HPP__

#include <string>
#include <stl/stringhelper/end_with.hpp>

namespace stl {
	namespace os {
		namespace path {

/** @ingroup path Function declaration
 * @brief add a seperator at the end of path.
 * @param[in] path path
 * @return the path
**/			
inline 
	std::string 
	integrity(
	const std::string& path)
{
#ifdef __os_windows__
	const char sep = '\\';
#else
	const char sep = '/';
#endif
	if(path.empty() || ::stl::stringhelper::end_with(path, sep))
	{
		return path;
	}
	return path + sep;
}

}}}

#endif //__STL_OS_PATH_INTEGRITY_HPP__