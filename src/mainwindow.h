#ifndef mainwindow_h__
#define mainwindow_h__

// Qt includes
#include <QtGui/QMainWindow>



// forward declares
namespace Ui
{
  class MainWindow;
}

class ParticleGLWidget;
class SettingsDock;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

public slots:

private:
  Ui::MainWindow* _ui;
  SettingsDock* _settingsdock;
  ParticleGLWidget* _glwidget;
};
#endif // mainwindow_h__
