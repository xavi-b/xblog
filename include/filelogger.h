#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <QCoreApplication>
#include <QThread>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include "logger.h"
#include "export.h"

namespace XB
{

class XBLOG_EXPORT FileLogger : public QThread
{
    Q_OBJECT
private:
    QString dirPath;
    QString baseFilename;
    qint64 logFileMaxSize = 1024 * 1024; // 1024 KB
    QFile currentLogFile;

    void logWrittenHandler(Log const& log);
    QString getLogFilenameFormat(QString const& baseFilename, char c) const;
    QString getLogFilenameFormat(QString const& baseFilename, int currentLogFileNum) const;
    QString getCurrentLogFilename() const;

    virtual void run() override;

public:
    FileLogger(QString const& dirPath, QObject* parent = nullptr);
    ~FileLogger();

    void setLogFileMaxSize(qint64 kbSize)
    {
        this->logFileMaxSize = kbSize * 1024;
    }

    void setBaseFilename(QString const& baseFilename)
    {
        this->baseFilename = baseFilename;
    }

signals:
    void fileError(QFile::FileError);
};

}

#endif // FILELOGGER_H
