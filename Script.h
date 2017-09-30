#pragma once
//#include<vector>
#include "pipeshell.h"

//用于发送日志信息
typedef struct SENDINFO
{
	CString logStr;
	bool IsShow;
	COLORREF color;
	bool IsSave;
}SEND_INFO;
/*切换游戏信息*/
struct COCINFO
{
	bool IsSwitch;
	int AppID;
	CString configName;
};
/*脚本类*/
class CScript
{
public:
	//构造函数
	CScript();
	//析构函数
	~CScript();
public:
	Cdmsoft			dm;							//大漠对象
	CbotFunction	coc;						//bot 辅助处理函数
	CGameInfo		LootRecord[MAX_SWITCH_COUNT];//记录资源函数
	COCINFO			cocInfo[MAX_SWITCH_COUNT];  //记录切换信息
	CPipeShell		adb;						//Adb 处理函数类
	CString			scriptVer;					//辅助版本号
	ArmyInfo		attackArmy;					//攻击兵种数量
	//界面控件指针，用于线程和界面间的数据通讯
	CProgressCtrl*	pProgress=NULL;				//CProgressCtrl 控件指针，用于CheckArmyNum函数，使用前务必进行初始化！
	//句柄
	HWND hParennt=NULL;							//父窗口句柄
	long bindHwnd;								//绑定窗口
	CString appPlayerInstallDir;				//模拟器安装路径
	CWinThread* pThread=NULL;
public:

