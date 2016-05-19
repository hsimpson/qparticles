
// local includes
#include "settings.h"
#include "ui_settings.h"

SettingsDock::SettingsDock( QWidget* parent/*=0*/ )
  :QDockWidget(parent),
  _ui(new Ui::Settings)
{
  _ui->setupUi(this);

  // setting the default values
  _properties[SettingsDock::ParticleCount] = 1000000U;
  _properties[SettingsDock::Gravity] = /*0.0f*/ 0.98f;
  _properties[SettingsDock::ParticleSize] = 1.0f;
  _properties[SettingsDock::ParticleOpacity] = 0.5f;
  _properties[SettingsDock::Force] = 0.1f;

  // hold the defaults
  _defaultproperties = _properties;

  // set default values into controls
  setValuesIntoControls(_properties);
}

SettingsDock::~SettingsDock()
{

}

void SettingsDock::on_ParticleSlider_valueChanged( int value )
{
  QString suffix;
  double display_value = (double)value;
  
  if(display_value >= 1e6)
  {
    display_value /= 1e6;
    suffix = "M";
  }
  else
  {
    display_value /= 1e3;
    suffix = "k";
  }
  QString display = QString("%1 %2").arg(display_value, 0, 'f', 2).arg(suffix);
  _ui->ParticleEdit->setText(display);
  // set back to properties hash
  _properties[SettingsDock::ParticleCount] = (unsigned int)value;
  emit settingsChanged(_properties);
}

void SettingsDock::on_GravitySlider_valueChanged( int value )
{
  float display_value = (float)value/1e3;
  _ui->GravityEdit->setText(QString("%1").arg(display_value, 0, 'f', 2));
  // set back to properties hash
  _properties[SettingsDock::Gravity] = display_value;
  emit settingsChanged(_properties);
}


void SettingsDock::on_ParticleSizeSlider_valueChanged( int value )
{
  float display_value = (float)value/10;
  _ui->ParticleSizeEdit->setText(QString("%1").arg(display_value, 0, 'f', 2));
  _properties[SettingsDock::ParticleSize] = (float)display_value;
  emit settingsChanged(_properties);
}

void SettingsDock::on_ParticleOpacitySlider_valueChanged( int value )
{
  float display_value = (float)value/100;
  _ui->ParticleOpacityEdit->setText(QString("%1").arg(display_value, 0, 'f', 2));
  _properties[SettingsDock::ParticleOpacity] = (float)display_value;
  emit settingsChanged(_properties);
}

void SettingsDock::on_ForceSlider_valueChanged( int value )
{
  float display_value = (float)value/100;
  _ui->ForceEdit->setText(QString("%1").arg(display_value, 0, 'f', 2));
  _properties[SettingsDock::Force] = (float)display_value;
  emit settingsChanged(_properties);
}

void SettingsDock::on_btnReset_clicked( bool checked )
{
  Q_UNUSED(checked);
  _properties = _defaultproperties;
  setValuesIntoControls(_properties);
}

void SettingsDock::setValuesIntoControls( const QHash<Property, QVariant>& properties )
{
  _ui->ParticleSlider->setValue        (properties[SettingsDock::ParticleCount]   .value<unsigned int>());
  _ui->GravitySlider->setValue         (properties[SettingsDock::Gravity]         .value<float>()*1000);
  _ui->ParticleSizeSlider->setValue    (properties[SettingsDock::ParticleSize]    .value<float>()*10);
  _ui->ParticleOpacitySlider->setValue (properties[SettingsDock::ParticleOpacity] .value<float>()*100);
  _ui->ForceSlider->setValue      (properties[SettingsDock::Force]      .value<float>()*100);
}

const QHash<SettingsDock::Property, QVariant>& SettingsDock::getDefaultProperties()
{
  return _defaultproperties;
}
