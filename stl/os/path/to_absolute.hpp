#ifndef __STL_OS_PATH_TO_ABSOLUTE_HPP__
#define __STL_OS_PATH_TO_ABSOLUTE_HPP__

#include <stl/os/path/revise.hpp>
#include <stl/os/path/current.hpp>
#include <stl/os/path/integrity.hpp>
#include <stl/os/path/truncate.hpp>
#include <stl/os/path/is_absolute.hpp>

#include <string.h>

namespace stl {
	namespace os {
		namespace path {
/** @ingroup path Function declaration
 * @brief transform a relative path to an absolute path.
 * @param[in] path a relative path
 * @return the absolute path
**/	
static 
	std::string 
	to_absolute(
	const std::string& path)
{
	if(is_absolute(path))
	{
		return revise(path);
	}
#ifdef __os_windows__
	const char* currentFolder = ".\\";
	const char* preFolder = "..\\";
#else
	const char* currentFolder = "./";
	const char* preFolder = "../";
#endif
	std::string regular = revise(path);
	std::string curpath = current();
	
	while(!regular.empty() && !curpath.empty()) 
	{
		if(::stl::stringhelper::begin_with(regular, currentFolder))
		{
			regular.erase(0, strlen(currentFolder));
		}
		else if(::stl::stringhelper::begin_with(regular, preFolder))
		{
			regular.erase(0, strlen(preFolder));
			curpath = truncate(curpath);
		}
		else 
		{
			break;
		}
	}
	return integrity(curpath) + regular;
}

}}}

#endif //__STL_OS_PATH_TO_ABSOLUTE_HPP__