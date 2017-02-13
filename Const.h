#pragma once
//Const.h
//常量定义入口
//
#ifndef CONST_H
#define CONST_H

//脚本状态
const int NormalNoRun = 0;
const int NormalRun = 1;
const int SwitchRun = 2;
const int ThreadSuspend = 3;
const int ShouldWaitForArmy = -1;
const int ShouldRestart = -2;
const int ShouldSwitch = -3;
//攻击参数
const int MAXARRYLENGTH = 240;
const int MAXATTACKCOUNT = 60;
//军队编号
const int BARBARIN = 1;
const int ARCHER = 2;
const int GIANT = 3;
const int GOBLIN = 4;
const int WALLBREAKER = 5;
const int WIZARD = 6;
const int BALLON = 7;
const int HHEALER = 8;
const int DRAGON = 9;
const int PEKA = 10;
const int BABYDRAGON = 11;
const int MINIOR = 12;
const int MINION = 13;
const int HOGRIDER = 14;
const int VALKYRIE = 15;
const int GOLEM = 16;
const int WITCH = 17;
const int LAVAHOUND = 18;
const int BOWLER = 19;
//咒语编号
const int LIGHTINGSPELL = 1;
const int HEALINGSPELL = 2;
const int RAGESPELL = 3;
const int JUMPSPELL = 4;
const int FREEZESPELL = 5;
const int CLONESPELL = 6;
const int POISON = 7;
const int EARTHQUAKESPELL = 8;
const int HASTESPELL = 9;
const int SKELETONSPELL = 10;
//服务器IP
const LPCTSTR IPADRESS = "112.74.36.23";
//交流
const LPCTSTR QQGROUPNAME = "584618461";
//脚本版本
const LPCTSTR cocBotVer = "5.170213";
//军队名称
const LPCTSTR ARMYNAME[30] =
{
	"NULL",
	"barbarin",
	"archer",
	"giant",
	"goblin",
	"wallbreaker",
	"wizard",
	"ballon",
	"healer",
	"dragon",
	"peka",
	"baby dragon",
	"minor",
	"minion",
	"hog rider",
	"valkyrie",
	"golem",
	"witch",
	"lavahound",
	"bower",
	"lighting spell"
};
//常用颜色
const COLORREF REDCOLOR = RGB(0XFF, 0X00, 0X00);
const COLORREF GREENCOLOR = RGB(0X00, 0XFF, 0X00);
const COLORREF BLUECOLOR = RGB(0X00, 0X00, 0XFF);
const COLORREF BLACKCOLOR = RGB(0X00, 0X00, 0X00);
//其它
const int MAXFINDPICTIME = 9999;






#endif