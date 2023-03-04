# lua-c++11regex

封装了c++11的[正则表达式库](https://zh.cppreference.com/w/cpp/regex)

## 使用方法

### 导入模块

```lua
regex=require"regex"
```

### std::regex

具体信息参阅[CppReference](https://zh.cppreference.com/w/cpp/regex)

```lua
r=regex([[(\d+)(?:\.(\d+))?]])
--创建std::regex, 如果模式串不合法会引发异常

mark=r:mark_count()	--2
--调用std::regex::mark_count, 返回正则表达式的子匹配数

match=r:match("12.25")	--12.25
--调用std::regex_match, 尝试用整个字符串匹配
--成功时返回std::cmatch, 否则返回nil

match=r:search("12.25and0")	--12.25
--调用std::regex_search, 尝试用找到匹配的子串
--成功时返回std::cmatch, 否则返回nil

-- r:replace 用法同std::regex_replace, 详见CppReference

--遍历所有符合要求的子串
for match in r:iteraotr("12.25and0") do print(match:str()) end
--[[
12.25
0
]]
```
### std::cmatch
```lua
print(match:str(nil or 0))	--12.25
--输出匹配到的内容
for i,j in pairs(match) do print(i,j) end
--for i=0,match:size()-1 do print(i,match[i]) end
--[[
0 12.25
1 12
2 25
]] --输出子匹配
```

## 编译

```
cmake -DLUA_LIB_PATH=lua库文件所在的目录 -DLUA_INCLUDE_PATH=lua头文件所在目录
make
```

## License

[MIT License](./LICENSE)

```
Copyright (c) 2023 chzn
```
