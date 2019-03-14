#ifndef __STL_OS_PROGRESS_FULLNAME_HPP__
#define __STL_OS_PROGRESS_FULLNAME_HPP__

#include <string>

#ifdef __os_windows__
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

/** @defgroup progress stl/os/progress
 * @brief Implement of progress operation.
 *
**/
namespace stl {
	namespace os {
		namespace progress {

/** @ingroup progress Function declaration
 * @brief get the execution path and the name of program.
 * @return the path
**/
static std::string fullname()
{
	std::string path;
#ifdef __os_windows__
	char cpath[MAX_PATH+1] = {0,};
	GetModuleFileName(NULL, cpath, MAX_PATH);
	path = cpath;
#else
	char clink[MAX_PATH] = {0,};
	char cpath[MAX_PATH] = {0,};
	sprintf(clink, "/proc/%d/exe", getpid());
	readlink(clink, cpath, sizeof(cpath));
	path = cpath;
#endif
	return path;
}


}}}

#endif //__STL_OS_PROGRESS_FULLNAME_HPP__
