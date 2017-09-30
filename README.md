
====模块功能========类名============文件名
1.程序入口			CcocBotApp		cocBot.h，cocBot.cpp
2.UI				CcocBotDlg		cocBot.h,cocBot.cpp
3.UI				page1			page1.h,page1.cpp
4.UI				page2			page2.h,page2.cpp
5.UI				page3			page3.h,page3.cpp
6.UI				page4			page4.h,page4.cpp
7.UI				page5			page5.h,page5.cpp
8.UI				page6			page6.h,page6.cpp
9.UI				page7			page7.h,page7.cpp
10.UI				page8			page8.h,page8.cpp
11.UI				page9			page9.h,page9.cpp
12.UI				page10			page10.h,page10.cpp
全局变量			NULL			global.h,global.cpp,const.h
脚本模块			CbotFunction	botFunction.h,botFunction.cpp
脚本模块			CScript			Script.h,Script.cpp
lua 模块			NULL			lua_func.h,lua_func.cpp
Kernal-pipe			CPipeShell		pipeshell.h,pipeshell.cpp
Kernal-imageloc		Cdmsoft			Cdmsoft.h,botLib.h
Kernal-other		NULL			botHelp.h,botHelp.cpp
		
================================================================================
MICROSOFT 基础类库: newcocbot 项目概述
===============================================================================

应用程序向导已为您创建了这个 newcocbot 应用程序。此应用程序不仅演示 Microsoft 基础类的基本使用方法，还可作为您编写应用程序的起点。

本文件概要介绍组成 newcocbot 应用程序的每个文件的内容。

newcocbot.vcxproj
这是使用应用程序向导生成的 VC++ 项目的主项目文件。 
它包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

newcocbot.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。
    它包含有关项目文件与筛选器之间的关联信息。在 IDE 中，通过这种关联，在特定节点下以分组形式显示具有相似扩展名的文件。例如，“.cpp”文件与“源文件”筛选器关联。

newcocbot.h
这是应用程序的主要头文件。它包括其他项目特定的头文件(包括 Resource.h)，并声明 CnewcocbotApp 应用程序类。

newcocbot.cpp
这是包含应用程序类 CnewcocbotApp 的主要应用程序源文件。

newcocbot.rc
这是程序使用的所有 Microsoft Windows 资源的列表。它包括 RES 子目录中存储的图标、位图和光标。此文件可以直接在 Microsoft Visual C++ 中进行编辑。项目资源位于 2052 中。

res\newcocbot.ico
这是用作应用程序图标的图标文件。此图标包括在主要资源文件 newcocbot.rc 中。

res\newcocbot.rc2
此文件包含不在 Microsoft Visual C++ 中进行编辑的资源。您应该将不可由资源编辑器编辑的所有资源放在此文件中。


/////////////////////////////////////////////////////////////////////////////

应用程序向导创建一个对话框类:

newcocbotDlg.h，newcocbotDlg.cpp - 对话框
这些文件包含 CnewcocbotDlg 类。该类定义应用程序主对话框的行为。该对话框的模板位于 newcocbot.rc 中，该文件可以在 Microsoft Visual C++ 中进行编辑。

/////////////////////////////////////////////////////////////////////////////

帮助支持:

hlp\newcocbot.hhp
此文件是帮助项目文件。它包含将帮助文件编译为 .chm 文件所需的数据。

hlp\newcocbot.hhc
此文件列出帮助项目的内容。

hlp\newcocbot.hhk
此文件包含帮助主题的索引。

hlp\afxcore.htm
此文件包含标准 MFC 命令和屏幕对象的标准帮助主题。将您自己的帮助主题添加到此文件中。

makehtmlhelp.bat
此文件由生成系统用来编译帮助文件。

hlp\Images\*.gif
这些是 Microsoft 基础类库标准命令的标准帮助文件主题所需的位图文件。


/////////////////////////////////////////////////////////////////////////////

其他功能:

ActiveX 控件
应用程序包括对使用 ActiveX 控件的支持。

Windows Sockets
应用程序支持通过 TCP/IP 网络建立通信。

/////////////////////////////////////////////////////////////////////////////

其他标准文件:

StdAfx.h，StdAfx.cpp
这些文件用于生成名为 newcocbot.pch 的预编译头 (PCH) 文件和名为 StdAfx.obj 的预编译类型文件。

Resource.h
这是标准头文件，它定义新的资源 ID。
Microsoft Visual C++ 读取并更新此文件。

newcocbot.manifest
	应用程序清单文件供 Windows XP 用来描述应用程序
	对特定版本并行程序集的依赖性。加载程序使用此
	信息从程序集缓存加载适当的程序集或
	从应用程序加载私有信息。应用程序清单可能为了重新分发而作为
	与应用程序可执行文件安装在相同文件夹中的外部 .manifest 文件包括，
	也可能以资源的形式包括在该可执行文件中。 
/////////////////////////////////////////////////////////////////////////////

其他注释:

应用程序向导使用“TODO:”指示应添加或自定义的源代码部分。

如果应用程序在共享的 DLL 中使用 MFC，则需要重新发布这些 MFC DLL；如果应用程序所用的语言与操作系统的当前区域设置不同，则还需要重新发布对应的本地化资源 MFC100XXX.DLL。有关这两个主题的更多信息，请参见 MSDN 文档中有关 Redistributing Visual C++ applications (重新发布 Visual C++ 应用程序)的章节。

/////////////////////////////////////////////////////////////////////////////
