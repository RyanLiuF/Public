#ifndef __STL_XFS_STRINGHELPER_BEGIN_WITH_HPP__
#define __STL_XFS_STRINGHELPER_BEGIN_WITH_HPP__

#include <string>

/** @defgroup stringhelper stl/stringhelper
 * @brief Implement of stringhelper operation.
 *
**/

namespace stl {
	namespace stringhelper {

/** @ingroup stringhelper Function declaration
 * @brief determines whether a string begins with the others string.
 * @param[in] src source string 
 * @param[in] head head
 * @return 
 * 			- true  : the source string begins with head
 * 			- false : the source string does not begin with head
**/
inline 
	bool 
	begin_with(
	const std::string& src, 
	const std::string& head) 
{
	std::string::size_type pos = src.find(head);
	return !src.empty() && (pos == 0);
}

/** @ingroup stringhelper Function declaration
 * @brief determines whether a string begins with a character.
 * @param[in] src source string 
 * @param[in] head head
 * @return 
 * 			- true  : the source string begins with head
 * 			- false : the source string does not begin with head
**/
inline
	bool 
	begin_with(
	const std::string& src, 
	char head)
{
	return begin_with(src, std::string(1, head));
}

}}

#endif //__STL_XFS_STRINGHELPER_BEGIN_WITH_HPP__