#ifndef __STL_DEFINE_HPP__
#define __STL_DEFINE_HPP__

#define NON_COPYABLE(T) \
  T(const T &); \
  T &operator=(const T &)

#define NON_MOVEABLE(T) \
  T(T &&); \
  T &operator=(T &&)

#if ((defined _WINDOWS) || (defined WIN32) || (defined WIN64))
#define  __os_windows__
#ifndef WINAPI
#define WINAPI _stdcall
#endif

#define F_OK	0x00
#define W_OK	0x02
#define R_OK	0x04
#define X_OK

#define EXPORT_API_ATTR_DEFAULT
#define EXPORT_API_ATTR_HIDDEN

/****header files ************/
#include <Windows.h>
#include <io.h>
#include <direct.h>
#include <sys/stat.h>
#endif

#if defined(__linux__) || defined(__linux)
#define  __os_linux__
#define WINAPI
#define EXPORT_API_ATTR_DEFAULT	__attribute__ ((visibility("default")))
#define EXPORT_API_ATTR_HIDDEN	__attribute__ ((visibility("hidden")))

#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#endif

#if defined(__ANDROID__) || defined(_ANDROID)
#define  __os_android__
#define WINAPI
#define EXPORT_API_ATTR_DEFAULT	__attribute__ ((visibility("default")))
#define EXPORT_API_ATTR_HIDDEN	__attribute__ ((visibility("hidden")))

#ifndef S_IREAD
#define S_IREAD		S_IRUSR
#endif

#ifndef S_IWRITE
#define S_IWRITE	S_IWUSR
#endif

#endif

#if defined(__APPLE__)
#define  __os_apple__
#endif

#endif//__STL_DEFINE_HPP__