#ifndef __BOTFUNCTION_H__
#define __BOTFUNCTION_H__
#include <string>
#include <map>
class CbotFunction
{
private:
	
	CString filePath;

	
	
public:
	CTime tm;
	CString  SearchStr;
	/*用于载入各种配置数据*/
	std::map<CString, CString>m_map;

	void SetPath(CString _in_path);
	unsigned int WriteFile(CString _in_FileName,CString _in_message);
	CString ReadFile(CString _in_FileName);
	CString ReadFileWithoutPath(CString _in_PathAndFlieName);
	CString GetPath();
	CString GetExePath();
	/*获取某个信息*/
	CString getSets(const CString& key);
	int getSetsInt(const CString& key);
	void setSetsStr(const CString& key, const CString& value);
	void setSetsInt(CString key, int value);
	/*从文件加载设置*/
	bool LoadSets(CString file);
	/*保存设置到文件*/
	bool SaveSets(CString file);
	unsigned int Dealy(long DelayCount);
	CString GetNowTime(int type);
	long Initialize();
	void ScreenCapture(CString _in_file_name);
	void SetStartTime();
	bool KillProcessById(DWORD pID);
	void FileSearch(CString root,CString type);
	CString SelectFile(const char* fileStr);
	bool compareStr(const char* firstStr, const char* nextStr);
private:

protected:
	int StartYear;
	int StartMonth;
	int StartDay;
	int StartHour;
	int StartMinute;
	int StartSecond;

};





class CGameInfo
{
public:
	void InitlizeDetail();
	CGameInfo();
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
struct ArmyInfo
{
	int giant;
	int babarin;
	int archer;
	int goblin;
	int wallbreaker;
	int wizard;
};


/*数组命名空间
处理大量数据的算法，例如 排序，查找...
*/
namespace Array
{
	//随机初始化数组
	template<class _Ty>
	int initArrayRand(_Ty* pArray, unsigned int n, _Ty rangeMin = 0, _Ty rangeMax = 100)
	{
		srand(time(0));
		int temp = rangeMax - rangeMin;
		if (temp <= 0) return -1;
		for (int i = 0; i < n; i++)
		{
			pArray[i] = rangeMin + rand() % temp;

		}
		return 0;
	}
	//选择法排序
	template<class _Ty>
	int sortArray(_Ty* array, unsigned int n)
	{
		int smallIndex;
		int pass, j;
		_Ty temp;
		//passs range 0,n-2
		for (pass = 0; pass < n - 1; pass++)
		{
			//从 下标 pass开始扫描子表
			smallIndex = pass;
			// j遍历子表，从array[pass+1]到array[n-1]
			for (j = pass + 1; j < n; j++)

				if (array[j] < array[smallIndex])
					//如果找到更小元素，则将 smallIndex 赋值给该位置
					smallIndex = j;
			//将表中最小与array[pass]交换
			if (smallIndex != pass)
			{
				temp = array[pass];
				array[pass] = array[smallIndex];
				array[smallIndex] = temp;
			}

		}
		return 0;
	}
	//查找，顺序查找
	template<class _Ty>
	int findArray(const _Ty* src, unsigned int n1, const _Ty*targetArr, unsigned int n2)
	{
		if (n1 < n2) return -1;
		//先找第一个
		int firstIndex, i, j;
		for (i = 0; i < n1; i++)
			//相等的话，进入匹配
			if (src[i] == targetArr[0])
			{
				firstIndex = i;
				if (firstIndex > n1 - n2) return -1;
				for (j = 1; j < n2; j++)
					//如果发现不等，跳出，进入下一轮查找
					if (src[firstIndex + j] != targetArr[j]) break;
				//循环正常结束，表明完全匹配，返回 firstIndex
				if (j == n2) return firstIndex;

			}
		//失败
		return -1;
	}
	//二维点集距离排序算法
	template<class _Ty>
	int SortDistance(_Ty*arrX, _Ty *arrY, unsigned int n, _Ty x0, _Ty y0)
	{
		/*先算点集到 x0,y0 的距离*/
		_Ty* dis = new _Ty[n];
		if (dis == nullptr) return -1;
		int i, j;
		_Ty dx, dy;
		for (i = 0; i < n; i++)
		{
			dx = arrX[i] - x0;
			dy = arrY[i] - y0;
			dis[i] = dx*dx + dy*dy;
		}
		//对距离进行排序
		/*这里直接用 选择排序法*/
		int smallIndex;
		int pass;
		_Ty temp;
		//passs range 0,n-2
		for (pass = 0; pass < n - 1; pass++)
		{
			//从 下标 pass开始扫描子表
			smallIndex = pass;
			// j遍历子表，从array[pass+1]到array[n-1]
			for (j = pass + 1; j < n; j++)

				if (dis[j] < dis[smallIndex])
					//如果找到更小元素，则将 smallIndex 赋值给该位置
					smallIndex = j;
			//将表中最小与array[pass]交换
			if (smallIndex != pass)
			{
				temp = dis[pass];
				dis[pass] = dis[smallIndex];
				dis[smallIndex] = temp;
				temp = arrX[pass];
				arrX[pass] = arrX[smallIndex];
				arrX[smallIndex] = temp;
				temp = arrY[pass];
				arrY[pass] = arrY[smallIndex];
				arrY[smallIndex] = temp;
			}

		}
		//释放内存
		delete[]dis;
		return 0;
	}
	//在点集中查找最短距离的点，返回他的下标
	template<class _Ty>
	int FindNearestPos(_Ty* arrx, _Ty*arry, unsigned int n, _Ty x0, _Ty y0)
	{
		/*先算点集到 x0,y0 的距离*/
		_Ty* dis = new _Ty[n];
		if (dis == nullptr) return -1;
		int i, minIndex;
		_Ty dx, dy;
		for (i = 0; i < n; i++)
		{
			dx = arrx[i] - x0;
			dy = arry[i] - y0;
			dis[i] = dx*dx + dy*dy;
		}
		minIndex = 0;
		//找到最小点集

		for (i = 1; i < n; i++) if (dis[minIndex] > dis[i]) minIndex = i; //如果发现有比最小距离小的，将它标记为最小距离


		return minIndex;
	}
}
#endif