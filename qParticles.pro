TARGET = qParticles
TEMPLATE = app

win32{
    CONFIG(debug, debug|release) {
        DESTDIR =   $$(IF_OUT_DIR)/dbg
        #LIBS += -l$$(IF_OUT_DIR)/dbg/if3dpane -losgd
    } else {
        DESTDIR =   $$(IF_OUT_DIR)/rel
        #LIBS += -l$$(IF_OUT_DIR)/rel/if3dpane -losg
    }
}


QT += opengl

LIBS += -lQtOpenCLGL -lQtOpenCL
win32: LIBS += -lglew32

HEADERS +=  ./src/mainwindow.h \
            ./src/settings.h \
            ./src/glwidget.h \
            ./src/trackball.h \
            ./src/boundingbox.h \
            ./src/objectbase.h \
            ./src/crosshair.h \

SOURCES +=  ./src/main.cpp \
            ./src/mainwindow.cpp \
            ./src/settings.cpp \
            ./src/glwidget.cpp \
            ./src/trackball.cpp \
            ./src/boundingbox.cpp \
            ./src/objectbase.cpp \
            ./src/crosshair.cpp \
            
            
            
FORMS +=    ./res/forms/mainwindow.ui \
            ./res/forms/settings.ui

TRANSLATIONS += ./res/translations/qparticles_de.ts \
                ./res/translations/qparticles_en.ts
                
RESOURCES += ./res/res.qrc

unix:!macx:!symbian{
    LIBS += -L$$PWD/../qt-opencl/lib/ -lQtOpenCLGL
    LIBS += -L$$PWD/../qt-opencl/lib/ -lQtOpenCL
    INCLUDEPATH += $$PWD/../qt-opencl/src/openclgl
    INCLUDEPATH += $$PWD/../qt-opencl/src/opencl
    DEPENDPATH += $$PWD/../qt-opencl/src/openclgl
    DEPENDPATH += $$PWD/../qt-opencl/src/opencl
}
