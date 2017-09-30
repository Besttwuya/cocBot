#pragma once
#ifndef _GLOBAL_H__
#define _GLOBAL_H__
#include "Const.h"
#include "Script.h"

#ifdef _DEBUG
#pragma comment(lib,"Debug/lua5.3.lib")
#else
#pragma comment(lib,"Release/lua5.3.lib")
#endif // _DEBUG

extern "C"
{
#include <lua.h>			/*lua*/
#include <lualib.h>			/*lua*/
#include <lauxlib.h>		/*lua*/
}

/*ȫ�ֱ���*/
/*��������Ŀ¼*/
extern CString gcurrent_path;
/*�ű�*/
extern  CScript script[MAX_THREAD_COUNT + 1];
/*lua*/
extern lua_State* glua;


#endif
