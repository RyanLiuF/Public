#ifndef  __STL_OS_FILE_IO_HPP__
#define  __STL_OS_FILE_IO_HPP__

#ifdef __os_windows__
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#else
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#endif

namespace stl{
    namespace os{
        namespace io{
class IO
{
public:
    IO(const std::string& fullname, 
                int open_flag,
                int permission_mode)
    : fd_(0)
    , opened_(false)
    {
    #ifdef __os_windows__
        fd_ = _open(fullname.c_str(), open_flag, permission_mode);
    #else
        fd_ = open(fullname.c_str(), open_flag, permission_mode);
    #endif
        opened_ = (-1 != fd_);
    }
    ~IO()
    {
        Close();
    }

    bool Opened() const
    {
        return opened_;
    }

    long Length()
    {
        if(!opened_) return -1;
        long len = Seek(0, SEEK_END) - Seek(0, SEEK_SET);
        Seek(0, SEEK_SET);
        return len;
    }

    long Seek(long offset, int origin)
    {
        if(!opened_) return -1;
    #ifdef __os_windows__
        return _lseek(fd_, offset, origin);
    #else
        return lseek(fd_, offset, origin);
    #endif  
    }

    int Read(void* buffer, unsigned int len)
    {
        if(!opened_) return -1;
    #ifdef __os_windows__
        return _read(fd_, buffer, len);
    #else
        return read(fd_, buffer, (size_t)len);
    #endif
    }

    int Write(void* buffer, unsigned int len)
    {
        if(!opened_) return -1;
    #ifdef __os_windows__
        return _write(fd_, buffer, len);
    #else
        return write(fd_, buffer, (size_t)len);
    #endif
    }

    void Flush()
    {
        if(!opened_) return;
    #ifdef __os_windows__
        _flushall();
        //_close(fd_);
    #elif defined(__os_android__)
        fsync(fd_);
    #else
        syncfs(fd_);//fsync
        //close(fd_);
    #endif
    }

    void Close()
    {
       if(!opened_) return;
    #ifdef __os_windows__
        _flushall();
        _close(fd_);
    #elif defined(__os_android__)
        fsync(fd_);
        close(fd_);
    #else
        syncfs(fd_);
        close(fd_);
    #endif
		opened_ = false;
    }

private:
    int     fd_;
    bool    opened_;
};

inline int 
    open(const std::string& file, 
                int open_flag,
                int permission_mode)
{
#ifdef __os_windows__
    return ::_open(file.c_str(), open_flag, permission_mode);
#else
    return ::open(file.c_str(), open_flag, permission_mode);
#endif
}

inline int 
    read(int fd, void* buffer, unsigned int len)
{
#ifdef __os_windows__
    return ::_read(fd, buffer, len);
 #else
    return ::read(fd, buffer, (size_t)len);
#endif
}

inline int
    write(int fd, void* buffer, unsigned int len)
{
#ifdef __os_windows__
    return ::_write(fd, buffer, len);
#else
    return ::write(fd, buffer, (size_t)len);
#endif    
}

inline int
    lseek(int fd, long offset, int origin)
{
#ifdef __os_windows__
    return ::_lseek(fd, offset, origin);
#else
    return ::lseek(fd, offset, origin);
#endif      
}

inline int 
    close(int fd)
{
#ifdef __os_windows__
       return ::_close(fd);
#else
       return ::close(fd);
#endif
}

inline int 
    flush(int fd)
{
#ifdef __os_windows__
    return ::_flushall();
#elif defined(__os_android__)
    return fsync(fd);
#else
    return syncfs(fd);    
#endif
}

static long 
    GetFileSize(const std::string& file)
{
#ifdef __os_windows__
    struct _stat info;
    _stat(file.c_str(), &info);
#else
     struct stat info;
     stat(file.c_str(), &info);
#endif
    return info.st_size;
}

typedef IO CIO;

}}}

#endif //__STL_OS_FILE_IO_HPP__