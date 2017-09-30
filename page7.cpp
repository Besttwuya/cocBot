// page7.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "page7.h"
#include "afxdialogex.h"

// page7 对话框
IMPLEMENT_DYNAMIC(page7, CDialog)
page7::page7(CWnd* pParent /*=NULL*/)
	: CDialog(page7::IDD, pParent)
	, app_player_path(_T(""))
{
	
}

page7::~page7()
{
}

void page7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, DeBugSearchShoot);
	DDX_Control(pDX, IDC_CHECK2, DebugLocateAD);
	DDX_Control(pDX, IDC_CHECK7, SetShowErrorMsg);
	DDX_Control(pDX, IDC_COMBO1, SwitchModeVersion_1);
	DDX_Control(pDX, IDC_CHECK3, IsSwitchMode);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);

	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_COMBO2, Clear);
}


BEGIN_MESSAGE_MAP(page7, CDialog)
	ON_BN_CLICKED(IDC_CHECK8, &page7::OnDisableSetWindowSize)
	ON_BN_CLICKED(IDC_BUTTON2, &page7::OnOpen1)

	ON_BN_CLICKED(IDC_BUTTON3, &page7::OnAdd)
	ON_BN_CLICKED(IDC_BUTTON4, &page7::OnClear)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SELECT_PATH, &page7::OnBnClickedSelectPath)
	ON_BN_CLICKED(IDC_SHOW_GRAPHIC, &page7::OnBnClickedShowGraphic)
END_MESSAGE_MAP()


// page7 消息处理程序


void page7::OnDisableSetWindowSize()
{
	
	// TODO: 在此添加控件通知处理程序代码
}




void page7::OnOpen1()
{
	// TODO: 在此添加控件通知处理程序代码
	CbotFunction* bot = new CbotFunction;
	CString path;
	path = bot->SelectFile("(配置文件(*.ini)|*.ini||");
	delete bot;
	m_edit1.SetWindowTextA(path);
}




void page7::OnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString winText,str;
	bool IsR = false;
	for (int i=0;i<MAX_SWITCH_COUNT;i++)
	{
		SwitchModeVersion_1.GetWindowTextA(winText);
		for (int j=0;j<MAX_SWITCH_COUNT;j++)
		{
			if (m_list1.GetItemText(j,1)==winText)
			{
				IsR = true;
				break;
			}
		}
		if (IsR)
		{
			AfxMessageBox(_T("版本重复！请重新选择！"), MB_OK);
			break;
		}
		if (m_list1.GetItemText(i, 1).GetLength() < 3)
		{
			str.Format("%d", SwitchModeVersion_1.GetCurSel());
			m_list1.SetItemText(i, 1, winText);
			m_list1.SetItemText(i, 3, str);
			m_edit1.GetWindowTextA(winText);
			m_list1.SetItemText(i, 2, winText);
			break;
		}
		
	}
	
}


void page7::OnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	int clearType = Clear.GetCurSel();
	if (clearType==0)
	{
		for (int i=0;i<15;i++)
		{
			m_list1.SetItemText(i, 1, "");
			m_list1.SetItemText(i, 2, "");
			m_list1.SetItemText(i, 3, "");
			m_list1.SetCheck(i, false);
		}
	}
	if (clearType>0)
	{
		clearType -= 1;
		m_list1.SetItemText(clearType, 1, "");
		m_list1.SetItemText(clearType, 2, "");
		m_list1.SetItemText(clearType, 3, "");
		m_list1.SetCheck(clearType, false);
	}

}


void page7::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()
	/*CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0Xc0, 0Xc0, 0Xc0));
	dc.FillPath();*/
}





void page7::OnBnClickedSelectPath()
{
	// TODO: 在此添加控件通知处理程序代码
	char szPath[MAX_PATH]; //存放选择的目录路径 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择模拟器安装目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		//str.Format("选择的目录为 %s", szPath);
		//AfxMessageBox(str); 
		SetDlgItemText(IDC_EDIT2, szPath);
		app_player_path = szPath;
	}
	
}


void page7::OnBnClickedShowGraphic()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(GetParent()->m_hWnd, WM_SHOW_GRAHIC, 0, 0);
}
