#pragma once

#include <QWidget>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <math.h>
#include <qsciscintilla.h>
#include "openccTranse.h"
#include "ui_qtconvclass.h"

//using namespace std;

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
	QtConvClass(QWidget *parent, QsciScintilla* pEdit);
	~QtConvClass();

	void showEvent(QShowEvent* event);


	
	std::string convertText(const std::string text);
	//void test();

private slots:
	void on_s2t();//简转繁体
	void on_t2s();//繁体转简体
	void on_close();
private:
	Ui::QtConvClass ui;
	QsciScintilla* m_pEdit;
	QString intext_;
	std::ostringstream oss_;
	QString oss2_;
	const size_t maxS2tTextLen_ = 1000'000;//测试后再定最大简繁转换文本长度。
};
