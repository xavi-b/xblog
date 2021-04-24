#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <QObject>
#include "log.h"
#include "export.h"

namespace XB
{

class XBLOG_EXPORT Logger : public QObject
{
    Q_OBJECT
private:
    Logger(QObject* parent = nullptr);
    void logPrivate(Log const& log);

public:
    static Logger* instance();

    static void log(Log const& log);
    static void log(LogLevel level, QString const& text);
    static void log(QString const& log);

signals:
    void logWritten(Log const& log);
};

}

#endif // LOGGER_H
