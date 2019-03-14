#ifndef __STL_LEXICAL_AS_HPP__
#define __STL_LEXICAL_AS_HPP__

#include <sstream>
#include <iomanip>
#include <stdlib.h>

/** @defgroup as stl/lexical/as
 * @brief Implement of th type conversion.
 *
**/
namespace stl {
	namespace lexical {

/** @ingroup as Function declaration
 * @brief To convert the data type In to Out.
 * @param[in] v the source data
 * @return the converted data of the Out type
 **/
template<typename Out, typename In>
static Out as(In v)
{
	std::stringstream stream;
	Out o;
	stream << v;
	stream >> o;
	return o;
}
/** @ingroup as Function declaration
 * @brief Convert the type of int to std::string.
 * @param[in] v the source data
 * @return the converted data of the std::string type
 **/
inline std::string as(const int v){
	std::ostringstream os;
	os<<std::setiosflags(std::ios::uppercase)\
	  <<std::setw(2)\
	  <<std::setfill('0')\
	  <<std::hex<<v;
	return os.str();
}
/** @ingroup as Function declaration
 * @brief Convert the type of std::string to long.
 * @param[in] v the source data
 * @return the converted data of long type
 **/
inline long as(const std::string& v)
{
	return strtol(v.c_str(), NULL, 16);
}
/** @ingroup as Function declaration
 * @brief Convert the type of const char* to long.
 * @param[in] v the source data
 * @return the converted data of long type
 **/
inline long as(const char* v)
{
	return strtol(v, NULL, 16);
}
/** @ingroup as Function declaration
 * @brief Convert the type of char* to long.
 * @param[in] v the source data
 * @return the converted data of long type
 **/
inline long as(char* v)
{
	return strtol(v, NULL, 16);
}

}}

inline std::string operator + (std::string str, int num)
{
	return str + stl::lexical::as<std::string>(num);
}

#endif//__STL_LEXICAL_AS_HPP__
