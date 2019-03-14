#ifndef __STL_OS_FILE_BASENAME_HPP__
#define __STL_OS_FILE_BASENAME_HPP__

#include <stl/os/file/name.hpp>
#include <algorithm>

namespace stl {
	namespace os {
		namespace file {

/** @ingroup ofiles Function declaration
 * @brief get the name of file from the relative or absolute path.
 * @param[in] fullpath the name of file could be a relative or absolute path.
 * @return the name of file without suffix 
**/
static 
	std::string 
	basename(const std::string& fullname)
{
	std::string n = name(fullname);
	std::string::reverse_iterator found = 
		std::find(n.rbegin(), n.rend(), '.');
	if(found == n.rend()) return n;
	n.erase((++found).base(), n.end());
	return n;
}

}}}


#endif //__STL_OS_FILE_BASENAME_HPP__