#ifndef EXPORT_H
#define EXPORT_H

#include <QtCore/QtGlobal>

#if defined(XBLOG_LIBRARY)
#  define XBLOG_EXPORT Q_DECL_EXPORT
#else
#  define XBLOG_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORT_H
