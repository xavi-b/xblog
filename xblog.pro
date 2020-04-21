TEMPLATE        = lib
CONFIG         += c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += core
DESTDIR         = $$PWD

SUBDIRS += \
    src/

include(src/src.pri)
