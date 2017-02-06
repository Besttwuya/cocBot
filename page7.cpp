// page7.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cocBot.h"
#include "page7.h"
#include "afxdialogex.h"

// page7 �Ի���
IMPLEMENT_DYNAMIC(page7, CDialog)
page7::page7(CWnd* pParent /*=NULL*/)
	: CDialog(page7::IDD, pParent)
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
	DDX_Control(pDX, IDC_CHECK8, DisableSetWindowSize);

	DDX_Control(pDX, IDC_EDIT1, m_edit1);

	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_COMBO2, Clear);
}


BEGIN_MESSAGE_MAP(page7, CDialog)
	ON_BN_CLICKED(IDC_CHECK8, &page7::OnDisableSetWindowSize)
	ON_BN_CLICKED(IDC_BUTTON1, &page7::OnBindWindowSet)
	ON_BN_CLICKED(IDC_BUTTON2, &page7::OnOpen1)

	ON_BN_CLICKED(IDC_BUTTON3, &page7::OnAdd)
	ON_BN_CLICKED(IDC_BUTTON4, &page7::OnClear)
END_MESSAGE_MAP()


// page7 ��Ϣ�������


void page7::OnDisableSetWindowSize()
{
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void page7::OnBindWindowSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IsShowBindSetWindow = true;
}


void page7::OnOpen1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CbotFunction* bot = new CbotFunction;
	CString path;
	path = bot->SelectFile("(�����ļ�(*.cbt)|*.cbt||");
	delete bot;
	m_edit1.SetWindowTextA(path);
}




void page7::OnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString winText,str;
	bool IsR = false;
	for (int i=0;i<15;i++)
	{
		SwitchModeVersion_1.GetWindowTextA(winText);
		for (int j=0;j<15;j++)
		{
			if (m_list1.GetItemText(j,1)==winText)
			{
				IsR = true;
				break;
			}
		}
		if (IsR)
		{
			AfxMessageBox(_T("�汾�ظ���������ѡ��"), MB_OK);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
