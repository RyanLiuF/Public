#ifndef __STL_OS_PATH_TEMPORARY_HPP__
#define __STL_OS_PATH_TEMPORARY_HPP__

#include <string>
#include <stl/os/path/integrity.hpp>
#include <stl/os/path/mkdir.hpp>

namespace stl {
	namespace os {
		namespace path {
/** @ingroup path Function declaration
 * @brief create temporary directory.
 * @param[in] integrated 
 * 						- true  : add the seperator at the end of temporary path
 * 						- false : do not revise the path
 * @return the temporary path
**/				
static 
	std::string 
	temporary(
	bool integrated = false) 
{
#ifdef __os_windows__
	std::string path("c:\\tmp");
#else
	std::string path("/tmp/temporary");
#endif

	struct temporary_creator
	{
		temporary_creator(const std::string& path) 
		{
			mkdir(path);
		}
	};
	static temporary_creator creator(path);
	return integrated ? integrity(path) : path;
}

}}}


#endif //__STL_OS_PATH_TEMPORARY_HPP__