#ifndef __STL_OS_PATH_ACCESS_HPP__
#define __STL_OS_PATH_ACCESS_HPP__

#include <stl/os/path/to_absolute.hpp>

/** @defgroup path stl/os/path
 * @brief Implement of path operation.
 *
**/

namespace stl {
	namespace os {
		namespace path {
/** @ingroup path Function declaration
 * @brief get the access of path.
 * @param[in] fullpath the path could be a relative or absolute path
 * @return 
 *          - 0  : path exists
 *          - non-zero : path not exists     
**/				
static 
	int 
	access(
	const std::string& path, 
	int mode = F_OK)
{
	struct stat info;
	std::string absolute = stl::os::path::to_absolute(path);
	int ret = ::access(absolute.c_str(), mode);
	ret = ret || stat(absolute.c_str(), &info);
#ifdef __os_windows__
	return ret || !((info.st_mode & _S_IFMT) == _S_IFDIR);
#else 
	return ret || !S_ISDIR(info.st_mode);
#endif
}

		}
	}
}


#endif //__STL_OS_PATH_ACCESS_HPP__