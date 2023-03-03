/*
 * regex_iterator.cpp
 * 封装regex_iterator不是很有希望
 * 根据cppreference上说的用上一个match[0].second实现了类似的效果
 * MIT License
 */
#include<regex>
#include<lua.hpp>
#include "regex.hpp"
using namespace std;
using namespace regex_constants;

namespace regex_iterator{

	// str (regex, smatch) upvalue:flag
	int iterator_func(lua_State *L){
		auto r=(std::regex*)luaL_checkudata(L,1,regex_tname);
		auto cm=(std::cmatch*)luaL_checkudata(L,2,match_results_tname);
		lua_getiuservalue(L,2,1);
		size_t slen;
		const char *s=lua_tolstring(L,-1,&slen);
		::match_results::__new(L);
		auto cm2=(std::cmatch*)lua_touserdata(L,-1);
		lua_rotate(L,-2,1);
		lua_setiuservalue(L,-2,1);

		auto flag=(std::regex_constants::match_flag_type)lua_tointeger(L,lua_upvalueindex(1));


		if(regex_search(cm->ready()?cm->operator[](0).second:s,s+slen,*cm2,*r,flag))return 1;
		else {
			lua_pop(L,1);
			return 0;
		}
	}

	// regex:iterator(str,flag)
	// func,regex,smatch (regex,string,flag)
	int new_iterator(lua_State *L){
		auto r=(std::regex*)luaL_checkudata(L,1,regex_tname);
		size_t slen;
		const char *s=luaL_checklstring(L,2,&slen);
		auto flag=match_default;
		if(lua_isinteger(L,3))flag=(decltype(flag))lua_tointeger(L,3);

		lua_pushinteger(L,flag);
		lua_pushcclosure(L,iterator_func,1);
		lua_pushvalue(L,1);

		::match_results::__new(L);
		lua_pushvalue(L,2);
		lua_setiuservalue(L,-2,1);
		return 3;
	}

	//iterator_state: regex
}