/*
 * regex.hpp
 * MIT License
 */
#ifndef LUA_REGEX_HPP
#define LUA_REGEX_HPP

#ifndef USE_BOOST
	#include<regex>
	#define NMSPC "std"
#else
	#include<boost/regex.hpp>
	using namespace boost;
	#define NMSPC "boost"
#endif
#include <lua.hpp>
extern const char regex_tname[];
extern const char match_results_tname[];

namespace lregex{
	int __new(lua_State *L);	// regex(string regex, regex_constants/uint flag)
	int create_metatable(lua_State *L);
}
namespace lmatch_results{
	int __new(lua_State *L);	// match_results()
	int create_metatable(lua_State *L);
}
namespace lregex_algorithm{
	int match(lua_State *L);
	int search(lua_State *L);
	int replace(lua_State *L);
}
namespace lregex_iterator{
	int new_iterator(lua_State *L);
}
int pushTable_syntax_option(lua_State* L);
int pushTable_match_flag(lua_State* L);
int pushTable_error_type(lua_State* L);

#endif