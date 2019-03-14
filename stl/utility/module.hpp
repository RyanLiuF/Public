#ifndef __STL_UTILITY_MODULEEX_HPP__
#define __STL_UTILITY_MODULEEX_HPP__

#include <stl/utility/library.hpp>
#include <memory>

namespace stl
{
    struct ModuleLifeCycle
    {
    public: 
        explicit ModuleLifeCycle(
            const std::string & constructor, const std::string & destructor) :
            constructor_(constructor), 
            destructor_(destructor)
        {
        }
        
        const std::string & constructor() const
        {
            return this->constructor_;
        }

        const std::string & destructor() const
        {
            return this->destructor_;
        }

    private:
        std::string constructor_;
        std::string destructor_;
    };
    using CModuleLifeCycle = ModuleLifeCycle;

    template< typename T >
    class CModule
    {
    public:
        CModule()
        : obj_ptr_(nullptr)
        {
        }
        virtual ~CModule()
        {
            this->reset();
        }
        void reset()
        {
            obj_ptr_.reset();
            loader_.reset();
        }
        T* get()
        {
            return obj_ptr_.get();
        }
        T* operator->()
        {
            return obj_ptr_.get(); 
        }
        explicit operator bool ()
        {
			return (obj_ptr_.get() != nullptr);
        }
	protected:
        std::shared_ptr<stl::CLibrary> loader_;
        std::shared_ptr<T> obj_ptr_;
    };

    template < typename T, typename... Args >
    class CModuleWithArgs: public CModule<T>
    {
    public:
      CModuleWithArgs( const std::string& name, 
                       const CModuleLifeCycle& lifecycle, 
                       Args... args )
      {
        this->loader_ = std::shared_ptr<stl::CLibrary>(new stl::CLibrary(name));
        auto __init_object_func__ = [&]()->void{
            typedef T*(WINAPI *constructor)(Args...);
            typedef void(WINAPI *destructor)(void*);
            constructor create = this->loader_->template address<constructor>(lifecycle.constructor());
            destructor destory = this->loader_->template address<destructor>(lifecycle.destructor());
            if(create && destory)
                this->obj_ptr_ = std::shared_ptr<T>(create(args...), destory);
        };
        if(*this->loader_)  __init_object_func__();
      }
    };

    template < typename T, typename... Args >
    CModule<T> make_module( const std::string& name, 
                            const ModuleLifeCycle& lifecycle, 
                            Args... args )
    {
        return CModuleWithArgs<T, Args...>(name, lifecycle, args...);
    }
}

#endif //__STL_UTILITY_MODULE_HPP__