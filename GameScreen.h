#pragma once
#include "CvvImage.h"
class CGameScreen
{
	
public:
	CGameScreen();
	~CGameScreen();
public://对象
	Cdmsoft dm;
	CbotFunction bot;
	IplImage* TheImage;
	CStatic* pStatic;
	CSliderCtrl* pGameFps;
	CButton* pIsShowGameScreen;
public://变量
	int sreennCode;
	bool IsThreadRun;
public://函数
	bool CreateDm();
	void Dealy(unsigned long mSeconds);
	void ResizeImage(IplImage* img);
	void ShowImage(IplImage* img, CWnd* pWnd);
	void gameScreenShow(const char* filename);
};

