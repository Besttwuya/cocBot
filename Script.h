#pragma once

//脚本引擎类

class CScript
{
public:
	//构造函数
	CScript();
	//析构函数
	~CScript();
	//矩形区域
	struct screenRect
	{
		long x1;
		long y1;
		long x2;
		long y2;

	};
public:
	CAdbshell adb;               //Adb 处理函数
	LPCTSTR scriptVer;           //辅助版本号
	ArmyMsg attackArmy;          //攻击兵种数量
	CRichEditCtrl* pRichEditCtrl;//rich edit 控件指针，用于WriteLog函数，使用前务必进行初始化！

	
public:
	Cdmsoft dm;                  //大漠对象
	CbotFunction coc;            //bot 辅助处理函数
	Detail  LootRecord[15];      //记录资源函数
	int SwitchNo;                //切换编号
	int train_time;              //训练时间
	bool IsThreadRun;            //线程函数运行标志
	long GetScriptState();
	/* scriptStateCode = 0 : normal not start
	   scriptStateCode = 1 : normal start and run
	   scriptStateCode = 2 : switch start and run
	   scriptStateCode = 3 : thread suspend
	   scriptStateCode = -1 :ShouldWaitForArmy
       scriptStateCode = -2 :ShouldRestart 
	   scriptStateCode = -3 :ShouldSwitch
							
	 */
	long scriptStateCode;
	// mode path
	CString GetExePath();
public://功能函数
	bool CreateDm(int type=0);
	bool StopThread(HANDLE hThread=0);
	void Dealy(unsigned long mSeconds);
	void DealyRandTime(unsigned long minDeaySeconds, unsigned long maxDealySeconds);
	int ExcludeTooNearPos(CString allpos, long minDistance, int type, CString& result);
	int KillAdb();
	int SendXSolider(int type);
	int RepairPos(long x, long y, int type, long* resultX, long* resultY);
	int AttackArea(long x1, long y1, long x2, long y2, long type, long* result_x, long* result_y);
	int ClearAdvirtisment();
	int checkMainScreen();
	int RequestHelp();
	int CheckArmyNum(int* Ma_time);
	void ClearArmy();
	int SpeedTrain();
	int MakeArmy();
	int adbCmd(CString f_input);
	int AddArmy();
	int GetResource();
	int send_LightngSpell();
	int LightingAttack(long darkelixir);
	int WaitForReturnHome();
	int Main_Attack();
	int EqualAttack();
	int WriteLog(CString logSrtr,bool IsShow,COLORREF color,bool IsSave);
	int User_Attack();
	int check_deadbase();
	int check_defends();
	int SearchResult(long InputGold, long IputElixir, long gold, long Elixir, int type);
	int SearchFish();
	void CollectResource();
	int Donate();
	int UpGrade_Wall();
	int ConnectBsOrOthers();
	int CloseBS();
	int SetClientWindowSize();
	int StartCoc(CString _in_coc_ver);
	int StopCoc(CString _in_coc_ver);
	int DownTroophs();
	int ZoomOut();
	int Statistics();
	bool HideKey();
	int AddDict();
	int RepairAttackArmy(int oldArmyCount, int type,int &distance);
	int GetArmyMsg();
	int MakeRect(long srcX,long* x1,long* x2);
	long FindPicSuper(long x1,long y1,long x2,long y2, LPCTSTR path, LPCTSTR picName, int timesOut, bool Isclick=true);
	int adbClick(int x, int y);
	int adbSwipe(int x1, int y1, int x2, int y2);
	int adbKeyEvent(int keyCode);
	int adbInputText(CString text);
	int adbRunApp(CString bagNameAndClassName);
	int adbCloseApp(CString packageName);
};
//******************* thread proc ***************//
