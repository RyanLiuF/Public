#ifndef __STL_SLEEP_HPP
#define __STL_SLEEP_HPP

#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>

namespace stl
{
    namespace time
    {
        inline void
            sleep(unsigned long millseconds)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(millseconds));
        }

        template< typename T=unsigned long >
        inline T
        tick()
        {
            auto now = std::chrono::time_point_cast<std::chrono::duration<T, std::milli>>
                        (std::chrono::steady_clock::now());
            return now.time_since_epoch().count();
        }

#pragma pack(push,1)
        struct tmExtend
        {
			int tm_sec;   // seconds after the minute - [0, 60] including leap second
			int tm_min;   // minutes after the hour - [0, 59]
			int tm_hour;  // hours since midnight - [0, 23]
			int tm_mday;  // day of the month - [1, 31]
			int tm_mon;   // months since January - [0, 11]
			int tm_year;  // years since 1900
			int tm_wday;  // days since Sunday - [0, 6]
			int tm_yday;  // days since January 1 - [0, 365]
			int tm_isdst; // daylight savings time flag
            int tm_mill;
        };
#pragma pack(pop)

        inline tmExtend 
            GetLocalTime(void)
        {
            auto clock = std::chrono::system_clock::now();
            auto epoch = clock.time_since_epoch();
            auto time = std::chrono::system_clock::to_time_t(clock);
            auto localtime = std::localtime(&time);
            tmExtend tmp;
            // memcpy(&tmp, localtime, sizeof(std::tm));
            tmp.tm_sec = localtime->tm_sec;
            tmp.tm_min = localtime->tm_min;
            tmp.tm_hour = localtime->tm_hour;
            tmp.tm_mday = localtime->tm_mday;
            tmp.tm_mon = localtime->tm_mon;
            tmp.tm_wday = localtime->tm_wday;
            tmp.tm_yday = localtime->tm_yday;
            tmp.tm_isdst = localtime->tm_isdst;
            tmp.tm_year = localtime->tm_year;
            tmp.tm_year += 1900;
            tmp.tm_mon += 1;
            tmp.tm_mill = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count()%1000;
            return tmp;
        }

        inline std::string 
            GetLocalTime(const std::string& fmt)
        {
            std::unique_ptr<char[]> buffer(new char[1024]());
            tmExtend tm = GetLocalTime();
            sprintf(&buffer[0], fmt.c_str(), \
                    tm.tm_year, tm.tm_mon, tm.tm_mday, \
                    tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mill);
            return &buffer[0];
        }

		inline std::string 
			GetLocalTime(const std::string& fmt, const tmExtend& tm)
		{
			std::unique_ptr<char[]> buffer(new char[1024]());
			sprintf(&buffer[0], fmt.c_str(), \
				tm.tm_year, tm.tm_mon, tm.tm_mday, \
				tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mill);
			return &buffer[0];
		}
        
    } // time
}

#endif