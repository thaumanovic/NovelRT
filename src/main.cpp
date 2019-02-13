#include <iostream>
#include "NovelRunner.h"
extern "C" {
    #include "../lib/lua53/lua.h"
    #include "../lib/lua53/lualib.h"
    #include "../lib/lua53/lauxlib.h"
}

lua_State* L;

static int average(lua_State *L) {
    int n = lua_gettop(L);
    double sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += lua_tonumber(L, i);
    }
    lua_pushnumber(L, sum/n);
    lua_pushnumber(L, sum);
    return 2;
}

int main() {
    // setenv("MESA_GL_VERSION_OVERRIDE", "3.2", true);
    // setenv("DISPLAY", "localhost:0.0", true);
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "average", average);
    luaL_dofile(L, "avg.lua");
    lua_close(L);
    return NovelRT::NovelRunner().runNovel(0);
}