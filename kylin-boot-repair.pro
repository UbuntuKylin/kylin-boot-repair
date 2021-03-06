QT       += core gui network  dbus KWindowSystem x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS +=-lpthread
LIBS +=-lX11

CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += gsettings-qt

# v10禁用窗管
lessThan(QT_VERSION, 5.9){
        DEFINES += __V10__
        QT      -= x11extras
        LIBS    -= -lpthread
    LIBS    -= -lX11
}
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIBS    += -lpolkit-qt5-core-1
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/aboutwidget.cpp \
    src/boot_repair.cpp \
    src/cmd_bash.cpp \
    src/daemonipcdbus.cpp \
    src/dbusadaptor.cpp \
    src/fdisk_thread.cpp \
    src/finish_page.cpp \
    src/logwidget.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/partion_device.cpp \
    src/pre_page.cpp \
    src/pre_repair.cpp \
    src/repair_page.cpp \
    src/repair_page2.cpp \
    src/start_page.cpp \
    src/stylewidget.cpp \
    src/stylewidgetattribute.cpp \
    src/stylewidgetshadow.cpp \
    src/sudoauthoritydialog.cpp \
    src/tabmenushadow.cpp \
    src/tabwidget.cpp \
    src/warning_page.cpp

HEADERS += \
    src/aboutwidget.h \
    src/boot_repair.h \
    src/cmd_bash.h \
    src/daemonipcdbus.h \
    src/dbusadaptor.h \
    src/fdisk_thread.h \
    src/finish_page.h \
    src/logwidget.h \
    src/mainwindow.h \
    src/partion_device.h \
    src/pre_page.h \
    src/pre_repair.h \
    src/repair_page.h \
    src/repair_page2.h \
    src/start_page.h \
    src/structNeedToUse.h \
    src/stylewidget.h \
    src/stylewidgetattribute.h \
    src/stylewidgetshadow.h \
    src/sudoauthoritydialog.h \
    src/tabmenushadow.h \
    src/tabwidget.h \
    src/warning_page.h

FORMS +=

TRANSLATIONS += translations/kylin-boot-repair_zh_CN.ts \
                translations/kylin-boot-repair_bo.ts



TARGET = kylin-boot-repair

target.path = /usr/bin
target.source += $$TARGET
icon.path = /usr/share/pixmaps
icon.files = data/bootrepair_icon.png
desktop.path = /usr/share/applications/
desktop.files = kylin-boot-repair.desktop
qm_files.files = translations/*.qm
qm_files.path = /usr/share/kylin-boot-repair/translations/

INSTALLS += target \
            icon \
            desktop \
            qm_files

DISTFILES += \
    data/bootrepair_icon.png \

RESOURCES += \
    data.qrc
