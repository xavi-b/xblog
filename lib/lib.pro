TEMPLATE        = lib
CONFIG         += c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += core
TARGET          = xblog
DESTDIR         = $$PWD

SUBDIRS += \
    $$PWD/../include \
    $$PWD/../src

include($$PWD/../include/include.pri)
include($$PWD/../src/src.pri)
