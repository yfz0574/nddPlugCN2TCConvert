/********************************************************************************
** Form generated from reading UI file 'qtconvclass.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCONVCLASS_H
#define UI_QTCONVCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtConvClass
{
public:
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *t2sBt;
    QPushButton *s2tBt;
    QPushButton *closeBtn;
    QLabel *label_2;

    void setupUi(QWidget *QtConvClass)
    {
        if (QtConvClass->objectName().isEmpty())
            QtConvClass->setObjectName(QString::fromUtf8("QtConvClass"));
        QtConvClass->resize(475, 365);
        label = new QLabel(QtConvClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(9, 9, 421, 41));
        gridLayoutWidget = new QWidget(QtConvClass);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 70, 390, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        t2sBt = new QPushButton(gridLayoutWidget);
        t2sBt->setObjectName(QString::fromUtf8("t2sBt"));

        gridLayout->addWidget(t2sBt, 0, 1, 1, 1);

        s2tBt = new QPushButton(gridLayoutWidget);
        s2tBt->setObjectName(QString::fromUtf8("s2tBt"));

        gridLayout->addWidget(s2tBt, 0, 0, 1, 1);

        closeBtn = new QPushButton(gridLayoutWidget);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));

        gridLayout->addWidget(closeBtn, 0, 2, 1, 1);

        label_2 = new QLabel(QtConvClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 310, 131, 16));

        retranslateUi(QtConvClass);
        QObject::connect(s2tBt, SIGNAL(clicked()), QtConvClass, SLOT(on_s2t()));
        QObject::connect(t2sBt, SIGNAL(clicked()), QtConvClass, SLOT(on_t2s()));
        QObject::connect(closeBtn, SIGNAL(clicked()), QtConvClass, SLOT(on_close()));

        QMetaObject::connectSlotsByName(QtConvClass);
    } // setupUi

    void retranslateUi(QWidget *QtConvClass)
    {
        QtConvClass->setWindowTitle(QCoreApplication::translate("QtConvClass", "QtConvClass", nullptr));
        label->setText(QCoreApplication::translate("QtConvClass", "notepad-- \347\256\200\344\275\223\347\271\201\344\275\223\350\275\254\346\215\242\346\217\222\344\273\266", nullptr));
        t2sBt->setText(QCoreApplication::translate("QtConvClass", "\347\271\201\344\275\223\350\275\254\347\256\200\344\275\223", nullptr));
        s2tBt->setText(QCoreApplication::translate("QtConvClass", "\347\256\200\344\275\223\350\275\254\347\271\201\344\275\223", nullptr));
        closeBtn->setText(QCoreApplication::translate("QtConvClass", "\345\205\263\351\227\255", nullptr));
        label_2->setText(QCoreApplication::translate("QtConvClass", "\347\233\256\345\211\215\344\273\205\346\224\257\346\214\201UTF-8\347\274\226\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtConvClass: public Ui_QtConvClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCONVCLASS_H
