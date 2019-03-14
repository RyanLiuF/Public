#ifndef __STL_OS_FILE_ACCESS_HPP__
#define __STL_OS_FILE_ACCESS_HPP__

#include <stl/os/path/to_absolute.hpp>

namespace stl {
	namespace os {
		namespace file {
/** @ingroup ofiles Function declaration
 * @brief get the access of file.
 * @param[in] fullpath the name of file could be a relative or absolute path
 * @return 
 *          - 0  : file exists
 *          - non-zero : file not exists     
**/			
static
	int
	access(
	const std::string& fullpath,
	int mode = F_OK)
{
	struct stat info;
	std::string absolute = stl::os::path::to_absolute(fullpath);
	int ret = ::access(absolute.c_str(), mode);
	ret = ret || stat(absolute.c_str(), &info);
#ifdef __os_windows__
	return ret || !((info.st_mode & _S_IFMT) == _S_IFREG);
#else
	return ret || !S_ISREG(info.st_mode);
#endif
}
}}}

#endif /*__STL_OS_FILE_ACCESS_HPP__*/
