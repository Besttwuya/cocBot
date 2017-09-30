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
	// ��ȡͼƬ�Ŀ�͸�
	int w = img->width;
	int h = img->height;

	// �ҳ���͸��еĽϴ�ֵ��
	//int max = (w > h) ? w : h;

	// ���㽫ͼƬ���ŵ�TheImage��������ı�������
	float scaleX = (float)((float)w / SCREENSHOWWIDTH);
	float scaleY = (float)((float)h / SCREENSHOWHEIGHT);
	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)(w / scaleX);
	int nh = (int)(h / scaleY);

	// Ϊ�˽����ź��ͼƬ���� TheImage �����в�λ�������ͼƬ�� TheImage ���Ͻǵ���������ֵ
	int tlx = (nw > nh) ? 0 : (int)(SCREENSHOWWIDTH - nw) / 2;
	int tly = (nw > nh) ? (int)(SCREENSHOWHEIGHT - nh) / 2 : 0;

	// ���� TheImage �� ROI ������������ͼƬ img
	cvSetImageROI(TheImage, cvRect(tlx, tly, nw, nh));

	// ��ͼƬ img �������ţ������뵽 TheImage ��
	cvResize(img, TheImage);

	// ���� TheImage �� ROI ׼��������һ��ͼƬ
	cvResetImageROI(TheImage);
}


void CGameScreen::ShowImage(IplImage* img, CWnd* pWnd)
{
	CDC* pDC = pWnd->GetDC();        // �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();                // ��ȡ HDC(�豸���) �����л�ͼ����
	//HWND hwnd = pWnd->m_hWnd;

	CRect rect;
	pWnd->GetClientRect(&rect);
	int rw = rect.right - rect.left;            // ���ͼƬ�ؼ��Ŀ�͸�
	int rh = rect.bottom - rect.top;
	int iw = img->width;                        // ��ȡͼƬ�Ŀ�͸�
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;                    // ʹͼƬ����ʾλ�������ڿؼ�������
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	CvvImage cimg;
	cimg.CopyOf(img);                            // ����ͼƬ
	cimg.DrawToHDC(hDC, &rect);                // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������

	//ReleaseDC(hwnd,hDC);
}


void CGameScreen::gameScreenShow(const char* filename)
{
	
	IplImage* ipl = cvLoadImage(filename, 1);    // ��ȡͼƬ�����浽һ���ֲ����� ipl ��
	if (!ipl)                                    // �ж��Ƿ�ɹ�����ͼƬ
		return;
	if (TheImage)                                // ����һ����ʾ��ͼƬ��������
		cvZero(TheImage);

	ResizeImage(ipl);    // �Զ����ͼƬ�������ţ�ʹ��������ֵ�߸պõ��� 256���ٸ��Ƶ� TheImage ��
	ShowImage(TheImage, pStatic);            // ������ʾͼƬ����    
	cvReleaseImage(&ipl);                        // �ͷ� ipl ռ�õ��ڴ�

}
