#ifndef __STL_XFS_STRINGHELPER_HPP__
#define __STL_XFS_STRINGHELPER_HPP__

#include <string>
#include <stl/stringhelper/is.hpp>
#include <stl/stringhelper/to.hpp>
#include <stl/stringhelper/split.hpp>
#include <stl/stringhelper/join.hpp>
#include <stl/stringhelper/trim.hpp>
#include <stl/stringhelper/isdigit.hpp>
#include <stl/stringhelper/begin_with.hpp>
#include <stl/stringhelper/end_with.hpp>

namespace stl {
	namespace stringhelper {

inline
	int 
	compareIgnoreCase(
	const std::string& str1, 
	const std::string& str2) 
{
	return toupper(str1).compare(toupper(str2));
}
	
	
}}


#endif //__STL_XFS_STRINGHELPER_HPP__
