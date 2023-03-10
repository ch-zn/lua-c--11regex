/*
 * regex.cpp
 * std::regex的封装
 * MIT License
 */
#include <lua.hpp>
#include "regex.hpp"
using namespace std;
using namespace regex_constants;

extern const char regex_tname[]=NMSPC"::regex";

namespace lregex{
	int __new(lua_State *L){	// regex(string regex, regex_constants/uint flag)
		// call from library.__call, arg 1 is library, true args start from 2
		size_t len=0;
		const char* s=luaL_checklstring(L,2,&len);

		auto flag=regex_constants::ECMAScript;
		if(lua_isinteger(L,3))flag=(decltype(flag))(lua_tointeger(L,3));

		void* ptr=lua_newuserdatauv(L,sizeof(regex),1);
		try{
			new(ptr)regex(s,flag);
		}catch (const regex_error& e){
			return luaL_error(L,e.what());
		}

		lua_pushvalue(L,2);
		lua_setiuservalue(L,-2,1);

		luaL_setmetatable(L,regex_tname);
		return 1;
	}
	int __gc(lua_State *L){
		((regex*)lua_touserdata(L,1))->regex::~regex();
		return 0;
	}
	int mark_count(lua_State *L){	// int()
		auto r=(regex*)luaL_checkudata(L,1,regex_tname);
		lua_pushinteger(L,r->mark_count());
		return 1;
	}
	int flags(lua_State *L){	// regex_constants/uint()
		auto r=(regex*)luaL_checkudata(L,1,regex_tname);
		lua_pushinteger(L,r->flags());
		return 1;
	}
	static const luaL_Reg __index[]={
			{"mark_count",mark_count},
			{"flags",flags},
			{"match",lregex_algorithm::match},
			{"search",lregex_algorithm::search},
			{"replace",lregex_algorithm::replace},
			{"iterator",lregex_iterator::new_iterator},
			{nullptr,nullptr}
	};
	int pushTable__index(lua_State *L){
		luaL_newlib(L,__index);
		return 1;
	}
	int create_metatable(lua_State *L){
		luaL_newmetatable(L,regex_tname);

		pushTable__index(L);
		lua_setfield(L,-2,"__index");

		lua_pushcfunction(L,__gc);
		lua_setfield(L,-2,"__gc");

		lua_pop(L,1);
		return 0;
	}
}