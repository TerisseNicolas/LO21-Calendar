QT += widgets

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

CONFIG += gui
CONFIG +=qt

SOURCES += \
    main.cpp \
    fenetregraphique.cpp \
    fenetreprogrammation.cpp \
    fenetreexportsemaine.cpp \
    fenetreprogrammationevt.cpp \
    fenetreprojet.cpp \
    fenetretachec.cpp \
    fenetretacheedition.cpp \
    fenetreprojetedition.cpp \
    fenetretacheu.cpp \
    Manager.cpp \
    Programmation.cpp \
    Projet.cpp \
    Tache.cpp \
    fenetreprogrammationsuppr.cpp \
    Duree.cpp

HEADERS += \
    fenetregraphique.h \
    fenetreprogrammation.h \
    fenetreexportsemaine.h \
    fenetreprogrammationevt.h \
    fenetreprojet.h \
    fenetretachec.h \
    fenetretacheedition.h \
    fenetreprojetedition.h \
    fenetretacheu.h \
    Manager.h \
    Programmation.h \
    Projet.h \
    Tache.h \
    fenetreprogrammationsuppr.h \
    Duree.h
