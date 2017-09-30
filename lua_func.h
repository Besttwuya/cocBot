#pragma once
#ifndef _LUA_FUNC_H__
#define _LUA_FUNC_H__
#include "global.h"/*使用全局变量*/
#include <string.h>
using std::string;

/*显示日志*/
int SetLog(lua_State* L);
/*获取 x,y 颜色*/
int GetColor(lua_State* L);
/*点击屏幕*/
int Tap(lua_State* L);
/*查找颜色*/
int FindColor(lua_State* L);
/*查找指定区域内颜色*/
int FindColorEx(lua_State* L);
/*根据指定的多点查找颜色坐标*/
int FindMultiColor(lua_State* L);
/*根据指定的多点查找指定区域内颜色坐标*/
int FindMultiColorEx(lua_State* L);
/*查找图片*/
int FindPic(lua_State* L);
/*查找指定区域内的图片*/
int FindPicEx(lua_State* L);
/*设置资源路径*/
int SetPath(lua_State* L);
/*延迟*/
int Dealy(lua_State* L);
/*获取某个士兵数量并选择*/
int SelectSolider(lua_State* L);
/*获取所有可下兵的位置*/
int GetAttackPos(lua_State* L);
/**/
int GetAttackPosEx(lua_State* L);
/*获取某个法术数量并选择*/
int SelectSpell(lua_State* L);
/*选择英雄*/
int SelectHero(lua_State* L);
/*创建lua栈,并作必要初始化*/
int lua_init(int index);
/*调用一个脚本*/
int lua_call_script(CString file);
#endif
