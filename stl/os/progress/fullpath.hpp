#ifndef __STL_OS_PROGRESS_FULLPATH_HPP__
#define __STL_OS_PROGRESS_FULLPATH_HPP__

#include <algorithm>

#include <stl/compatible.h>
#include <stl/os/progress/fullname.hpp>

namespace stl {
	namespace os {
		namespace progress {
/** @ingroup progress Function declaration
 * @brief get the execution path of program.
 * @return the path
**/
static std::string fullpath() 
{
#ifdef __os_windows__
	char sep = '\\';
#else
	char sep = '/';
#endif
	std::string name = fullname();
	if (name.empty()) return name;

	std::string::reverse_iterator found = 
		std::find_if(name.rbegin(), name.rend(), 
			std::bind(
				std::equal_to<std::string::value_type>(), 
				std::placeholders::_1, 
				sep));
	if (found == name.crend()) return name;
	name.erase((++found).base(), name.end());
	return name;
}
		
}}}

#endif //__STL_OS_PROGRESS_FULLPATH_HPP__