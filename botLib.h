#pragma once

#ifdef DLL_IMPORT
#else
#define DLL_IMPORT extern "C" __declspec(dllimport) /*µ¼Èëº¯Êý*/

#endif
#ifdef _DEBUG
#pragma comment(lib,"../Debug/botLib")
#else
#pragma comment(lib,"../Release/botLib")
#endif

DLL_IMPORT int  ImageLoc(int width, int height, void* pimg, const char* temp_file, double match_rate, int *ret_x, int*ret_y);

DLL_IMPORT int  ImageLocFromFile(const char* img1, const char* img2, double match_rate, int*ret_x, int*ret_y);