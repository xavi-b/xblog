#include "logger.h"

namespace XB
{

Logger::Logger(QObject* parent)
    : QObject(parent)
{

}

void Logger::logPrivate(Log const& log)
{
#ifdef QT_DEBUG
    std::cout << log.toString().toStdString() << std::endl;
#endif

    emit logWritten(log);
}

Logger* Logger::instance()
{
    static Logger i;
    return &i;
}

void Logger::log(Log const& log)
{
    Logger::instance()->logPrivate(log);
}

void Logger::log(LogLevel level, QString const& text)
{
    Logger::instance()->logPrivate(Log(level, text));
}

void Logger::log(QString const& log)
{
    Logger::instance()->logPrivate(Log(log));
}

}
