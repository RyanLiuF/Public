#ifndef __STL_OS_PATH_TRUNCATE_HPP__
#define __STL_OS_PATH_TRUNCATE_HPP__

#include <string>
#include <algorithm>

namespace stl {
	namespace os {
		namespace path {
/** @ingroup path Function declaration
 * @brief truncate the path according to the seperator.
 * @param[in] path path
 * @return the truncate path
**/
static 
	std::string 
	truncate(
	const std::string& path)
{
#ifdef __os_windows__
	const char sep = '\\';
#else
	const char sep = '/';
#endif
	if(path.empty()) return path;

	std::string trun = path;
	std::string::reverse_iterator rfound = 
		std::find(trun.rbegin(), trun.rend(), sep);

	if(rfound == trun.rend()) return path;

	trun.erase((++rfound).base(), trun.end());
	return trun;
}

}}}

#endif //__STL_OS_PATH_TRUNCATE_HPP__