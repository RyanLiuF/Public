#ifndef __STL_OS_PATH_CURRENT_HPP__
#define __STL_OS_PATH_CURRENT_HPP__

#ifdef __os_windows__
#include <direct.h>
#include <io.h>
#else 
#include <sys/stat.h>
#include <dlfcn.h>
#endif

#include <string>

namespace stl {
	namespace os {
		namespace path {

/** @ingroup path Function declaration
 * @brief get the program path.
 * @return the current path
**/	
inline 
	std::string 
	current() 
{
	char buffer[1024] = {0,};
	return getcwd(buffer, sizeof(buffer));
}

/** @ingroup path Function declaration
 * @brief get the dll path.
 * @return the dll path
**/
inline 
	std::string 
	dll()
{
#ifdef __os_windows__
	MEMORY_BASIC_INFORMATION info;
	HMODULE hDll = ::VirtualQuery(dll, &info, sizeof(info))!=0?\
				  (HMODULE)info.AllocationBase : NULL;
	char buffer[1024] = {0, };
	GetModuleFileName(hDll, buffer, sizeof(buffer));
	char sep = '\\';
	std::string name(buffer);//absolute path
#elif defined(__os_android__)
	char sep = '/';
	std::string name = current();
#else
	char sep = '/';
	Dl_info info;
	int ret = dladdr((void*)dll, &info);
	std::string name(info.dli_fname);//maybe a relative path
#endif
	if (name.empty()) return name;
	std::string::reverse_iterator found = 
		std::find_if(name.rbegin(), name.rend(), 
		std::bind(std::equal_to<std::string::value_type>(), 
		std::placeholders::_1, 
		sep));
	if (found == name.crend()) return name;
	name.erase((++found).base(), name.end());
	return name;
}

}}}
#endif //__STL_OS_PATH_CURRENT_HPP__