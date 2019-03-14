#ifndef __STL_XFS_SPLIT_HPP__
#define __STL_XFS_SPLIT_HPP__

#include <string>
#include <vector>

namespace stl {
	namespace stringhelper {

inline
	bool
	split(
	const std::string& s,
	const std::string& sep, 
	std::string& first,
	std::string& second)
{
	std::string::size_type sep_pos = s.find(sep);
	first = s.substr(0, sep_pos);
	if (sep_pos != std::string::npos)
		second = s.substr(sep_pos + sep.length());
	return true;
}

inline
	std::vector<std::string>
	split(
	const std::string& s,
	const std::string& sep) {

	std::vector<std::string> vectors;
	if (s.empty()) return vectors;

	std::string::size_type beg_pos = 0;
	std::string::size_type end_pos = s.find(sep);
	while (end_pos != std::string::npos)
	{
		end_pos += beg_pos;
		vectors.push_back(s.substr(beg_pos, end_pos - beg_pos));
		beg_pos = end_pos + sep.length();
		std::string::size_type pos = s.substr(beg_pos).find(sep);
		end_pos = s.substr(beg_pos).find(sep);
	}

	if (beg_pos < s.length())
		vectors.push_back(s.substr(beg_pos));
	return vectors;
}

inline
	bool
	split(
	const std::string& s,
	char sep, std::string& first,
	std::string& second)
{
	return split(s, std::string(1, sep), first, second);
}

inline
std::vector<std::string>
	split(
	const std::string& s,
	char sep)
{
	return split(s, std::string(1, sep));
}

}}


#endif //__STL_XFS_SPLIT_HPP__