#pragma once
#ifndef _LUA_FUNC_H__
#define _LUA_FUNC_H__
#include "global.h"/*ʹ��ȫ�ֱ���*/
#include <string.h>
using std::string;

/*��ʾ��־*/
int SetLog(lua_State* L);
/*��ȡ x,y ��ɫ*/
int GetColor(lua_State* L);
/*�����Ļ*/
int Tap(lua_State* L);
/*������ɫ*/
int FindColor(lua_State* L);
/*����ָ����������ɫ*/
int FindColorEx(lua_State* L);
/*����ָ���Ķ�������ɫ����*/
int FindMultiColor(lua_State* L);
/*����ָ���Ķ�����ָ����������ɫ����*/
int FindMultiColorEx(lua_State* L);
/*����ͼƬ*/
int FindPic(lua_State* L);
/*����ָ�������ڵ�ͼƬ*/
int FindPicEx(lua_State* L);
/*������Դ·��*/
int SetPath(lua_State* L);
/*�ӳ�*/
int Dealy(lua_State* L);
/*��ȡĳ��ʿ��������ѡ��*/
int SelectSolider(lua_State* L);
/*��ȡ���п��±���λ��*/
int GetAttackPos(lua_State* L);
/**/
int GetAttackPosEx(lua_State* L);
/*��ȡĳ������������ѡ��*/
int SelectSpell(lua_State* L);
/*ѡ��Ӣ��*/
int SelectHero(lua_State* L);
/*����luaջ,������Ҫ��ʼ��*/
int lua_init(int index);
/*����һ���ű�*/
int lua_call_script(CString file);
#endif
