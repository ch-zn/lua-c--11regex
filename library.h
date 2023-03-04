/*
 * library.h
 * MIT License
 */

/*
 * push:
 * {syntax={std::regex_constants::syntax_option_type},
 *  match ={std::regex_constants::match_flag_type}
 *  error ={std::regex_constants::error_type}
 * } -metatable-> {
 *    __call=func(self,string,flags=default){return std::regex(string,flags)}
 *   }
 *
 * registered metatable:
 *   std::regex{
 *     __index={
 *       mark_count,
 *       flags,
 *       match=func(self,string,flag=default){cmatch cm;return std::regex_match(string,cm,self,flag),cm},
 *       search=func(self,string,flag=default){cmatch cm;return std::regex_search(string,cm,self,flag),cm},
 *       replace=func(self,string,fmt,flag=default){return std::regex_replace(string,self,fmt,flag)},
 *       iterator=func(self,string){return std::regex_iterator(string,self)}, // used for generic for loop
 *       	// for(cmatch in regex:iterator(string))
 *     },
 *     __gc=func(self){~self();}
 *   }
 *   std::cmatch{
 *     __index={
 *       empty,
 *       size,
 *       length,
 *       position,
 *       prefix,
 *       suffix,
 *       str,
 *       format
 *     },
 *     __gc=func(self){~self();},
 *     __pairs
 *   }
 */


#ifndef REGEX_LIBRARY_H
#define REGEX_LIBRARY_H

#include <lua.hpp>

extern"C" __declspec(dllexport) int luaopen_regex (lua_State *L);

#endif //REGEX_LIBRARY_H