	int SwitchNo;								//切换编号
	int trainTime;								//训练时间
	bool IsThreadRun;							//线程函数运行标志
	int AppPlayerIndex;							//模拟器编号
	int AppCocID;								//coc 编号
	int AppPlayerType;							//模拟器类型
	int townLevel = 9;							//主城等级
	bool IsOffLine;								//是否下线等等
	bool IsSwitch;								//是否切换
	long GetScriptState();
	int army_camp = 200;						//兵营容量
	/* scriptStateCode = 0 : normal not start
	   scriptStateCode = 1 : normal start and run
	   scriptStateCode = 2 : switch start and run
	   scriptStateCode = 3 : thread suspend
	   scriptStateCode = -1 :ShouldWaitForArmy
       scriptStateCode = -2 :ShouldRestart 
	   scriptStateCode = -3 :ShouldSwitch
							
	 */
	long scriptInfo;
	// mode path
	CString GetExePath();
public://功能函数
	//创建大漠
	bool CreateDm(int type=0);
	//延迟
	void Dealy(unsigned long mSeconds);
	//随机延迟
	void DealyRandTime(unsigned long minDeaySeconds, unsigned long maxDealySeconds);
	//鼠标左键单击
	void LeftClick(long x, long y);
	int KillAdb();
	/*选择士兵，返回数量*/
	int SelectSolider(int type);
	/*选择法术，返回数量*/
	int SelectSpell(int type);
	/*选择英雄*/
	int SelectHero(int type);
	/*opencv图像识别*/
	int ImageLoc(long x1, long y1, long x2, long y2, const char* file, double sim, int&ret_x, int&ret_y);
	/*对下兵位置进行修复*/
	int RepairPos(long x, long y, int type, long* resultX, long* resultY);
	/*下兵位置*/
	int AttackArea(long x1, long y1, long x2, long y2, long type, long* result_x, long* result_y);
	/*广告处理*/
	int ClearAdvirtisment();
	/*等待游戏主界面载入*/
	int WaitForMainScreen();
	/*请求支援*/
	int RequestHelp();
	/*检测兵营容量*/
	int CheckArmyNum(int* Ma_time);
	/*清除士兵*/
	void ClearArmy();
	/*加速*/
	int SpeedTrain();
	/*造兵*/
	int MakeArmy();
	//通用 模拟器 adb 命令行
	/*
	strCmd 命令*/
	int adbCmd(CString strCmd);
	//雷电模拟器
	/*
	index 模拟器序号
	cmd 对应命令
	*/
	int adbCmd(int index, CString cmd);
	/*补兵*/
	int AddArmy();
	/*获得资源信息*/
	int GetResource();
	/*使用雷电法术*/
	int send_LightngSpell();
	int LightingAttack(long darkelixir);
	/*等待返回村庄*/
	int WaitForReturnHome();
	/*智能攻击*/
	int Attack_Intel();
	/*均分攻击*/
	int Attack_Equal();
	/*设置日志*/
	int SetLog(CString logSrtr,bool IsShow=true,COLORREF color=BLUECOLOR,bool IsSave=false);
	/*lua 脚本攻击*/
	int Attack_lua();
	/*检测是否为死鱼*/
	int CheckDeadbase();
	/*检测防御是否满足*/
	int CheckDefends();
	/*对搜索结果进行处理*/
	int SearchResult(long InputGold, long IputElixir, long gold, long Elixir, int type);
	/*搜鱼*/
	int SearchFish();
	/*资源采集*/
	void CollectResource();
	/*捐兵*/
	int DonateArmy();
	/*判断。。。*/
	int IdentifyIsDonate(int* array, int type = 2);
	/*升级城墙*/
	int UpGradeWall();
	/*连接模拟器*/
	int ConnectAppPlayer();
	/*设置分辨率*/
	int SetClientWindowSize(int x=850,int y=667);
	/*打开游戏*/
	int StartCoc();
	/*关闭游戏*/
	int StopCoc();
	/*控制杯段*/
	int ControlTroophs();
	/*缩小游戏画面*/
	int ZoomOut();
	/*隐藏虚拟键*/
	bool HideKey();
	/*载入字库*/
	int AddDict();
	/*修正下兵位置*/
	int RepairAttackArmy(int oldArmyCount,int &distance);
	/*获取所有下兵信息*/
	int GetArmyMsg();
	/*控制ocr 范围*/
	int MakeRect(long srcX,long* x1,long* x2);
	/*等待某个图片*/
	long WaitPic(long x1,long y1,long x2,long y2, LPCTSTR path, LPCTSTR picName, int timesOut, bool Isclick=true);
	/*adb 点击*/
	int adbClick(int x, int y);
	/*adb 滑动*/
	int adbSwipe(int x1, int y1, int x2, int y2);
	/*adb 事件*/
	int adbKeyEvent(int keyCode);
	/*adb 文字输入*/
	int adbInputText(CString text);
	/*adb 启动应用*/
	int adbRunApp(CString bagNameAndClassName);
	/*adb 关闭应用*/
	int adbCloseApp(CString packageName);
	/*统计*/
	int Statistics();
	/*捐兵点击*/
	int DonateClick(int type, int count, int y0);
	/*判断是否在主界面*/
	int checkMainScreen();
	/*判断并修复一些错误*/
	int checkScreenError();
	/*获取雷电 list2命令*/
	CString getList2(int x, int y);
	/*启动模拟器*/
	int LaunchAppPlayer(int wParam);
	/*关闭模拟器*/
	int QuitAppPlayer( int wParam);
	/*重启*/
	int RestartScript();  //脚本重启
	/*下线等待*/
	int WaitForTrainArmy();
	/*切换*/
	int SwitchCoc();
	/*进攻*/
	int Attack();
	//
	//脚本初始化
	int script_init();
	//脚本主函数
	int script_main();
	/*设置句柄*/
	int SetBindHwnd();
};




//多开信息


static unsigned  EntryScript(LPVOID pParam);
//开始一个脚本  index -序号，appHwnd-窗口句柄，configFile-配置文件
CScript*	StartOneScript(CScript *script_info,int index=-1,const char* configFile=nullptr);

BOOL        StopOneScript(CScript*  script_info);

BOOL        SuspendOneScript(CScript* script_info);

BOOL        ResumOneScript(CScript* script_info);

BOOL        SuspendAllScript(CScript* script_info[]);

BOOL        ResumAllScript(CScript* script_info[]);

BOOL        StopAllScript(CScript* all_script_info[]);

