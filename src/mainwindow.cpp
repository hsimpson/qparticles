// Qt includes
#include <QMessageBox>

// local includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "glwidget.h"



MainWindow::MainWindow(QWidget *parent /* = 0 */)
: QMainWindow(parent),
  _ui(new Ui::MainWindow),
  _settingsdock(0),
  _glwidget(0)
{
  _ui->setupUi(this);  
  // create the settings dock
  _settingsdock = new SettingsDock(this);
  
  addDockWidget(Qt::RightDockWidgetArea, _settingsdock);

  
  QGLFormat fmt;
  fmt.setVersion(4,1);
  //fmt.setProfile(QGLFormat::CoreProfile);//DOESN'T WORK WITH CORE PROFILE(NOTHING ON SCREEN)
  fmt.setProfile(QGLFormat::CompatibilityProfile);
  // turn on multisampling
  //fmt.setSampleBuffers(true);
  //QGLFormat::setDefaultFormat(defFormat);

  // create the glwidget
  _glwidget = new ParticleGLWidget(fmt, this);
  setCentralWidget(_glwidget);

  connect(_settingsdock, SIGNAL(settingsChanged(const QHash<SettingsDock::Property, QVariant>&)),
    _glwidget, SLOT(setProperties(const QHash<SettingsDock::Property, QVariant>&)));

  // setting initial variables
  _glwidget->setProperties(_settingsdock->getDefaultProperties());
}


MainWindow::~MainWindow()
{

}
