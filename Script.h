#pragma once
//#include<vector>
#include "pipeshell.h"

//���ڷ�����־��Ϣ
typedef struct SENDINFO
{
	CString logStr;
	bool IsShow;
	COLORREF color;
	bool IsSave;
}SEND_INFO;
/*�л���Ϸ��Ϣ*/
struct COCINFO
{
	bool IsSwitch;
	int AppID;
	CString configName;
};
/*�ű���*/
class CScript
{
public:
	//���캯��
	CScript();
	//��������
	~CScript();
public:
	Cdmsoft			dm;							//��Į����
	CbotFunction	coc;						//bot ����������
	CGameInfo		LootRecord[MAX_SWITCH_COUNT];//��¼��Դ����
	COCINFO			cocInfo[MAX_SWITCH_COUNT];  //��¼�л���Ϣ
	CPipeShell		adb;						//Adb ��������
	CString			scriptVer;					//�����汾��
	ArmyInfo		attackArmy;					//������������
	//����ؼ�ָ�룬�����̺߳ͽ���������ͨѶ
	CProgressCtrl*	pProgress=NULL;				//CProgressCtrl �ؼ�ָ�룬����CheckArmyNum������ʹ��ǰ��ؽ��г�ʼ����
	//���
	HWND hParennt=NULL;							//�����ھ��
	long bindHwnd;								//�󶨴���
	CString appPlayerInstallDir;				//ģ������װ·��
	CWinThread* pThread=NULL;
public:

