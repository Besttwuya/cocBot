// page5.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "page5.h"
#include "afxdialogex.h"


// page5 对话框

IMPLEMENT_DYNAMIC(page5, CDialogEx)

page5::page5(CWnd* pParent /*=NULL*/)
	: CDialogEx(page5::IDD, pParent)
{

}

page5::~page5()
{
}

void page5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, IsDonateSendGetRet);
	DDX_Control(pDX, IDC_CHECK2, IsDonateNotFull);
	DDX_Control(pDX, IDC_EDIT1, DonateMinSendGetRet);
	DDX_Control(pDX, IDC_COMBO1, DonateType);
	DDX_Control(pDX, IDC_EDIT2, DonateCount);
	DDX_Control(pDX, IDC_EDIT3, DonateDealy);
	DDX_Control(pDX, IDC_CHECK3, IsBarbarin);
	DDX_Control(pDX, IDC_CHECK4, IsArcher);
	DDX_Control(pDX, IDC_CHECK5, IsGiant);
	DDX_Control(pDX, IDC_CHECK6, IsGoblin);
	DDX_Control(pDX, IDC_CHECK7, IsWallBreaker);
	DDX_Control(pDX, IDC_CHECK8, IsBallon);
	DDX_Control(pDX, IDC_CHECK9, IsWizard);
	DDX_Control(pDX, IDC_CHECK10, IsHealer);
	DDX_Control(pDX, IDC_CHECK11, IsDragon);
	DDX_Control(pDX, IDC_CHECK12, IsPeka);
	DDX_Control(pDX, IDC_CHECK13, IsBabyDragon);
	DDX_Control(pDX, IDC_CHECK14, IsMiner);
	DDX_Control(pDX, IDC_CHECK15, IsMinion);
	DDX_Control(pDX, IDC_CHECK16, IsHogRider);
	DDX_Control(pDX, IDC_CHECK17, IsValkyrie);
	DDX_Control(pDX, IDC_CHECK18, IsGolem);
	DDX_Control(pDX, IDC_CHECK19, IsWitch);
	DDX_Control(pDX, IDC_CHECK20, IsLavaHound);
	DDX_Control(pDX, IDC_CHECK21, IsBower);
	DDX_Control(pDX, IDC_CHECK22, IsPoison);
	DDX_Control(pDX, IDC_CHECK23, IsEarthquake);
	DDX_Control(pDX, IDC_CHECK24, IsHaste);
	DDX_Control(pDX, IDC_CHECK25, IsSkeleton);
	DDX_Control(pDX, IDC_LIST1, ListKeyWord);
	DDX_Control(pDX, IDC_COMBO2, KeyWordToDonate);
	DDX_Control(pDX, IDC_COMBO3, InputKeyWord);
	DDX_Control(pDX, IDC_REQUEST_WORDS, requestWords);
	DDX_Control(pDX, IDC_CHECK26, IsChangeWords);
}


BEGIN_MESSAGE_MAP(page5, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &page5::OnAddKeyWord)
	ON_BN_CLICKED(IDC_BUTTON2, &page5::OnClearKeyWord)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// page5 消息处理程序




void page5::OnAddKeyWord()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Input_str,keyStr;
	InputKeyWord.GetWindowText(Input_str);
	int index = KeyWordToDonate.GetCurSel();
	keyStr = ListKeyWord.GetItemText(index, 1);
	if (keyStr.Find(Input_str)<0)
	{
		if (keyStr.GetLength()>0)
		{
			keyStr += ",";
		}
		
		keyStr += Input_str;
		ListKeyWord.SetItemText(index, 1, keyStr);
	}
	
	
}


void page5::OnClearKeyWord()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i=0;i<21;i++)
	{
		ListKeyWord.SetItemText(i,1,"");
		//ListKeyWord.SetItemText(i,2,"");
	}
}


void page5::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}
