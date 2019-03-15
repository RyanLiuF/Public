#ifndef __STL_CONCURRENCE_SEMAPHORE_HPP__
#define __STL_CONCURRENCE_SEMAPHORE_HPP__

#include <mutex>
#include <condition_variable>

namespace stl
{
    namespace concurrence
    {
        class CSemaphore
        {
        public:
            CSemaphore(int val = 1)
            : cnt(val)
            {}
            void wait()
            {
                std::unique_lock<std::mutex> ul(locker);
                if(--cnt < 0)
                    cv.wait(ul);
            }
            bool wait_for(std::chrono::milliseconds mill)
            {
                std::unique_lock<std::mutex> ul(locker);
                return (--cnt < 0) ? (cv.wait_for(ul, mill)==std::cv_status::no_timeout) : false;
            }
            void post()
            {
                std::unique_lock<std::mutex> ul(locker);
                if(++cnt <= 0)
                {
                    cv.notify_one();
                }
            }
			void reset()
			{
				std::unique_lock<std::mutex> ul(locker);
				cnt = 1;
			}
        private:
            int cnt;
            std::mutex locker;
            std::condition_variable cv;
        };
    }
}

#endif//__STL_CONCURRENCE_SEMAPHORE_HPP__