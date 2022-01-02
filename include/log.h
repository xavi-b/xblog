#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDateTime>
#include "export.h"

namespace XB
{

enum LogLevel : char
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    __COUNT
};

static const char* LogLevelNames[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR"};

static_assert(sizeof(LogLevelNames) / sizeof(char*) == LogLevel::__COUNT, "Sizes do not match");

struct XBLOG_EXPORT Log
{
    LogLevel  level;
    QString   text;
    QDateTime dateTime;

    Log()
        : dateTime(QDateTime::currentDateTimeUtc())
    {
    }

    Log(LogLevel level, QString const& text)
        : level(level), text(text), dateTime(QDateTime::currentDateTimeUtc())
    {
    }

    Log(QString const& text)
        : Log(LogLevel::DEBUG, text)
    {
    }

    Log(char const* text)
        : Log(LogLevel::DEBUG, text)
    {
    }

    QString toString() const
    {
        return QString("%1 [%2] %3").arg(this->dateTime.toString(Qt::ISODateWithMs)).arg(LogLevelNames[this->level], 10).arg(this->text);
    }
};

} // namespace XB

#endif // LOG_H
