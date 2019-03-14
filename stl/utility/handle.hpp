#ifndef __STL_UTILITY__HANDLE_HPP__
#define __STL_UTILITY__HANDLE_HPP__

#include <stl/define.hpp>

namespace stl
{
  template< typename T, typename R >
  class Handle
  {
    NON_COPYABLE(Handle);

    T _h;
    R ((WINAPI *_closeF))(T);

  protected:
    void setHandle(T h, R ((WINAPI *closeF))(T))
    {
      _h = h;
      _closeF = closeF;
      //if ((_h == NULL) || (_h == INVALID_HANDLE_VALUE))
        //throw Exception();
    }

    explicit Handle(T h, R ((WINAPI *closeF))(T))
    {
      setHandle(h,closeF);
    }

    explicit Handle() :
      _h(NULL),
      _closeF(NULL)
    {
    }

  public:
    Handle(Handle &&o) :
      _h(o._h),
      _closeF(o._closeF)
    {
      o._h = NULL;
    }

    ~Handle()
    {
      if (_h != NULL && _closeF != NULL)
      {
        _closeF(_h);
        _h = NULL;
      }
    }

    T handle() const
    {
      return _h;
    }

    Handle &operator=(Handle &&o)
    {
      _h = o._h;
      _closeF = o._closeF;
      o._h = NULL;
      return *this;
    }

    explicit operator bool() const
    {
      return (_h != NULL) && (_h != (T)(-1));
    }
  };

#ifdef __os_windows__  
using CHandle = Handle<HMODULE, BOOL>;
#else
using CHandle = Handle<void*, int>;
#endif
}

#endif //__STL_UTILITY__HANDLE_HPP__