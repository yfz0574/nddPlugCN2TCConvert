#pragma once
#include "qtconvclass.h"
//#include "ch2tcexport.h"
#include <QMenuBar>
#include <QMessageBox>
#include <qscint/scintilla/include/Scintilla.h>
#include "util.hpp"
#include <QApplication>
#include <QTextStream>
#include <QDebug>
#include <iostream>
//#if defined(DEBUG)  || defined(_DEBUG) //MSVC defines _DEBUG
#define CMDOUTPUT
#if defined(CMDOUTPUT)
//#pragma comment( linker, "/subsystem:console /entry:WinMainCRTStartup")
#endif
QtConvClass::QtConvClass(QWidget *parent, QsciScintilla* pEdit, NDD_PROC_DATA s_procData)
	: QWidget(parent)
{
	//ui.setupUi(this);
	//m_pEdit = pEdit;
	scint_editor_ = nullptr;
	maxS2tTextLen_ = 1000'000;//测试后再定最大简繁转换文本长度。
	//getConvMenu(s_procData.m_rootMenu);
	

}

QtConvClass::~QtConvClass()
{
	// 关闭控制台窗口
	//FreeConsole();
}


void QtConvClass::setScintilla(const std::function<QsciScintilla* ()>& cb)
{
	if (scint_editor_)
	{
		delete scint_editor_;
		scint_editor_ = nullptr;
	}

	scint_editor_ = new ScintillaEditor(cb);

}
void QtConvClass::getConvMenu(QMenu* menu)
{
	//QMessageBox msgBox;
	//msgBox.setText(reinterpret_cast<const char*>(u8"进入了getConvMenu()#39！"));

	menu->addAction(reinterpret_cast<const char*>(u8"简体转繁体"),  [this] {
		on_s2t();
		},
		Qt::CTRL + Qt::Key_F11);
	menu->addAction(reinterpret_cast<const char*>(u8"繁体转简体"),  [this] {
		 
		on_t2s();
		},
		Qt::CTRL + Qt::Key_F12);
	//QAction* QMenu::addAction(const QString & text, Functor functor, const QKeySequence & shortcut = 0)

	//connect(submenuAction, &QAction::triggered, this, &MyClass::handleSubmenuAction);
	
#if 1==0
	// 创建控制台窗口
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);

	// 将标准输出和标准错误重定向到控制台窗口
	QTextStream out(stdout);
	QTextStream err(stderr);

	qInstallMessageHandler([](QtMsgType type, const QMessageLogContext& context, const QString& msg) {
		QByteArray localMsg = msg.toLocal8Bit();
		switch (type) {
		case QtDebugMsg:
			fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtInfoMsg:
			fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtWarningMsg:
			fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtCriticalMsg:
			fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtFatalMsg:
			fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			abort();
		}
		});
