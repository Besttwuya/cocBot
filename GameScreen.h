#pragma once
#include "CvvImage.h"
class CGameScreen
{
	
public:
	CGameScreen();
	~CGameScreen();
public://����
	Cdmsoft dm;
	CbotFunction bot;
	IplImage* TheImage;
	CStatic* pStatic;
	CSliderCtrl* pGameFps;
	CButton* pIsShowGameScreen;
public://����
	int sreennCode;
	bool IsThreadRun;
public://����
	bool CreateDm();
	void Dealy(unsigned long mSeconds);
	void ResizeImage(IplImage* img);
	void ShowImage(IplImage* img, CWnd* pWnd);
	void gameScreenShow(const char* filename);
};

