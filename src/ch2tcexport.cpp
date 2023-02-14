#pragma once
//#include "ch2tcexport.h"
#include "qtconvclass.h"
#define NDD_EXPORTDLL
#include "util.hpp"
#include "coreApplication.h"
#include <QMessageBox>
#if defined(Q_OS_WIN)
#if defined(NDD_EXPORTDLL)
#define NDD_EXPORT __declspec(dllexport)
#else
#define NDD_EXPORT __declspec(dllimport)
#endif
#else
#define NDD_EXPORT __attribute__((visibility("default")))
#endif


#define NDD_EXPORTDLL

#if defined(Q_OS_WIN)
#if defined(NDD_EXPORTDLL)
#define NDD_EXPORT __declspec(dllexport)
#else
#define NDD_EXPORT __declspec(dllimport)
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

	NDD_EXPORT bool NDD_PROC_IDENTIFY(NDD_PROC_DATA* pProcData);
	NDD_EXPORT int NDD_PROC_MAIN(QWidget* pNotepad, const QString& strFileName, std::function<QsciScintilla* ()>getCurEdit, NDD_PROC_DATA* procData);


#ifdef __cplusplus
}
#endif

static NDD_PROC_DATA s_procData;
static QWidget* s_pMainNotepad = nullptr;
std::function<QsciScintilla* ()> s_getCurEdit;

//const rcast<char> str = rcast<char>(u8"简繁体转换");

bool NDD_PROC_IDENTIFY(NDD_PROC_DATA* pProcData)
{
	if (pProcData == NULL)
	{
		return false;
	}
	pProcData->m_strPlugName = reinterpret_cast<const char*>(u8"简繁体转换");
	pProcData->m_strComment = reinterpret_cast<const char*>(u8"简繁体转换插件，可自定义词库.");

	pProcData->m_version = QString("v1.0");
	pProcData->m_auther = QString("yfz0574");
	pProcData->m_menuType = 1;
		return true;
}

//插件的入口点函数
int NDD_PROC_MAIN(QWidget* pNotepad, const QString& strFileName, std::function<QsciScintilla* ()>getCurEdit, NDD_PROC_DATA* pProcData)
{
	//对于需要创建二级菜单的例子，pProcData不能为nullptr。s_procData.m_rootMenu是根菜单节点，由主程序进行创建。用户自定义的菜单，都在该根菜单之下自行新增。
		//该NDD_PROC_MAIN函数只会调用一次。所以在唯一调用之下，务必要把参数中的值保存一份。否则后续再也没有机会执行该函数。
		//务必拷贝一份 pProcData，函数返回后，在外面会释放。
	int argc = 0;
	char** argv = nullptr;
	//new MyCoreApplication(argc, argv);
	//NDD_PROC_DATA s_procData;
	//std::function<QsciScintilla* ()> s_getCurEdit;
	QsciScintilla* pEdit = getCurEdit();
	if (pProcData != nullptr)
	{
		s_procData = *pProcData;
	}
	else
	{
		return -1;
	}

	QWidget* s_pMainNotepad;
	s_pMainNotepad = pNotepad;
	s_getCurEdit = getCurEdit;
	//上面 pProcData、pMainNotepad、s_getCurEdit 三个值，务必要保存起来。因为后面不会再有机会执行该函数。如果后续业务功能中需要这些值，只能通过操作保存的副本进行。
		// 如 果 pProcData->m_menuType = 1; 是 自 己 要 创 建 二 级 菜 单 的 场 景 。 则 通 过s_procData.m_rootMenu 获取该插件的菜单根节点。
		//插件开发者自行在 s_procData.m_rootMenu 下添加新的二级菜单项目

	//TODO: 子菜单关联上on_s2t()和on_t2s().
	
	//后续就是自行绑定 pAction 的执行槽函数。后面通过点击菜单上面的按钮，进行槽函数的
	//触发调用。
	//nddJsonPlugin = new NDDJsonPlugin(s_pMainNotepad, strFileName, nullptr, s_pMainNotepad);
	QtConvClass* nddConvPlugin = new QtConvClass(pNotepad, nullptr, s_procData);
	//connect
	nddConvPlugin->getConvMenu(s_procData.m_rootMenu);
	nddConvPlugin->setScintilla(s_getCurEdit);
	//nddConvPlugin->getJsonViewMenu(s_procData.m_rootMenu);


	return 0;
}

