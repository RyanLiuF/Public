#ifndef _STL_OS_PATH_TRAVERSE_HPP_
#define _STL_OS_PATH_TRAVERSE_HPP_

#include <string>
#include <string.h>
#include <vector>
#include <map>

#ifdef __os_windows__
#include<windows.h>
#else
#include <dirent.h>
#include <errno.h>
#endif

#include <stl/os/path/access.hpp>
#include <stl/os/path/truncate.hpp>
#include <stl/os/path/to_absolute.hpp>

namespace stl{
    namespace os{
        namespace path{

/** @ingroup path Function declaration
 * @brief traverse each files under the folder.
 * @param[in] path  path
 * @param[out] traversor the vector of each files and subdirectories
 * @return void
**/
static void
    traverse(
        const std::string& path, 
        std::vector<std::string>& traversor )
{
    std::string absoulte = to_absolute(path);
    if(0 == access(absoulte, F_OK))
    {
#ifdef __os_windows__
        WIN32_FIND_DATA datas = {0} ;
        std::string travese_path = absoulte+"\\*.*";
        HANDLE handle = FindFirstFile(travese_path.c_str(), &datas);
        if(INVALID_HANDLE_VALUE == handle)
			return;
        do{
            if(datas.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if(datas.cFileName[0] == '.')
                    continue;
                std::string next = absoulte + datas.cFileName;
                traverse(next, traversor);
                traversor.push_back(next);
            }
            else
            {
                traversor.push_back(absoulte+datas.cFileName);
            }
        }while(FindNextFile(handle, &datas));
        FindClose(handle);
#else
        DIR* dir_ = opendir(absoulte.c_str());
        if(NULL == dir_)
        {
            return;
        }
        struct dirent *next_; 
        while(NULL != (next_=readdir(dir_)))
        {
            if(0==strcmp(next_->d_name, ".") || 0==strcmp(next_->d_name, ".."))
            {
                continue;
            }
            std::string nextPath = absoulte + next_->d_name;
            if(!stl::os::path::access(nextPath))
            {
                 traverse(nextPath, traversor);
                 traversor.push_back(nextPath);
            }
            else
            {
                 traversor.push_back(absoulte+next_->d_name);
            }
        } 
#endif
    }
}

/** @ingroup path Function declaration
 * @brief traverse each files under the folder.
 * @param[in] path path
 * @param[out] traversor the map of subdirectories and its files
 * @return void
**/
static void
    traverse(
        const std::string& path, 
        std::map<std::string, std::vector<std::string>>& traversor )
{
    std::string absoulte = to_absolute(path);
    if(0 == access(absoulte))
    {
#ifdef __os_windows__
        WIN32_FIND_DATA datas = {0} ;
        std::string travese_path = absoulte+"\\*.*";
        HANDLE handle = FindFirstFile(travese_path.c_str(), &datas);
        if(INVALID_HANDLE_VALUE == handle)
			return;
        do{
            if(datas.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if(datas.cFileName[0] == '.')
                    continue;
                std::string next = absoulte + datas.cFileName;
                traverse(next, traversor);
                traversor[absoulte].push_back(next);//reserve the path due to include the empty directory
            }
            else
            {
                traversor[absoulte].push_back(absoulte+datas.cFileName);
            }
        }while(FindNextFile(handle, &datas));
        FindClose(handle);
#else
        DIR* dir_ = opendir(absoulte.c_str());
        if(NULL == dir_)
        {
            return;
        }
        struct dirent *next_; 
        while(NULL != (next_=readdir(dir_)))
        {
            if(0==strcmp(next_->d_name, ".") || 0==strcmp(next_->d_name, ".."))
            {
                continue;
            }
            std::string nextPath = absoulte + next_->d_name;
            if(!stl::os::path::access(nextPath))
            {
                 traverse(nextPath, traversor);
                 traversor[absoulte].push_back(nextPath);
            }
            else
            {
                 traversor[absoulte].push_back(absoulte+next_->d_name);
            }
        }        
#endif
    }
}
/** @ingroup path Function declaration
 * @brief traverse each files under the current folder.
 * @param[in] path path
 * @param[out] traversor the vector of each files and subdirectories
 * @return void
**/
static void traverse_only_current(
	const std::string& path, 
	std::vector<std::string>& traversor)
{
	std::string absoulte = path;
	if(0 == ::access(absoulte.c_str(), 0))
	{
#ifdef __os_windows__
		WIN32_FIND_DATA datas = {0} ;
		std::string travese_path = absoulte+"\\*.*";
		HANDLE handle = FindFirstFile(travese_path.c_str(), &datas);
		if(INVALID_HANDLE_VALUE == handle)
			return;
		do{
			if(datas.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(datas.cFileName[0] == '.')
					continue;
				std::string next = absoulte + datas.cFileName;
				//traverse(next, traversor);
				traversor.push_back(next);
			}
			else
			{
				traversor.push_back(absoulte+datas.cFileName);
			}
		}while(FindNextFile(handle, &datas));
		FindClose(handle);
#else
		DIR* dir_ = opendir(absoulte.c_str());
		if(NULL == dir_)
		{
			return;
		}
		struct dirent *next_; 
		while(NULL != (next_=readdir(dir_)))
		{
			if(0==strcmp(next_->d_name, ".") || 0==strcmp(next_->d_name, ".."))
			{
				continue;
			}
			std::string nextPath = absoulte + next_->d_name;
			if(!stl::os::path::access(nextPath))
			{
				traverse(nextPath, traversor);
				traversor.push_back(nextPath);
			}
			else
			{
				traversor.push_back(absoulte+next_->d_name);
			}
		} 
#endif
	}
}

}}}


#endif