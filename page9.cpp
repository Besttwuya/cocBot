// page9.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cocBot.h"
#include "page9.h"
#include "afxdialogex.h"


// page9 �Ի���

IMPLEMENT_DYNAMIC(page9, CDialogEx)

page9::page9(CWnd* pParent /*=NULL*/)
	: CDialogEx(page9::IDD, pParent)
{

}

page9::~page9()
{
}

void page9::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEdit1);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}


BEGIN_MESSAGE_MAP(page9, CDialogEx)
END_MESSAGE_MAP()


// page9 ��Ϣ�������
