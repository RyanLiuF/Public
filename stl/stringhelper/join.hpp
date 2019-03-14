#ifndef __STL_STRINGHELPER_JOIN_HPP__
#define __STL_STRINGHELPER_JOIN_HPP__

#include <stl/lexical/as.hpp>

#include <map>
#include <string>

namespace stl {
	namespace stringhelper {

	template<typename Iter>
	static 
		std::string 
		join(
		Iter begin, 
		Iter end, 
		const std::string& junctor)
	{
		std::string result;
		for (; begin != end; ++begin)
		{
			if (!result.empty()) result += junctor;
			result += ::stl::lexical::as<std::string>(*begin);
		}
		return result;
	}

	template<typename Iter>
	inline 
		std::string 
		join(
		Iter begin, 
		Iter end, 
		char junctor)
	{
		return join(begin, end, std::string(1, junctor));
	}

	template<typename Container>
	inline std::string join(
		const Container& c, char junctor)
	{
		return join(c.begin(), c.end(), junctor);
	}

	template<typename Container>
	inline std::string join(
		const Container& c, 
		const std::string& junctor)
	{
		return join(c.begin(), c.end(), junctor);
	}

	template<typename K, typename V>
	inline std::string join(
		const typename std::pair<K, V>& p, 
		const std::string& junctor)
	{
		return 
			::stl::lexical::as<std::string>(p.first) +
			junctor +
			::stl::lexical::as<std::string>(p.second);
	}

	template<typename K, typename V>
	inline std::string join(
		const typename std::pair<K, V>& p, char junctor)
	{
		return join(p, std::string(1, junctor));
	}

	template<typename K, typename V>
	inline 
		std::string 
		join(
		const typename std::map<K, V>& m, 
		const std::string& mapJunctor, 
		const std::string& pairJunctor)
	{
		std::string result;
		typename std::map<K, V>::const_iterator itr = m.begin();
		for (; itr != m.end(); ++itr)
		{
			if (!result.empty()) result += mapJunctor;
			result += join(*itr, pairJunctor);
		}
		return result;
	}

	template<typename K, typename V>
	static 
		std::string 
		join(
		const typename std::map<K, V>& m, 
		char mapJunctor, 
		char pairJunctor)
	{
		std::string mj(1, mapJunctor), pj(1, pairJunctor);
		return join(m, mj, pj);
	}

}}


#endif //__STL_STRINGHELPER_JOIN_HPP__