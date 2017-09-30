#pragma once
//Const.h
//常量定义入口
//
#ifndef CONST_H
#define CONST_H

//脚本状态
enum SCRIPT_STATE { NOTSTART, START, INRUN, PAUSE, STOP };//脚本控制枚举
#define SCRIPT_STATE_NOT_RUN   0
#define SCRIPT_STATE_IN_RUN       1
#define SCRIPT_STATE_SUSPEND    2 //暂停线程
#define SCRIPT_STATE_RESUM        3     //  恢复线程
#define ShouldWaitForArmy           -1
#define ShouldRestart                     -2
#define ShouldSwitch                      -3
/********************************* 攻击参数 ******************************************/
#define MAX_ARMY_COUNT  240
#define MAXATTACKCOUNT  60
/*攻击 椭圆 坐标*/
const long ATTACK_CIRCLE_X[]=
{
	623, 622, 622, 622, 621, 621, 620, 619, 618, 617,
	616, 615, 613, 611, 610, 608, 606, 604, 601, 599,
	596, 594, 591, 588, 585, 582, 579, 576, 573, 569,
	566, 562, 558, 554, 551, 547, 542, 538, 534, 530,
	525, 521, 517, 512, 507, 503, 498, 493, 488, 484,
	479, 474, 469, 464, 459, 454, 449, 444, 439, 434,
	429, 423, 418, 413, 408, 403, 398, 393, 388, 383,
	378, 374, 369, 364, 359, 355, 350, 345, 341, 336,
	332, 328, 323, 319, 315, 311, 307, 303, 299, 296,
	292, 288, 285, 282, 279, 275, 272, 270, 267, 264,
	262, 259, 257, 255, 253, 251, 249, 247, 245, 244,
	243, 241, 240, 239, 239, 238, 237, 237, 237, 237,
	237, 237, 237, 237, 238, 238, 239, 240, 241, 242,
	244, 245, 247, 248, 250, 252, 254, 256, 259, 261,
	263, 266, 269, 272, 275, 278, 281, 284, 288, 291,
	295, 298, 302, 306, 310, 314, 318, 322, 327, 331,
	335, 340, 344, 349, 353, 358, 363, 368, 372, 377,
	382, 387, 392, 397, 402, 407, 412, 417, 422, 427,
	432, 437, 443, 448, 453, 458, 463, 468, 473, 478,
	482, 487, 492, 497, 502, 506, 511, 515, 520, 524,
	529, 533, 537, 541, 546, 550, 554, 557, 561, 565,
	568, 572, 575, 578, 582, 585, 588, 591, 593, 596,
	598, 601, 603, 605, 607, 609, 611, 613, 614, 616,
	617, 618, 619, 620, 621, 621, 622, 622, 622, 622
};
const long ATTACK_CIRCLE_Y[] =
{
	295, 298, 301, 305, 308, 312, 315, 319, 322, 326,
	329, 332, 336, 339, 342, 346, 349, 352, 355, 358,
	361, 364, 367, 370, 373, 376, 378, 381, 384, 386,
	389, 391, 394, 396, 398, 400, 402, 404, 406, 408,
	410, 412, 413, 415, 416, 418, 419, 420, 421, 422,
	423, 424, 425, 425, 426, 426, 427, 427, 427, 427,
	427, 427, 427, 427, 427, 426, 426, 425, 424, 424,
	423, 422, 421, 420, 418, 417, 416, 414, 413, 411,
	409, 407, 406, 404, 402, 399, 397, 395, 393, 390,
	388, 385, 383, 380, 377, 375, 372, 369, 366, 363,
	360, 357, 354, 351, 348, 344, 341, 338, 334, 331,
	328, 324, 321, 318, 314, 311, 307, 304, 300, 297,
	293, 290, 286, 283, 279, 276, 272, 269, 265, 262,
	259, 255, 252, 249, 245, 242, 239, 236, 233, 230,
	227, 224, 221, 218, 215, 212, 210, 207, 204, 202,
	199, 197, 195, 192, 190, 188, 186, 184, 182, 180,
	178, 177, 175, 174, 172, 171, 170, 169, 167, 166,
	166, 165, 164, 163, 163, 162, 162, 162, 162, 162,
	162, 162, 162, 162, 162, 163, 163, 164, 165, 166,
	167, 168, 169, 170, 171, 172, 174, 175, 177, 179,
	180, 182, 184, 186, 188, 190, 193, 195, 197, 200,
	202, 205, 207, 210, 213, 215, 218, 221, 224, 227,
	230, 233, 236, 239, 243, 246, 249, 252, 256, 259,
	263, 266, 269, 273, 276, 280, 283, 287, 290, 294
};
//Heros

