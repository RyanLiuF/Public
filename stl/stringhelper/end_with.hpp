#ifndef __STL_XFS_STRINGHELPER_END_WITH_HPP__
#define __STL_XFS_STRINGHELPER_END_WITH_HPP__

namespace stl {
	namespace stringhelper {
/** @ingroup stringhelper Function declaration
 * @brief determines whether a string ends up with the others string.
 * @param[in] src source string 
 * @param[in] tail tail
 * @return 
 * 			- true  : the source string ends up with tail
 * 			- false : the source string does not end with tail
**/		
inline 
	bool 
	end_with(
	const std::string& src,
	const std::string& tail)
{
	std::string::size_type pos = src.find(tail);
	
	return !src.empty() && ((pos + tail.length()) == src.length());
}
/** @ingroup stringhelper Function declaration
 * @brief determines whether a string ends up with a character.
 * @param[in] src source string 
 * @param[in] tail tail
 * @return 
 * 			- true  : the source string ends up with tail
 * 			- false : the source string does not end with tail
**/	
inline 
	bool 
	end_with(
	const std::string& src, 
	char tail)
{
	return end_with(src, std::string(1, tail));
}

}}

#endif //__STL_XFS_STRINGHELPER_END_WITH_HPP__