/*
 * regex_algorithm.cpp
 * 封装了std::regex_match, std::regex_search, std::regex_replace
 * MIT License
 */
#include <regex>
#include <lua.hpp>
#include "regex.hpp"
using namespace std;
using namespace regex_constants;

namespace regex_algorithm{
	int match(lua_State *L){
		auto r=(std::regex*)luaL_checkudata(L,1,regex_tname);
		size_t slen;
		const char *s=luaL_checklstring(L,2,&slen);
		auto flag=match_default;
		if(lua_isinteger(L,3))flag=(decltype(flag))lua_tointeger(L,3);
		::match_results::__new(L);
		auto cm=(std::cmatch*)lua_touserdata(L,-1);
		lua_pushvalue(L,2);
		lua_setiuservalue(L,-2,1);	// 防止s被Lua回收
		lua_pushboolean(L,std::regex_match(s,s+slen,*cm,*r,flag));
		lua_rotate(L,-2,1);
		return 2;
	}
	int search(lua_State *L){
		auto r=(std::regex*)luaL_checkudata(L,1,regex_tname);
		size_t slen;
		const char *s=luaL_checklstring(L,2,&slen);
		auto flag=match_default;
		std::cmatch *cm;
		::match_results::__new(L);
		cm=(std::cmatch*)lua_touserdata(L,-1);
		lua_pushvalue(L,2);
		lua_setiuservalue(L,-2,1);	// 防止s被Lua回收
		if(lua_isinteger(L,3))flag=(decltype(flag))lua_tointeger(L,3);
		lua_pushboolean(L,std::regex_search(s,s+slen,*cm,*r,flag));
		lua_rotate(L,-2,1);
		return 2;
	}
	int replace(lua_State *L){
		auto r=(std::regex*)luaL_checkudata(L,1,regex_tname);
		const char *s=luaL_checkstring(L,2);
		const char *fmt=luaL_checkstring(L,3);
		auto flag=match_default;
		if(lua_isinteger(L,4))flag=(decltype(flag))lua_tointeger(L,4);
		const string &str=regex_replace(s,*r,fmt,flag);
		lua_pushlstring(L,str.c_str(),str.length());
		return 1;
	}
}