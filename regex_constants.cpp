/*
 * regex_constants.cpp
 * 将std::regex_constants的常量打包进table中
 * MIT License
 */
#include <regex>
#include <lua.hpp>

using namespace std;
using namespace regex_constants;

int pushTable_syntax_option(lua_State* L){	// +1
	static struct {const char*name;const syntax_option_type&m;}
		match_flag[]={
			{"icase",icase},	// 不考虑大小写
			{"nosubs",nosubs},	// 不存储子匹配 ()当做(?:)
			{"optimize",optimize},	// 快速匹配
			{"collate",regex_constants::collate},	// 使用本地环境
#if __cplusplus >= 201703L
			{"multiline",multiline},
#endif
			{"ECMAScript",ECMAScript},
			{"basic",basic},
			{"extended",extended},
			{"awk",awk},
			{"grep",grep},
			{"egrep",egrep}
	};
	const int size=sizeof(match_flag)/sizeof(remove_extent<decltype(match_flag)>::type);
	lua_createtable(L,0,size);
	for(int i=1;i<=size;i++){
		lua_pushinteger(L,match_flag[i-1].m);
		lua_setfield(L,-2,match_flag[i-1].name);
	}
	return 1;
}

int pushTable_match_flag(lua_State* L){	// +1
	static struct {const char*name;const match_flag_type&m;}match_flag[]={
			{"match_not_bol",match_not_bol},
			{"match_not_eol",match_not_eol},
			{"match_not_bow",match_not_bow},
			{"match_not_eow",match_not_eow},
			{"match_any",match_any},
			{"match_not_null",match_not_null},
			{"match_continuous",match_continuous},
			{"match_prev_avail",match_prev_avail},
			{"format_default",format_default},
			{"format_sed",format_sed},
			{"format_no_copy",format_no_copy},
			{"format_first_only",format_first_only}
	};
	const int size=sizeof(match_flag)/sizeof(remove_extent<decltype(match_flag)>::type);
	lua_createtable(L,0,size);
	for(int i=1;i<=size;i++){
		lua_pushinteger(L,match_flag[i-1].m);
		lua_setfield(L,-2,match_flag[i-1].name);
	}
	return 1;
}

int pushTable_error_type(lua_State* L){	// +1
	static struct {const char*name;const error_type&m;}error_type[]={
			{"collate",error_collate},
			{"ctype",error_ctype},
			{"escape",error_escape},
			{"backref",error_backref},
			{"brack",error_brack},
			{"paren",error_paren},
			{"brace",error_brace},
			{"badbrace",error_badbrace},
			{"range",error_range},
			{"space",error_space},
			{"badrepeat",error_badrepeat},
			{"complexity",error_complexity},
			{"stack",error_stack},
	};
	const int size=sizeof(error_type)/sizeof(remove_extent<decltype(error_type)>::type);
	lua_createtable(L,0,size);
	for(int i=1;i<=size;i++){
		lua_pushstring(L,error_type[i-1].name);
		lua_seti(L,-2,error_type[i-1].m);
	}
	return 1;
}