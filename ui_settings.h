/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created: Tue 31. Jan 22:08:59 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSlider *ParticleSlider;
    QLineEdit *ParticleEdit;
    QLabel *label_2;
    QSlider *GravitySlider;
    QLineEdit *GravityEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_5;
    QSlider *ParticleSizeSlider;
    QSlider *ParticleOpacitySlider;
    QSlider *ForceSlider;
    QLineEdit *ParticleSizeEdit;
    QLineEdit *ParticleOpacityEdit;
    QLineEdit *ForceEdit;
    QPushButton *btnReset;
    QSpacerItem *verticalSpacer;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDockWidget *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(459, 429);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ParticleSlider = new QSlider(dockWidgetContents);
        ParticleSlider->setObjectName(QString::fromUtf8("ParticleSlider"));
        ParticleSlider->setMinimumSize(QSize(150, 0));
        ParticleSlider->setMinimum(100);
        ParticleSlider->setMaximum(30000000);
        ParticleSlider->setSingleStep(250000);
        ParticleSlider->setPageStep(500000);
        ParticleSlider->setValue(100);
        ParticleSlider->setSliderPosition(100);
        ParticleSlider->setOrientation(Qt::Horizontal);
        ParticleSlider->setTickPosition(QSlider::NoTicks);
        ParticleSlider->setTickInterval(250000);

        gridLayout->addWidget(ParticleSlider, 0, 1, 1, 1);

        ParticleEdit = new QLineEdit(dockWidgetContents);
        ParticleEdit->setObjectName(QString::fromUtf8("ParticleEdit"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ParticleEdit->sizePolicy().hasHeightForWidth());
        ParticleEdit->setSizePolicy(sizePolicy);
        ParticleEdit->setMaximumSize(QSize(75, 16777215));
        ParticleEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ParticleEdit->setReadOnly(true);

        gridLayout->addWidget(ParticleEdit, 0, 2, 1, 1);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        GravitySlider = new QSlider(dockWidgetContents);
        GravitySlider->setObjectName(QString::fromUtf8("GravitySlider"));
        GravitySlider->setMinimumSize(QSize(150, 0));
        GravitySlider->setMinimum(-1000);
        GravitySlider->setMaximum(1000);
        GravitySlider->setOrientation(Qt::Horizontal);
        GravitySlider->setTickPosition(QSlider::NoTicks);

        gridLayout->addWidget(GravitySlider, 1, 1, 1, 1);

        GravityEdit = new QLineEdit(dockWidgetContents);
        GravityEdit->setObjectName(QString::fromUtf8("GravityEdit"));
        sizePolicy.setHeightForWidth(GravityEdit->sizePolicy().hasHeightForWidth());
        GravityEdit->setSizePolicy(sizePolicy);
        GravityEdit->setMaximumSize(QSize(75, 16777215));
        GravityEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        GravityEdit->setReadOnly(true);

        gridLayout->addWidget(GravityEdit, 1, 2, 1, 1);

        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(dockWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_5 = new QLabel(dockWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        ParticleSizeSlider = new QSlider(dockWidgetContents);
        ParticleSizeSlider->setObjectName(QString::fromUtf8("ParticleSizeSlider"));
        ParticleSizeSlider->setMinimumSize(QSize(150, 0));
        ParticleSizeSlider->setMinimum(10);
        ParticleSizeSlider->setMaximum(100);
        ParticleSizeSlider->setValue(11);
        ParticleSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(ParticleSizeSlider, 2, 1, 1, 1);

        ParticleOpacitySlider = new QSlider(dockWidgetContents);
        ParticleOpacitySlider->setObjectName(QString::fromUtf8("ParticleOpacitySlider"));
        ParticleOpacitySlider->setMinimumSize(QSize(150, 0));
        ParticleOpacitySlider->setMaximum(100);
        ParticleOpacitySlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(ParticleOpacitySlider, 3, 1, 1, 1);

        ForceSlider = new QSlider(dockWidgetContents);
        ForceSlider->setObjectName(QString::fromUtf8("ForceSlider"));
        ForceSlider->setMinimumSize(QSize(150, 0));
        ForceSlider->setMinimum(-500);
        ForceSlider->setMaximum(500);
        ForceSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(ForceSlider, 4, 1, 1, 1);

        ParticleSizeEdit = new QLineEdit(dockWidgetContents);
        ParticleSizeEdit->setObjectName(QString::fromUtf8("ParticleSizeEdit"));
        sizePolicy.setHeightForWidth(ParticleSizeEdit->sizePolicy().hasHeightForWidth());
        ParticleSizeEdit->setSizePolicy(sizePolicy);
        ParticleSizeEdit->setMaximumSize(QSize(75, 16777215));
        ParticleSizeEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ParticleSizeEdit->setReadOnly(true);

        gridLayout->addWidget(ParticleSizeEdit, 2, 2, 1, 1);

        ParticleOpacityEdit = new QLineEdit(dockWidgetContents);
        ParticleOpacityEdit->setObjectName(QString::fromUtf8("ParticleOpacityEdit"));
        sizePolicy.setHeightForWidth(ParticleOpacityEdit->sizePolicy().hasHeightForWidth());
        ParticleOpacityEdit->setSizePolicy(sizePolicy);
        ParticleOpacityEdit->setMaximumSize(QSize(75, 16777215));
        ParticleOpacityEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ParticleOpacityEdit->setReadOnly(true);

        gridLayout->addWidget(ParticleOpacityEdit, 3, 2, 1, 1);

        ForceEdit = new QLineEdit(dockWidgetContents);
        ForceEdit->setObjectName(QString::fromUtf8("ForceEdit"));
        sizePolicy.setHeightForWidth(ForceEdit->sizePolicy().hasHeightForWidth());
        ForceEdit->setSizePolicy(sizePolicy);
        ForceEdit->setMaximumSize(QSize(75, 16777215));
        ForceEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ForceEdit->setReadOnly(true);

        gridLayout->addWidget(ForceEdit, 4, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        btnReset = new QPushButton(dockWidgetContents);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));

        verticalLayout->addWidget(btnReset);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_6 = new QLabel(dockWidgetContents);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_7 = new QLabel(dockWidgetContents);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(label_7);

        label_8 = new QLabel(dockWidgetContents);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(label_8);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        Settings->setWidget(dockWidgetContents);

        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDockWidget *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Einstellungen", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Settings", "Gravitation:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Settings", "Partikelgr\303\266\303\237e:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Settings", "Partikelopazit\303\244t:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Settings", "Anzahl der Partikel:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Settings", "Kraft:", 0, QApplication::UnicodeUTF8));
        btnReset->setText(QApplication::translate("Settings", "Werte auf Voreinstellung zur\303\274cksetzen", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Settings", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600; text-decoration: underline;\">Steuerung</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Settings", "Linke Maustaste:\n"
"Leertaste:\n"
"W:\n"
"A:\n"
"S:\n"
"D:\n"
"Bild nach oben:\n"
"Bild nach unten:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Settings", "Szene drehen\n"
"Kraft aktivieren\n"
"Kraftzentrum nach vorne\n"
"Kraftzentrum nach links\n"
"Kraftzentrum nach hinten\n"
"Kraftzentrum nach rechts\n"
"Kraftzentrum nach oben\n"
"Kraftzentrum nach unten", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