	int SwitchNo;								//�л����
	int trainTime;								//ѵ��ʱ��
	bool IsThreadRun;							//�̺߳������б�־
	int AppPlayerIndex;							//ģ�������
	int AppCocID;								//coc ���
	int AppPlayerType;							//ģ��������
	int townLevel = 9;							//���ǵȼ�
	bool IsOffLine;								//�Ƿ����ߵȵ�
	bool IsSwitch;								//�Ƿ��л�
	long GetScriptState();
	int army_camp = 200;						//��Ӫ����
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
public://���ܺ���
	//������Į
	bool CreateDm(int type=0);
	//�ӳ�
	void Dealy(unsigned long mSeconds);
	//����ӳ�
	void DealyRandTime(unsigned long minDeaySeconds, unsigned long maxDealySeconds);
	//����������
	void LeftClick(long x, long y);
	int KillAdb();
	/*ѡ��ʿ������������*/
	int SelectSolider(int type);
	/*ѡ��������������*/
	int SelectSpell(int type);
	/*ѡ��Ӣ��*/
	int SelectHero(int type);
	/*opencvͼ��ʶ��*/
	int ImageLoc(long x1, long y1, long x2, long y2, const char* file, double sim, int&ret_x, int&ret_y);
	/*���±�λ�ý����޸�*/
	int RepairPos(long x, long y, int type, long* resultX, long* resultY);
	/*�±�λ��*/
	int AttackArea(long x1, long y1, long x2, long y2, long type, long* result_x, long* result_y);
	/*��洦��*/
	int ClearAdvirtisment();
	/*�ȴ���Ϸ����������*/
	int WaitForMainScreen();
	/*����֧Ԯ*/
	int RequestHelp();
	/*����Ӫ����*/
	int CheckArmyNum(int* Ma_time);
	/*���ʿ��*/
	void ClearArmy();
	/*����*/
	int SpeedTrain();
	/*���*/
	int MakeArmy();
	//ͨ�� ģ���� adb ������
	/*
	strCmd ����*/
	int adbCmd(CString strCmd);
	//�׵�ģ����
	/*
	index ģ�������
	cmd ��Ӧ����
	*/
	int adbCmd(int index, CString cmd);
	/*����*/
	int AddArmy();
	/*�����Դ��Ϣ*/
	int GetResource();
	/*ʹ���׵編��*/
	int send_LightngSpell();
	int LightingAttack(long darkelixir);
	/*�ȴ����ش�ׯ*/
	int WaitForReturnHome();
	/*���ܹ���*/
	int Attack_Intel();
	/*���ֹ���*/
	int Attack_Equal();
	/*������־*/
	int SetLog(CString logSrtr,bool IsShow=true,COLORREF color=BLUECOLOR,bool IsSave=false);
	/*lua �ű�����*/
	int Attack_lua();
	/*����Ƿ�Ϊ����*/
	int CheckDeadbase();
	/*�������Ƿ�����*/
	int CheckDefends();
	/*������������д���*/
	int SearchResult(long InputGold, long IputElixir, long gold, long Elixir, int type);
	/*����*/
	int SearchFish();
	/*��Դ�ɼ�*/
	void CollectResource();
	/*���*/
	int DonateArmy();
	/*�жϡ�����*/
	int IdentifyIsDonate(int* array, int type = 2);
	/*������ǽ*/
	int UpGradeWall();
	/*����ģ����*/
	int ConnectAppPlayer();
	/*���÷ֱ���*/
	int SetClientWindowSize(int x=850,int y=667);
	/*����Ϸ*/
	int StartCoc();
	/*�ر���Ϸ*/
	int StopCoc();
	/*���Ʊ���*/
	int ControlTroophs();
	/*��С��Ϸ����*/
	int ZoomOut();
	/*���������*/
	bool HideKey();
	/*�����ֿ�*/
	int AddDict();
	/*�����±�λ��*/
	int RepairAttackArmy(int oldArmyCount,int &distance);
	/*��ȡ�����±���Ϣ*/
	int GetArmyMsg();
	/*����ocr ��Χ*/
	int MakeRect(long srcX,long* x1,long* x2);
	/*�ȴ�ĳ��ͼƬ*/
	long WaitPic(long x1,long y1,long x2,long y2, LPCTSTR path, LPCTSTR picName, int timesOut, bool Isclick=true);
	/*adb ���*/
	int adbClick(int x, int y);
	/*adb ����*/
	int adbSwipe(int x1, int y1, int x2, int y2);
	/*adb �¼�*/
	int adbKeyEvent(int keyCode);
	/*adb ��������*/
	int adbInputText(CString text);
	/*adb ����Ӧ��*/
	int adbRunApp(CString bagNameAndClassName);
	/*adb �ر�Ӧ��*/
	int adbCloseApp(CString packageName);
	/*ͳ��*/
	int Statistics();
	/*������*/
	int DonateClick(int type, int count, int y0);
	/*�ж��Ƿ���������*/
	int checkMainScreen();
	/*�жϲ��޸�һЩ����*/
	int checkScreenError();
	/*��ȡ�׵� list2����*/
	CString getList2(int x, int y);
	/*����ģ����*/
	int LaunchAppPlayer(int wParam);
	/*�ر�ģ����*/
	int QuitAppPlayer( int wParam);
	/*����*/
	int RestartScript();  //�ű�����
	/*���ߵȴ�*/
	int WaitForTrainArmy();
	/*�л�*/
	int SwitchCoc();
	/*����*/
	int Attack();
	//
	//�ű���ʼ��
	int script_init();
	//�ű�������
	int script_main();
	/*���þ��*/
	int SetBindHwnd();
};




//�࿪��Ϣ


static unsigned  EntryScript(LPVOID pParam);
//��ʼһ���ű�  index -��ţ�appHwnd-���ھ����configFile-�����ļ�
CScript*	StartOneScript(CScript *script_info,int index=-1,const char* configFile=nullptr);

BOOL        StopOneScript(CScript*  script_info);

BOOL        SuspendOneScript(CScript* script_info);

BOOL        ResumOneScript(CScript* script_info);

BOOL        SuspendAllScript(CScript* script_info[]);

BOOL        ResumAllScript(CScript* script_info[]);

BOOL        StopAllScript(CScript* all_script_info[]);

