#ifndef __STL_XFS_STRINGHELPER_ISDIGIT_HPP__
#define __STL_XFS_STRINGHELPER_ISDIGIT_HPP__

#include "is.hpp"

namespace stl {
	namespace stringhelper {
/** @ingroup stringhelper Function declaration
 * @brief determines whether a string is numberic.
 * @param[in] str source string 
 * @param[in] detectDecimal whether or not detect the decimal
 * @return 
 * 			- true  : numberic
 * 			- false : non-numberic
**/	
static bool isdigit(
	const std::string& str, bool detectDecimal = false)
{
	if(!detectDecimal || str.find('.') == str.npos) 
	{
		return is(str, ::isdigit);
	}

	std::string integer, decimal;
	split(str, '.', integer, decimal);
	return 
		is(integer, ::isdigit) && is(decimal, ::isdigit);
}

}}


#endif //__STL_XFS_STRINGHELPER_ISDIGIT_HPP__