#include "filelogger.h"

namespace XB
{

void FileLogger::logWrittenHandler(Log const& log)
{
    if(this->currentLogFile.isOpen() && this->currentLogFile.size() > this->logFileMaxSize)
    {
        this->currentLogFile.close();
        this->currentLogFile.setFileName(this->getCurrentLogFilename());
        if(!this->currentLogFile.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadWrite))
            emit fileError(this->currentLogFile.error());
    }

    if(this->currentLogFile.isOpen())
    {
        QTextStream out(&this->currentLogFile);
        out.setCodec("UTF-8");
        out << log.toString();
    }
}

QString FileLogger::getLogFilenameFormat(QString const& baseFilename, char c) const
{
    return QString("%1.%2.log").arg(baseFilename).arg(c);
}

QString FileLogger::getLogFilenameFormat(QString const& baseFilename, int currentLogFileNum) const
{
    return QString("%1.%2.log").arg(baseFilename).arg(currentLogFileNum);
}

QString FileLogger::getCurrentLogFilename() const
{
    QDir dir(this->dirPath);
    QStringList logFiles = dir.entryList(QStringList(this->getLogFilenameFormat(this->baseFilename, '*')), QDir::Filter::Files);

    int currentLogFileNum = 0;
    bool ok;
    for(int i = 0; i < logFiles.size(); ++i)
    {
        int num = logFiles[i].section('.', 1, 1).toInt(&ok);
        if(ok && num > currentLogFileNum)
            currentLogFileNum = num;
    }

    QFile currentFile(dir.filePath(this->getLogFilenameFormat(this->baseFilename, currentLogFileNum)));
    if(currentFile.exists() && currentFile.open(QIODevice::ReadOnly) && currentFile.size() > this->logFileMaxSize)
        ++currentLogFileNum;

    return dir.filePath(this->getLogFilenameFormat(this->baseFilename, currentLogFileNum));
}

void FileLogger::run()
{
    this->currentLogFile.setFileName(this->getCurrentLogFilename());
    if(!this->currentLogFile.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadWrite))
    {
        emit fileError(this->currentLogFile.error());
        return;
    }

    this->exec();

    if(this->currentLogFile.isOpen())
        this->currentLogFile.close();
}

FileLogger::FileLogger(QString const& dirPath, QObject* parent)
    : QThread(parent), dirPath(dirPath)
{
    if(QCoreApplication::instance())
        baseFilename = QCoreApplication::instance()->applicationName();

    connect(Logger::instance(), &Logger::logWritten, this, &FileLogger::logWrittenHandler);
}

FileLogger::~FileLogger()
{
    if(this->isRunning())
        this->quit();
}

}
