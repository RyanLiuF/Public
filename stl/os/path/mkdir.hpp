#ifndef __STL_OS_PATH_MKDIR_HPP__
#define __STL_OS_PATH_MKDIR_HPP__

#include <string>
#include <stl/os/path/is_relative.hpp>
#include <stl/os/path/truncate.hpp>
#include <stl/os/path/to_absolute.hpp>

#ifdef __os_windows__
#include <direct.h>
#include <io.h>
#else
#include <sys/stat.h>
#endif

namespace stl {
	namespace os {
		namespace path {
/** @ingroup path Function declaration
 * @brief recursively create directory.
 * @param[in] path path
 * @param[in] recursion 
 * 							- true  : recursive
 * 							- false : non-recursive
 * @param[in] flag path permissions
 * @return 
 * 			- 0  : success
 * 			- non-zero : failed
**/			
inline 
	int
	mkdir(
	const std::string& path, 
	bool recursion = true,
	int flag = 0x755)
{
	struct mkdirhelper {
		static int mkdir(const std::string& path, int flag)
		{
#ifdef __os_windows__
			return ::mkdir(path.c_str());
#else
			return ::mkdir(path.c_str(), flag);
#endif
		}
	};

//	std::string absolute = to_absolute(path);//spend more time
	std::string absolute = path;
	if(!recursion)
	{
		return mkdirhelper::mkdir(absolute, flag);
	}

	int ret = 0;
	if(::access(absolute.c_str(), F_OK))
	{
		ret = mkdir(truncate(absolute), recursion, flag);
		if(ret == 0)
		{
			return mkdirhelper::mkdir(absolute, flag);
		}
	}
	return ret;
}

}}}

#endif //__STL_OS_PATH_MKDIR_HPP__