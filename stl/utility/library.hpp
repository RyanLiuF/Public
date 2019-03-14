#ifndef __STL_UTILITY_LIBRARY_HPP__
#define __STL_UTILITY_LIBRARY_HPP__

#include <stl/define.hpp>
#include <stl/utility/handle.hpp>
#include <vector>

namespace stl
{  
    template<typename T>
    class CModuleLoader
    {
    public:
        explicit CModuleLoader(const std::string& name, std::vector<std::string> pathList)
        : pathList_(pathList)
        , dllname_(name)
        , handle_(T())
        {
            for(auto v: pathList_) 
            {
            #ifdef  __os_windows__
                handle_ = LoadLibraryEx((v+dllname_+".dll").c_str(), NULL, 0);
            #else
                handle_ = dlopen((v+"lib"+dllname_+".so").c_str(), RTLD_NOW);
            #endif
                if(nullptr != handle_){
                    break;
                }
            }
        }
        T operator() () const
        {
            return handle_;
        }
    private:
        std::vector<std::string> pathList_;
        std::string dllname_;
        T handle_;
    };

    class Library : public CHandle
    {
        NON_COPYABLE(Library);
    public:
        explicit Library(const std::string &lib)
    #ifdef __os_windows__ 
        : Handle(CModuleLoader<HMODULE>(lib, {"", "../", "./"})(), FreeLibrary)
    #else
        : Handle(CModuleLoader<void*>(lib, {"", "../", "./"})(), dlclose)
    #endif
        {
        }
        ~Library()
        {
        }
        template< typename R, typename... Args >
        R call(const std::string& funcName, Args... args)
        {
        #ifdef __os_windows__ 
            auto func = reinterpret_cast< R (WINAPI *)(Args...) >(GetProcAddress(handle(),funcName.c_str()));
        #else
            auto func = reinterpret_cast< R (WINAPI *)(Args...) >(dlsym(handle(), funcName.c_str()));
        #endif
            return (nullptr == func) ? R(-1) : func(args...);
        }

        template< typename F >
		F address(const std::string& funcName)
        {
        #ifdef __os_windows__ 
            auto func = reinterpret_cast< F >(GetProcAddress(handle(),funcName.c_str()));
        #else
            auto func = reinterpret_cast< F >(dlsym(handle(), funcName.c_str()));
        #endif
            return func;
        }
    };
    using CLibrary = Library;
}

#endif //__STL_UTILITY_LIBRARY_HPP__