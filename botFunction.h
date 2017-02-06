#ifndef __BOTFUNCTION_H__
#define __BOTFUNCTION_H__
class CbotFunction
{
private:
	CString str_all_set;
	CString file_path;
	CString now_version;
	CString ClashOfClans_Version;
	long AttackCount;
	long SearchCount;
	// This structure is used internally by the XSleep function 
	
public:
	CTime tm;
	CString State_str;
	CString ConfigInfo;
	CString  SearchStr;
	long parenthwnd;
	long BindHwnd;
	int BindType;
	void SetAllSetting(CString in_set);
	void SetVersion(CString in_ver);
	void SetPath(CString _in_path);
	unsigned int WriteFile(CString _in_FileName,CString _in_message);
	bool SetSingleSetting(CString TargetName,CString Value);
	CString ReadFile(CString _in_FileName);
	CString ReadFileWithoutPath(CString _in_PathAndFlieName);
	CString GetPath();
	CString GetExePath();
	CString GetVersion();
	CString GetSingleSetting(CString in_need);
	unsigned int GetMode();
	unsigned int IsWaitForTrainArmy();
	unsigned int IsRequestHelp();
	unsigned int Dealy(long DelayCount);
	unsigned int SetCocVer(CString ver);
	CString GetCocVer();
	CString GetNowTime(int type);
	long Initialize();
	long AddSomeCount(int type,long keyvalue);
	long GetSomeCount(int type);
	CString GetConfig(CString TargetName, CString LeftStr, CString RightStr);
	CString GetConfig(CString configStr, CString TargetName, CString LeftStr, CString RightStr);
	void ScreenCapture(CString _in_file_name);
	void SetStartTime();
	bool KillProcessById(DWORD pID);
	void FileSearch(CString root);
	CString SelectFile(CString Str);
	long SpiltStr(char* strToken, const char* strDelimit,CString& result);
private:

protected:
	CString License;
	int StartYear;
	int StartMonth;
	int StartDay;
	int StartHour;
	int StartMinute;
	int StartSecond;

};





class Detail
{
public:
	void InitlizeDetail();
	Detail();
private:
	long StartTime;
	long LootGold;
	long LootElixir;
	long LootDarkElixir;
	long LootTroophs;
	long NowTime;
	long RunTime;
public:
	long NowGold;
	long NowElixir;
	long NowDarkElixir;
	long NowTroophs;
	long StartGold;
	long StartElixir;
	long StartDarkElixir;
	long StartTroophs;
	float ArmyRet;
	long SetStartResource(long _in_StartGold,long _in_StartElixir,long _in_StartDarkElixir,long _in_StartTroophs);
	long SetNowResource(long _in_NowGold,long _in_NowElixir,long _in_NowDarkElixir,long _in_NowTroophs);
	long GetLootGold();
	long GetLootElixir();
	long GetLootDarkElixir();
	long GetLootTroophs();
	long GetRunTime();
	bool IsFirstRecord;
	bool IsRecordSuccess;
};
class Reg
{
private:
	long RunTime;
	long NowTime;
public:


};
struct ArmyMsg
{
	int giant;
	int babarin;
	int archer;
	int goblin;
	int wallbreaker;
	int wizard;
};

#endif