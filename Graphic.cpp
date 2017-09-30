// Graphic.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "Graphic.h"
#include "afxdialogex.h"

// Graphic 对话框

IMPLEMENT_DYNAMIC(Graphic, CDialogEx)

Graphic::Graphic(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GRAPHIC, pParent)
{

	EnableAutomation();

}

Graphic::~Graphic()
{
}

void Graphic::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void Graphic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Graphic, CDialogEx)
	ON_BN_CLICKED(IDC_LOAD_POS, &Graphic::OnBnClickedLoadPos)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Graphic, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IGraphic 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {7D22B051-2F5E-4386-9267-4537DEA36379}
static const IID IID_IGraphic =
{ 0x7D22B051, 0x2F5E, 0x4386, { 0x92, 0x67, 0x45, 0x37, 0xDE, 0xA3, 0x63, 0x79 } };

BEGIN_INTERFACE_MAP(Graphic, CDialogEx)
	INTERFACE_PART(Graphic, IID_IGraphic, Dispatch)
END_INTERFACE_MAP()


// Graphic 消息处理程序


void Graphic::OnBnClickedLoadPos()
{
	// TODO: 在此添加控件通知处理程序代码
	CbotFunction bot ;
	CString filename;
	filename = bot.SelectFile("配置文件(*.txt)|*.txt||");
	using namespace std;
	CFile file;
	if (false == file.Open(filename, CFile::modeRead))
	{
		AfxMessageBox("open file false");
		return;
	}

	DWORD file_len = file.GetLength();
	char* buff = new char[file_len + 1];
	file.Read(buff, file_len);
	file.Close();
	buff[file_len] = '\0';
	file.Close();

	vector<string>vstr1, vstr_x,vstr_y;
	_split(buff, vstr1, "|");
	if (vstr1.size() != 2)
	{
		AfxMessageBox("not size 2");
		return;
	}
	_split(vstr1[0], vstr_x, ",");
	_split(vstr1[1], vstr_y, ",");
	if (vstr_x.size() != vstr_y.size())
	{
		AfxMessageBox("not equal size");
		return;
	}
	int max_pos = vstr_x.size();
	
	vpos_x.clear();
	vpos_y.clear();
	for (int i=0;i<max_pos;i++)
	{
		vpos_x.push_back(_ttoi(vstr_x[i].c_str()));
		vpos_y.push_back(_ttoi(vstr_y[i].c_str()));
		
	}
	RedrawWindow();
}


void Graphic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rc;
	GetClientRect(rc);
	if (vpos_x.size() == 0)return;
	int max_pos = vpos_x.size();
	for (int i=0;i<max_pos;i++)
	{
		dc.SetPixel(vpos_x[i], vpos_y[i], 0xff);
	}
}
