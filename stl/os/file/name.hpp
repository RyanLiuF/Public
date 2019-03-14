#ifndef __STL_OS_FILE_NAME_HPP__
#define __STL_OS_FILE_NAME_HPP__

#include <string>

namespace stl {
	namespace os {
		namespace file {
/** @ingroup ofiles Function declaration
 * @brief get the name of file from the relative or absolute path.
 * @param[in] fullpath the name of file could be a relative or absolute path.
 * @return the name of file with suffix 
**/			
static 
	std::string 
	name(
	const std::string& 
	fullname)
{
#ifdef __os_windows__
	const char sep = '\\';
#else
	const char sep = '/';
#endif

	std::string::size_type pos = fullname.rfind(sep);
	if (pos == fullname.npos) return fullname;
	return fullname.substr(pos+1);
}

}}}

#endif //__STL_OS_FILE_NAME_HPP__