TEMPLATE = app

HEADERS += \
    scene3d.h \
    mainwindow.h \
    interface3dmodel.h \
    glext.h \
    sfera.h \
    yadro.h \
    triangle.h \
    gameplay.h \
    gamer.h

SOURCES += \
    scene3d.cpp \
    mainwindow.cpp \
    interface3dmodel.cpp \
    main.cpp \
    sfera.cpp \
    yadro.cpp \
    mouse_events.cpp \
    triangle.cpp \
    gameplay.cpp \
    gamer.cpp

RESOURCES += \
    textures.qrc

QT += \
    opengl

CONFIG += opengl

LIBS += -lGL -lGLU


