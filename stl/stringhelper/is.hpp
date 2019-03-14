#ifndef __STL_XFS_STRINGHELPER_IS_HPP__
#define __STL_XFS_STRINGHELPER_IS_HPP__

#include <math.h>
#include <string>
#include <algorithm>
#include <functional>

namespace stl {
	namespace stringhelper {

static 
	bool 
	is(
	const std::string& str, 
	const std::function<int(int)>& pred)
{
	return !str.empty() && str.end() == 
		std::find_if(str.begin(), str.end(), 
			std::not1(pred));
}

}}

#endif //__STL_XFS_STRINGHELPER_IS_HPP__