#pragma once
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include <QtGui/QGuiApplication>
#include <QtWidgets/QPushButton>
#include <windows.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

class MyCoreApplication : public QCoreApplication {
public:
    MyCoreApplication(int& argc, char** argv) : QCoreApplication(argc, argv) {}

protected:
    bool event(QEvent* event)override;
};