const LPCTSTR GRAND_WARDEN_COLOR1 = "ffc49e-030f0f";
const LPCTSTR GRAND_WARDEN_COLOR2 = "9|1|ffd8b0-030f0f,-4|7|9e44b0-050f0f,16|9|a048b8-050f0f";
//DONATE
const LPCTSTR EXTR_NEED_COLOR1 = "95c800-0F0F0F";
const LPCTSTR EXTR_NEED_COLOR2 = "4|0|ffffff-050505,10|0|96c800-0F0F0F,1|3|88c002-0F0F0F,4|4|ffffff-050505";
//军队编号
#define BARBARIN  1
#define ARCHER  2
#define GIANT  3
#define GOBLIN  4
#define WALLBREAKER  5
#define WIZARD  6
#define BALLON  7
#define HHEALER  8
#define DRAGON  9
#define PEKA  10
#define BABYDRAGON  11
#define MINIOR  12
#define MINION  13
#define HOGRIDER  14
#define VALKYRIE  15
#define GOLEM  16
#define WITCH  17
#define LAVAHOUND  18
#define BOWLER  19
//咒语编号
#define LIGHTINGSPELL  1
#define HEALINGSPELL  2
#define RAGESPELL  3
#define JUMPSPELL  4
#define FREEZESPELL  5
#define CLONESPELL  6
#define POISON  7
#define EARTHQUAKESPELL  8
#define HASTESPELL  9
#define SKELETONSPELL  10
//模拟器相关
//BlueStacks App Player
#define APP_PLAYER_BLUESTACKS    0
//雷电模拟器
#define  APP_PLAYER_LIGHTING      1
//夜神模拟器
//#define   APP_PLAYER_NIGHT             2
//服务器IP
const LPCTSTR IPADRESS =					"112.74.36.23";
//交流
const LPCTSTR QQGROUPNAME =					"584618461";
//脚本版本
const LPCTSTR cocBotVer =					"6.170924";
//插件版本
#define DM_VER_5							"5.1423"
#define DM_VER_6							"6.1538"
//军队名称
const LPCTSTR ARMYNAME[]
{
	"野蛮人",
	"弓箭手",
	"巨人",
	"哥布林",
	"炸弹人",
	"气球",
	"法师",
	"天使",
	"飞龙",
	"皮卡",
	"飞龙宝宝",
	"矿工",
	"亡灵",
	"野猪骑士",
	"武神",
	"石头人",
	"女巫",
	"熔岩猎犬",
	"巨石投手",
	"随意",
	"救命"
};
//常用颜色
const COLORREF REDCOLOR =					RGB(0XFF, 0X00, 0X00);
const COLORREF GREENCOLOR =					RGB(0X00, 0XFF, 0X00);
const COLORREF BLUECOLOR =					RGB(0X00, 0X00, 0XFF);
const COLORREF BLACKCOLOR =					RGB(0X00, 0X00, 0X00);
//自定义界面消息
#define WM_PAGE1_QUICK_SET					WM_USER+0X101			//快速设
#define WM_LOAD_IN_CONFIG					WM_USER+0X102
#define WM_LOAD_OUT_CONFIG					WM_USER+0X103
#define WM_PAGE_1_TEST_MESSAGE				WM_USER+0X104
#define WM_PAGE_7_BINDSET_CLICK				WM_USER+0X105
#define WM_BINDSET_SAVE_CONFIG				WM_USER+0X106
#define WM_SELECT_APP_PLAYER				WM_USER+0X107			//选择模拟器消息
#define WM_SHOW_GRAHIC						WM_USER+0X108
//自定义线程消息
//1.刷新模拟器信息
#define TH_UPDATA_APP_PLAYER_INFO           WM_USER+0X1070
//2.向主界面发送资源统计信息
#define TH_STASTICS                         WM_USER+0X1080
//3.向主界面发送日志信息
#define TH_SETLOG                           WM_USER+0X1090
//4.向主界面发送 获取某个模拟器句柄
#define  TH_GET_APP_PLAYER_HWND				WM_USER+0X10A0

//其它

//最大多开数
#define MAX_THREAD_COUNT					10
//最长时间
#define MAX_FIND_PIC_TIME                   9999
//最大切换数量（包括第零个）
#define  MAX_SWITCH_COUNT					3
//显示图片区域
#define  SCREENSHOWWIDTH					462
#define SCREENSHOWHEIGHT					340
//字库编号
#define DICT_COC_ARMY						0
#define DICT_COC_FISH						1
#define DICT_COC_RESOURCE					2
#define DICT_COC_TROOPTH					3
#define DICT_COC_DONATE						5
#define DICT_COC_ATTACKARMY					6


//账号密码
#define DEFAULT_ACCOUNT						"cocBot"
#define DEFAULT_PASSWORD					"123456"




#endif