#pragma once

//�ű�������

class CScript
{
public:
	//���캯��
	CScript();
	//��������
	~CScript();
	//��������
	struct screenRect
	{
		long x1;
		long y1;
		long x2;
		long y2;

	};
public:
	CAdbshell adb;               //Adb ������
	LPCTSTR scriptVer;           //�����汾��
	ArmyMsg attackArmy;          //������������
	CRichEditCtrl* pRichEditCtrl;//rich edit �ؼ�ָ�룬����WriteLog������ʹ��ǰ��ؽ��г�ʼ����

	
public:
	Cdmsoft dm;                  //��Į����
	CbotFunction coc;            //bot ����������
	Detail  LootRecord[15];      //��¼��Դ����
	int SwitchNo;                //�л����
	int train_time;              //ѵ��ʱ��
	bool IsThreadRun;            //�̺߳������б�־
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
public://���ܺ���
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
