#ifndef __STL_OS_PATH_RMDIR_HPP__
#define __STL_OS_PATH_RMDIR_HPP__

#include <stl/os/path/traverse.hpp>
#include <stl/os/file/access.hpp>

namespace stl {
	namespace os {
		namespace path {
/** @ingroup path Function declaration
 * @brief recursively remove directory.
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
	rmdir(
	const std::string& path, 
	bool recursion = true)
{
	struct rmdirhelper{
		static int rmdir(const std::string& path)
		{
			if(!stl::os::path::access(path))
			{
				return ::rmdir(path.c_str());
			}
			if (!stl::os::file::access(path))
			{
				return ::remove(path.c_str());
			}
			return 0;
		}
	};
	std::map<std::string, std::vector<std::string>> traversor;
	traverse(path, traversor);

	if(traversor.empty() || !recursion)
	{
		return rmdirhelper::rmdir(path);
	}

	for(std::map<std::string, std::vector<std::string>>::iterator \
		it = traversor.begin();
		it != traversor.end(); it++)
	{
		for(std::vector<std::string>::iterator \
			vt = it->second.begin();\
			vt != it->second.end(); vt++)
		{
			if(rmdirhelper::rmdir(*vt))
			{
				rmdir(*vt);
				continue;
			}
		}
		if(rmdirhelper::rmdir(it->first))
		{
			rmdir(it->first);
			continue;
		}
	}
	return 0;
}

}}}

#endif //__STL_OS_PATH_RMDIR_HPP__