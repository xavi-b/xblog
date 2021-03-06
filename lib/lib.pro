TEMPLATE        = lib
CONFIG         += c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += core
TARGET          = xblog
DESTDIR         = $$PWD

unix {
target.path = /usr/lib/
INSTALLS += target
}

DEFINES += XBLOG_LIBRARY

SUBDIRS += \
    $$PWD/../include \
    $$PWD/../src

include($$PWD/../include/include.pri)
include($$PWD/../src/src.pri)