#endif
}
void QtConvClass::on_s2t() {
	
	//QMessageBox msgBox;
	//msgBox.setText(reinterpret_cast<const char*>(u8"进入了on_s2t()#100！"));
	//int ret = msgBox.exec();
	//qDebug() << reinterpret_cast<const char*>(u8"进入了on_s2t()#102");
	if(scint_editor_ ==nullptr)
	{
		QMessageBox::information (this,"critical:","m_pEdit is nullptr!");
	}
	intext_= scint_editor_->getchText();
	if (intext_.length() == 0)
	{
		return;
		//this->close();
	}
	//qDebug() << reinterpret_cast<const char*>(u8"进入了on_s2t()#");
	int codepage = scint_editor_->getCodePage();
	//qDebug() <<"intext="<<QString::fromStdString( intext_)<< ",codepage=" << codepage;
	if (codepage != SC_CP_UTF8)
	{
		QMessageBox msgBox;
		msgBox.setText(reinterpret_cast<const char*>(u8"暂未支持非UTF8编码的文件！"));
		//msgBox.setInformativeText("Do you want to save your changes?");
		//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		//this->close();
		return;
		
	}
	//msgBox.setText(reinterpret_cast<const char*>(u8"进入了on_s2t()#128！"));
	// ret = msgBox.exec();
	openccTranse transe;
	oss2_ = reinterpret_cast<const char*>(u8"");
	QString str = QCoreApplication::applicationDirPath();
	str += reinterpret_cast<const char*>(u8"/plugin/nddCN2TCConvert");///STCharacters.ocd2
	transe.configFileName_ = str.toStdString()+ reinterpret_cast<const char*>(u8"/s2t.json");
	//const std::string& text = reinterpret_cast<const char*>(u8"燕燕于飞差池其羽之子于归远送于野");
	
	try {
			opencc_t od = opencc_open(transe.configFileName_.c_str());
			char* converted = opencc_convert_utf8(od, intext_.c_str(), (size_t)-1);
			//oss2_ = converted;
			scint_editor_->replaceSelection(converted);
			opencc_convert_utf8_free(converted);
			//this->close();
			return;
		}
	catch (Exception& ex) {
		throw std::runtime_error(ex.what());
		//this->close();
		return;
	}
	
}
void QtConvClass::on_t2s() {

	//QString text = m_pEdit->selectedText();
	intext_ = scint_editor_->getchText();
	if(intext_.length()==0)
	{
		//this->close();
		return;
	}
	ConversionPtr convert;
	//TextDict dict();
	int codepage = scint_editor_->getCodePage();
	if (codepage != SC_CP_UTF8)
	{
		QMessageBox msgBox;
		msgBox.setText(reinterpret_cast<const char*>(u8"暂未支持非UTF8编码的文件！"));
		//msgBox.setInformativeText("Do you want to save your changes?");
		//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		//this->close();
		return;

	}

	openccTranse transe;
	//oss2_ = reinterpret_cast<const char*>(u8"");
	QString str = QCoreApplication::applicationDirPath();
	str += reinterpret_cast<const char*>(u8"/plugin/nddCN2TCConvert");
	transe.configFileName_ = str.toStdString() + reinterpret_cast<const char*>(u8"/t2s.json");
	try {
		
		//QMessageBox::information(NULL, "提示", "进入了on_t2s() .try");
		opencc_t od = opencc_open(transe.configFileName_.c_str());
		char* converted = opencc_convert_utf8(od, intext_.c_str(), (size_t)-1);
		if (converted == nullptr)
		{
			QMessageBox msgBox;
			
			QString  errstr;
			errstr = reinterpret_cast<const char*>(u8"转换失败！原因为：");
			errstr += opencc_error();
			msgBox.setText(errstr);
			//msgBox.setInformativeText("Do you want to save your changes?");
			//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
			//msgBox.setDefaultButton(QMessageBox::Save);
			int ret = msgBox.exec();
			//this->close();
			return;
		}
		oss2_ = converted;
		scint_editor_->replaceSelection(converted);
		opencc_convert_utf8_free(converted);
		
		//this->close();
		return;
	}
	catch (Exception& ex) {
		
		QMessageBox msgBox;
		QString  errstr;
		errstr = reinterpret_cast<const char*>(u8"转换失败！原因为：");
		//errstr += opencc_error();
		errstr += ex.what();
		msgBox.setText(errstr);
		//msgBox.setInformativeText("Do you want to save your changes?");
		//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		//this->close();
		return;
		//throw std::runtime_error(ex.what());
		//return;
	}

	//scint_editor_->replaceSelection(converted);
}

openccTranse::openccTranse(){

};
std::string QtConvClass::convertText(const std::string text) {


	std::string res = reinterpret_cast<const char*>(u8"");
	if (text.length() > maxS2tTextLen_)
	{
		res= reinterpret_cast < const char*>(u8"超过最大长度限制");
		return res;
	}
	openccTranse transe;
	res =transe.convertText(text);
	return res;






}


void QtConvClass::on_close()
{

	this->close();
	return;

}


std::string openccTranse::convertText(const std::string text)
{
	const std::string& converted = converter->Convert(text);
	return converted;
};

