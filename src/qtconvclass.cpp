#pragma once
#include "qtconvclass.h"
//#include <qsciscintilla.h>
#include <QMessageBox>
#include <qscint/scintilla/include/Scintilla.h>

QtConvClass::QtConvClass(QWidget *parent, QsciScintilla* pEdit)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_pEdit = pEdit;
}

QtConvClass::~QtConvClass()
{}
void QtConvClass::showEvent(QShowEvent* event)
{
	//qDebug() << "窗口显示啦~";
	intext_= m_pEdit->selectedText();
	
}


void QtConvClass::on_s2t() {

	//intext_= m_pEdit->selectedText();
	if (intext_.isEmpty())
	{
		return;
		this->close();
	}
	int codepage = static_cast<int>(m_pEdit->SendScintilla(SCI_GETCODEPAGE,0ul,nullptr ));
	if (codepage != SC_CP_UTF8)
	{
		QMessageBox msgBox;
		msgBox.setText("暂未支持非UTF8编码的文件！");
		//msgBox.setInformativeText("Do you want to save your changes?");
		//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		this->close();
		return;
		
	}

	openccTranse transe;
	oss2_ = reinterpret_cast<const char*>(u8"");
	QString str = QCoreApplication::applicationDirPath();
	str += "/plugin/nddToys";///STCharacters.ocd2
	transe.configFileName_ = str.toStdString()+"/s2t.json";
	//const std::string& text = reinterpret_cast<const char*>(u8"燕燕于飞差池其羽之子于归远送于野");
	
	try {
			opencc_t od = opencc_open(transe.configFileName_.c_str());
			char* converted = opencc_convert_utf8(od, intext_.toStdString().c_str(), (size_t)-1);
			oss2_ = converted;
			opencc_convert_utf8_free(converted);
			m_pEdit->replaceSelectedText(oss2_);
			this->close();
			return;
		}
	catch (Exception& ex) {
		throw std::runtime_error(ex.what());
		this->close();
		return;
	}
	
}
void QtConvClass::on_t2s() {

	//QString text = m_pEdit->selectedText();
	//intext_ = m_pEdit->selectedText();
	if(intext_.isEmpty())
	{
		this->close();
		return;
	}
	ConversionPtr convert;
	//TextDict dict();
	int codepage = static_cast<int>(m_pEdit->SendScintilla(SCI_GETCODEPAGE, 0ul, nullptr));
	if (codepage != SC_CP_UTF8)
	{
		QMessageBox msgBox;
		msgBox.setText(reinterpret_cast<const char*>("暂未支持非UTF8编码的文件！"));
		//msgBox.setInformativeText("Do you want to save your changes?");
		//msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		this->close();
		return;

	}

	openccTranse transe;
	oss2_ = reinterpret_cast<const char*>(u8"");
	QString str = QCoreApplication::applicationDirPath();
	str += "/plugin/nddCN2TCConvert";
	transe.configFileName_ = str.toStdString() + "/t2s.json";
	try {
		
		//QMessageBox::information(NULL, "提示", "进入了on_t2s() .try");
		opencc_t od = opencc_open(transe.configFileName_.c_str());
		char* converted = opencc_convert_utf8(od, intext_.toStdString().c_str(), (size_t)-1);
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
			this->close();
			return;
		}
		oss2_ = converted;
		opencc_convert_utf8_free(converted);
		m_pEdit->replaceSelectedText(oss2_);
		this->close();
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
		this->close();
		return;
		//throw std::runtime_error(ex.what());
		//return;
	}





	//convert_amount(0);
	//QString outtext;
	//outtext.fromStdString( oss_.str());
	//QMessageBox::information(nullptr, "", oss2_);
	//m_pEdit->setSelection()
	//m_pEdit->replaceSelectedText(QString("testamount"));
	m_pEdit->replaceSelectedText(oss2_);
}

openccTranse::openccTranse(){

};
std::string QtConvClass::convertText(const std::string text) {


	std::string res =(const char*) u8"";
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

