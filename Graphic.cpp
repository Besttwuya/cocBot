// Graphic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cocBot.h"
#include "Graphic.h"
#include "afxdialogex.h"

// Graphic �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IGraphic ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {7D22B051-2F5E-4386-9267-4537DEA36379}
static const IID IID_IGraphic =
{ 0x7D22B051, 0x2F5E, 0x4386, { 0x92, 0x67, 0x45, 0x37, 0xDE, 0xA3, 0x63, 0x79 } };

BEGIN_INTERFACE_MAP(Graphic, CDialogEx)
	INTERFACE_PART(Graphic, IID_IGraphic, Dispatch)
END_INTERFACE_MAP()


// Graphic ��Ϣ�������


void Graphic::OnBnClickedLoadPos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CbotFunction bot ;
	CString filename;
	filename = bot.SelectFile("�����ļ�(*.txt)|*.txt||");
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
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rc;
	GetClientRect(rc);
	if (vpos_x.size() == 0)return;
	int max_pos = vpos_x.size();
	for (int i=0;i<max_pos;i++)
	{
		dc.SetPixel(vpos_x[i], vpos_y[i], 0xff);
	}
}
