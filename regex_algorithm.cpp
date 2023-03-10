/*
 * regex_algorithm.cpp
 * 封装了std::regex_match, std::regex_search, std::regex_replace
 * MIT License
 */
#include <lua.hpp>
#include "regex.hpp"
using namespace std;
using namespace regex_constants;
#include<iostream>
namespace lregex_algorithm{
	int match(lua_State *L){
		auto r=(regex*)luaL_checkudata(L,1,regex_tname);
		size_t slen;
		const char *s=luaL_checklstring(L,2,&slen);
		auto flag=match_default;
		if(lua_isinteger(L,3))flag=(decltype(flag))lua_tointeger(L,3);
		lmatch_results::__new(L);
		auto cm=(cmatch*)lua_touserdata(L,-1);
		lua_pushvalue(L,2);
		lua_setiuservalue(L,-2,1);	// 防止s被Lua回收
		if(!regex_match(s,s+slen,*cm,*r,flag)){
			lua_pop(L,1);
			lua_pushboolean(L,false);
		}
		return 1;
	}
	int search(lua_State *L){
		auto r=(regex*)luaL_checkudata(L,1,regex_tname);
		size_t slen;
		const char *s=luaL_checklstring(L,2,&slen);
		auto flag=match_default;
		cmatch *cm;
		lmatch_results::__new(L);
		cm=(cmatch*)lua_touserdata(L,-1);
		lua_pushvalue(L,2);
		lua_setiuservalue(L,-2,1);	// 防止s被Lua回收
		if(lua_isinteger(L,3))flag=(decltype(flag))lua_tointeger(L,3);
		if(!regex_search(s,s+slen,*cm,*r,flag)){
			lua_pop(L,1);
			lua_pushboolean(L,false);
		}
		return 1;
	}
	int replace(lua_State *L){
		auto r=(regex*)luaL_checkudata(L,1,regex_tname);
		size_t slen;
		const char *s=luaL_checklstring(L,2,&slen);
		const char *fmt=luaL_checkstring(L,3);
		auto flag=match_default;
		if(lua_isinteger(L,4))flag=(decltype(flag))lua_tointeger(L,4);
		const string &str=regex_replace(string(s,s+slen),*r,fmt,flag);
		lua_pushlstring(L,str.c_str(),str.length());
		return 1;
	}
}