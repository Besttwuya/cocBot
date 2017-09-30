#include "stdafx.h"
#include "GameScreen.h"


CGameScreen::CGameScreen()
{
	sreennCode = 0;
	IsThreadRun = false;
	CvSize ImageSize;
	/*
	*/
	
	ImageSize.height = SCREENSHOWHEIGHT;
	ImageSize.width = SCREENSHOWWIDTH;
	TheImage= cvCreateImage(ImageSize, IPL_DEPTH_8U, 3);
}


CGameScreen::~CGameScreen()
{
	cvReleaseImage(&TheImage);
	dm = NULL;
}


bool CGameScreen::CreateDm()
{
	int ret = 0;

	::CoInitialize(NULL);
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	if (dm.CreateDispatch(clsid) == TRUE)
	{
		return true;
	}
	else
	{
		return false;
	}


}


void CGameScreen::Dealy(unsigned long mSeconds)
{
	DWORD j = GetTickCount();
	for (;;)
	{

		if (GetTickCount() >= j + mSeconds)
		{
			break;
		}
		if (sreennCode <= 0)
		{
			break;
		}
		Sleep(1);
	}
}


void CGameScreen::ResizeImage(IplImage* img)
{
	// 读取图片的宽和高
	int w = img->width;
	int h = img->height;

	// 找出宽和高中的较大值者
	//int max = (w > h) ? w : h;

	// 计算将图片缩放到TheImage区域所需的比例因子
	float scaleX = (float)((float)w / SCREENSHOWWIDTH);
	float scaleY = (float)((float)h / SCREENSHOWHEIGHT);
	// 缩放后图片的宽和高
	int nw = (int)(w / scaleX);
	int nh = (int)(h / scaleY);

	// 为了将缩放后的图片存入 TheImage 的正中部位，需计算图片在 TheImage 左上角的期望坐标值
	int tlx = (nw > nh) ? 0 : (int)(SCREENSHOWWIDTH - nw) / 2;
	int tly = (nw > nh) ? (int)(SCREENSHOWHEIGHT - nh) / 2 : 0;

	// 设置 TheImage 的 ROI 区域，用来存入图片 img
	cvSetImageROI(TheImage, cvRect(tlx, tly, nw, nh));

	// 对图片 img 进行缩放，并存入到 TheImage 中
	cvResize(img, TheImage);

	// 重置 TheImage 的 ROI 准备读入下一幅图片
	cvResetImageROI(TheImage);
}


void CGameScreen::ShowImage(IplImage* img, CWnd* pWnd)
{
	CDC* pDC = pWnd->GetDC();        // 获得显示控件的 DC
	HDC hDC = pDC->GetSafeHdc();                // 获取 HDC(设备句柄) 来进行绘图操作
	//HWND hwnd = pWnd->m_hWnd;

	CRect rect;
	pWnd->GetClientRect(&rect);
	int rw = rect.right - rect.left;            // 求出图片控件的宽和高
	int rh = rect.bottom - rect.top;
	int iw = img->width;                        // 读取图片的宽和高
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;                    // 使图片的显示位置正好在控件的正中
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	CvvImage cimg;
	cimg.CopyOf(img);                            // 复制图片
	cimg.DrawToHDC(hDC, &rect);                // 将图片绘制到显示控件的指定区域内

	//ReleaseDC(hwnd,hDC);
}


void CGameScreen::gameScreenShow(const char* filename)
{
	
	IplImage* ipl = cvLoadImage(filename, 1);    // 读取图片、缓存到一个局部变量 ipl 中
	if (!ipl)                                    // 判断是否成功载入图片
		return;
	if (TheImage)                                // 对上一幅显示的图片数据清零
		cvZero(TheImage);

	ResizeImage(ipl);    // 对读入的图片进行缩放，使其宽或高最大值者刚好等于 256，再复制到 TheImage 中
	ShowImage(TheImage, pStatic);            // 调用显示图片函数    
	cvReleaseImage(&ipl);                        // 释放 ipl 占用的内存

}
