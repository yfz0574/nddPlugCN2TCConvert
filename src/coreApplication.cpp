#include "coreApplication.h"


  bool MyCoreApplication::event(QEvent* event) 
  {
        if (event->type() == QEvent::ApplicationActivate) {
            qDebug() << "Application activated!";
        }
        return QCoreApplication::event(event);
    }


