/*
 * library.cpp
 * 给lua一个可以调用的table
 *  做table时包含了3个table表示std::regex_constants的3种常量
 *  做函数时是std::regex的构造函数
 * MIT License
 */
#include "library.h"
#include "regex.hpp"


extern"C" __declspec(dllexport) int luaopen_regex (lua_State *L){
	regex::create_metatable(L);
	match_results::create_metatable(L);

	lua_createtable(L,0,3);
	pushTable_syntax_option(L);
	lua_setfield(L,-2,"syntax");
	pushTable_match_flag(L);
	lua_setfield(L,-2,"match");
	pushTable_error_type(L);
	lua_setfield(L,-2,"error");
	lua_createtable(L,0,1);
	lua_pushcfunction(L,regex::__new);
	lua_setfield(L,-2,"__call");
	lua_setmetatable(L,-2);
	return 1;
}