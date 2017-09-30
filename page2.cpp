// page2.cpp : 实现文件
//

#include "stdafx.h"
#include "cocBot.h"
#include "page2.h"
#include "afxdialogex.h"


// page2 对话框

IMPLEMENT_DYNAMIC(page2, CDialog)

page2::page2(CWnd* pParent /*=NULL*/)
	: CDialog(page2::IDD, pParent)
	,m_strLine(_T(""))
	,m_ptOrigin(0)
{

}

page2::~page2()
{
}

void page2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, TrainArmyStyle);
	DDX_Control(pDX, IDC_COMBO2, IsClearArmy);
	DDX_Control(pDX, IDC_COMBO3, IsAddArmy);
	DDX_Control(pDX, IDC_EDIT1, Barbarin);
	DDX_Control(pDX, IDC_EDIT2, Archer);
	DDX_Control(pDX, IDC_EDIT3, Giant);
	DDX_Control(pDX, IDC_EDIT4, Goblin);
	DDX_Control(pDX, IDC_EDIT5, WallBreaker);
	DDX_Control(pDX, IDC_EDIT6, Ballon);
	DDX_Control(pDX, IDC_EDIT7, Wizard);
	DDX_Control(pDX, IDC_EDIT8, Healer);
	DDX_Control(pDX, IDC_EDIT9, Dragon);
	DDX_Control(pDX, IDC_EDIT10, Peka);
	DDX_Control(pDX, IDC_EDIT11, BabyDragon);
	DDX_Control(pDX, IDC_EDIT12, Miner);
	DDX_Control(pDX, IDC_EDIT13, Minion);
	DDX_Control(pDX, IDC_EDIT14, HogRider);
	DDX_Control(pDX, IDC_EDIT15, Valkyrie);
	DDX_Control(pDX, IDC_EDIT16, Golem);
	DDX_Control(pDX, IDC_EDIT17, Witch);
	DDX_Control(pDX, IDC_EDIT18, LavaHound);
	DDX_Control(pDX, IDC_EDIT19, BowLer);
	DDX_Control(pDX, IDC_EDIT20, LightingSpell);
	DDX_Control(pDX, IDC_EDIT21, HealingSpell);
	DDX_Control(pDX, IDC_EDIT22, RageSpell);
	DDX_Control(pDX, IDC_EDIT23, JumpSpell);
	DDX_Control(pDX, IDC_EDIT24, FreezeSpell);
	DDX_Control(pDX, IDC_EDIT25, CloneSpell);
	DDX_Control(pDX, IDC_EDIT26, PoisonSpell);
	DDX_Control(pDX, IDC_EDIT27, EarthquakeSpell);
	DDX_Control(pDX, IDC_EDIT28, HasteSpell);
	DDX_Control(pDX, IDC_EDIT29, SkeletonSpell);
	DDX_Control(pDX, IDC_CHECK1, IsSpeedUp);
	DDX_Control(pDX, IDC_EDIT30, SpeedUpBegin);
	DDX_Control(pDX, IDC_EDIT31, SpeedUpEnd);
	DDX_Control(pDX, IDC_AllCount, AllCount);
}


BEGIN_MESSAGE_MAP(page2, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &page2::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &page2::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &page2::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &page2::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &page2::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &page2::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &page2::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &page2::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &page2::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &page2::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &page2::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, &page2::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, &page2::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, &page2::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &page2::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, &page2::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, &page2::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, &page2::OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, &page2::OnEnChangeEdit19)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// page2 消息处理程序



void page2::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::TotalInput()
{
	CString winText;
	int TotalArmy = 0;
	Barbarin.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);

	Archer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);
	Giant.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*5;
	Goblin.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText);
	WallBreaker.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*2;
	Ballon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*5;
	Wizard.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*4;
	Healer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*14;
	Dragon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*20;
	Peka.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*25;
	BabyDragon.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*10;
	Miner.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*5;
	Minion.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*2;
	HogRider.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*5;
	Valkyrie.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*8;
	Golem.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*30;
	Witch.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*12;
	LavaHound.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*30;
	BowLer.GetWindowTextA(winText);
	TotalArmy += _ttoi(winText)*6;
	winText.Format("%d", TotalArmy);
	AllCount.SetWindowTextA(winText);
}


void page2::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit11()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit12()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit13()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit14()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit15()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit16()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit17()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit18()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnEnChangeEdit19()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	TotalInput();
}


void page2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()
	//CRect rect;
	//GetClientRect(rect);
	//dc.FillSolidRect(rect, RGB(0Xc0, 0Xc0, 0Xc0));
	//dc.FillPath();
}
