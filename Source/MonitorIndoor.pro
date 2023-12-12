QT += widgets serialport sql charts printsupport
requires(qtConfig(combobox))

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)


SOURCES += \
    BrowseRecords.cpp \
    RecorderMgr.cpp \
    data.cpp \
    main.cpp \
    led.cpp\
    mainwindow.cpp \
    settingsdialog.cpp

HEADERS += \
    BrowseRecords.h \
    RecorderMgr.h \
    data.h \
    led.h\
    mainwindow.h \
    settingsdialog.h

FORMS += \
    BrowseRecords.ui \
    mainwindow.ui \
    mainwindowedited.ui \
    settingsdialog.ui


target.path =Documents
INSTALLS += target

RESOURCES += \
    MonitorIndoor.qrc

DISTFILES += \
    BrowseRecords.qml \
    BrowseRecordsForm.ui.qml
