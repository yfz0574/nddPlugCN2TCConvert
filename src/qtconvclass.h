#pragma once

#include <QWidget>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <math.h>
#include <qsciscintilla.h>
#include "scintillaeditor.h"
#include "openccTranse.h"
#include "ui_qtconvclass.h"
#include <QAction>
#include <QObject>


//using namespace std;
#ifndef QTCONVCLASS_H
#define QTCONVCLASS_H
#include <pluginGL.h>



using iter = std::vector<std::string>::const_iterator;
#if  defined   NDEBUG
#define   assert（condition）   （（void）   0） 
#else 
#define assert（condition） _assert（（condition）,  condition,  __FILE__,  __LINE__）

#endif

class QsciScintilla;
class QtConvClass : public QWidget
{
	Q_OBJECT

public:
	QtConvClass(QWidget *parent, QsciScintilla* pEdit, NDD_PROC_DATA s_procData);
	~QtConvClass();
	void getConvMenu(QMenu* menu);
	void setScintilla(const std::function<QsciScintilla* ()>& cb);
	//void showEvent(QShowEvent* event);
	std::function<QsciScintilla* ()> s_getCurEdit;

	
	std::string convertText(const std::string text);
	//void test();

private slots:
	void on_s2t();//简转繁体
	void on_t2s();//繁体转简体
	void on_close();
private:
	Ui::QtConvClass ui;
	ScintillaEditor* scint_editor_;
	std::string intext_;
	std::ostringstream oss_;
	QString oss2_;
	size_t maxS2tTextLen_;//测试后再定最大简繁转换文本长度。
	NDD_PROC_DATA* pProcData_;
	NDD_PROC_DATA s_procData;
	QWidget* s_pMainNotepad;
	
};
#endif // !QTCONVCLASS_H
