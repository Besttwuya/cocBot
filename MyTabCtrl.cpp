// MyTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "newcocbot.h"
#include "MyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{

}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序

void CMyTabCtrl::DrawItem(_In_ LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CBrush cbr;
	cbr.CreateSolidBrush(RGB(0,0,0));
	char szTabText[100];
	TC_ITEM tci;
	memset(szTabText,'\0',sizeof(szTabText));
	tci.mask =TCIF_TEXT;
	tci.pszText=szTabText;
	tci.cchTextMax= sizeof(szTabText)-1;
	GetItem(lpDrawItemStruct->itemID,&tci);
	//
	CDC* dc =CDC::FromHandle(lpDrawItemStruct->hDC);
	dc->FillRect(&lpDrawItemStruct->rcItem,&cbr);
	// draw text
	dc->SetBkColor(RGB(0X2d,0X2d,0X30));
	dc->SetTextColor(RGB(0x0,0x0,0x0));
	RECT rc;
	rc=lpDrawItemStruct->rcItem;
	rc.top+=3;
	dc->DrawText(tci.pszText,lstrlen(tci.pszText),&rc,DT_CENTER);

}


BOOL CMyTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(RGB(0Xd2,0X1e,0X1e));
	pDC->FillRect(&rect,&brush);

	//return CTabCtrl::OnEraseBkgnd(pDC);
	return TRUE;
}
