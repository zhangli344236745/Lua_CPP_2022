//
// Created by 江澎涌 on 2022/5/8.
//

#include "上值.h"

static int counter(lua_State *L) {
    int value = lua_tointeger(L, lua_upvalueindex(1));
    lua_pushinteger(L, ++value);
    lua_copy(L, -1, lua_upvalueindex(1));
    return 1;
}

int newCounter(lua_State *L) {
    lua_pushinteger(L, 0);
    lua_pushcclosure(L, &counter, 1);
    return 1;
}

static const struct luaL_Reg luaLReg[] = {
        {"newCounter", newCounter},
        {nullptr, nullptr}
};

void upValueDemo() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 设置一个 lib
    luaL_newlib(L, luaLReg);
    // Counter = lib
    lua_setglobal(L, "Counter");

    std::string fileName = "/Users/jiangpengyong/Desktop/code/Lua/Lua_CPP_2022/8、编写C函数技巧/上值/上值.lua";
    if (luaL_loadfile(L, fileName.c_str()) || lua_pcall(L, 0, 0, 0)) {
        error(L, "can't run config. file: %s", lua_tostring(L, -1));
    }

    lua_close(L);
}