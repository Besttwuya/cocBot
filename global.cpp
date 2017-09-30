#include "stdafx.h"
#include "global.h"

CString gcurrent_path;

CScript script[MAX_THREAD_COUNT + 1];

lua_State* glua;