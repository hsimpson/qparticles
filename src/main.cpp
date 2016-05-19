/*
*
* qParticles is a demo for OpenCL Particles inspired by the CUDA implementation from
* Craig Mouser, (http://www.craigmouser.com)
* Written by Daniel Toplak
*
* Features:
* - Qt GUI with controls for particle count force, etc.
* - Particles are calculated in a 3d space
* - Bounding box to hold the particles in the 3d space
*
*/
// Qt includes
#include <QtGui/QApplication>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>

// local includes
#include "mainwindow.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  // translation stuff
  QString locale = QLocale::system().name();
  QTranslator translator;
  
  if(translator.load(":/translations/qparticles_" + locale))
    app.installTranslator(&translator);


  MainWindow mw;
  mw.showMaximized();
  return app.exec();
}