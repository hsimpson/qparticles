#ifndef settings_h__
#define settings_h__

// Qt includes
#include <QtGui/QDockWidget>
#include <QtCore/QHash>
#include <QtCore/QVariant>

// forward declares
namespace Ui
{
  class Settings;
}


class SettingsDock : public QDockWidget
{
  Q_OBJECT;
public:
  enum Property
  {
    ParticleCount,
    Gravity,
    ParticleSize,
    ParticleOpacity,
    Force
  };
  SettingsDock(QWidget* parent=0);
  ~SettingsDock();

  const QHash<SettingsDock::Property, QVariant>& getDefaultProperties();

public slots:
  void on_ParticleSlider_valueChanged ( int value );
  void on_GravitySlider_valueChanged ( int value );
  void on_ParticleSizeSlider_valueChanged ( int value );
  void on_ParticleOpacitySlider_valueChanged ( int value );
  void on_ForceSlider_valueChanged (int value );

  void on_btnReset_clicked (bool checked);
  

signals:
  void settingsChanged(const QHash<SettingsDock::Property, QVariant>& properties);
    
private:
  void setValuesIntoControls(const QHash<SettingsDock::Property, QVariant>& properties);
  Ui::Settings* _ui;
  QHash<SettingsDock::Property, QVariant> _properties; // this are our current properties
  QHash<SettingsDock::Property, QVariant> _defaultproperties; // this are a copy which holds the default properties
};
#endif // settings_h__
