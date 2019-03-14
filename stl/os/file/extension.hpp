#ifndef __STL_OS_FILE_EXTENSION_HPP__
#define __STL_OS_FILE_EXTENSION_HPP__

#include <stl/os/file/name.hpp>

namespace stl {
	namespace os {
		namespace file {

/** @ingroup ofiles Function declaration
 * @brief get the suffix of file from the relative or absolute path.
 * @param[in] fullpath the name of file could be a relative or absolute path.
 * @return  the suffix of file
**/
static 
	std::string 
	extension(const std::string& fullname)
{
	std::string n = name(fullname);
	std::string::reverse_iterator found = 
		std::find(n.rbegin(), n.rend(), '.');
	if(found == n.rend()) return "";
	n.erase(n.begin(), found.base());
	return n;
}

}}}

#endif //__STL_OS_FILE_EXTENSION_HPP__