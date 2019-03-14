#ifndef __STL_OS_FILE_QUERRY_HPP__
#define __STL_OS_FILE_QUERRY_HPP__

#include <string>
#include <cstdint>
#ifdef __os_windows__
#include <windows.h>

#ifndef MODULE_VERSION_INPUT
#define MODULE_VERSION_INPUT
	#pragma comment(lib, "version.lib")
#endif

#endif 

namespace stl {
	namespace os {
		namespace file {

struct version;

/** @ingroup ofiles Function declaration
 * @brief get the version of file that is an absolute path.
 * @param[in] fullpath the name of file could be a relative or absolute path.
 * @return the version of file   
**/
template<typename T>
inline std::string query(const std::string& pathname);

template<>
inline std::string query<version>(const std::string& pathname) 
{
	std::string ver;
#ifdef __os_windows__
	std::string infor = "\\StringFileInfo\\080404b0\\FileDescription";
	uint32_t dwSize = GetFileVersionInfoSize(pathname.c_str(), NULL); 
	if(0 == dwSize) { return ver; }
	std::unique_ptr<char[]> buf(new char[dwSize + 1]);
	memset(buf.get(), 0, dwSize + 1);

	uint32_t dwRtn = 
		GetFileVersionInfo(pathname.c_str(), NULL, dwSize, buf.get()); 
	if(0 == dwRtn) { return ver; }

	LPVOID lpBuffer = NULL;
	uint32_t uLen = 0;
	dwRtn = VerQueryValue(buf.get(), infor.c_str(), &lpBuffer, &uLen); 
	if(0 == dwRtn) { return ver; }
	ver = (char*)lpBuffer;
#endif
	return ver;
}
		
		
}}}

#endif //__STL_OS_FILE_QUERRY_HPP__