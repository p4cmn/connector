#include "logger.h"
#include <QDateTime>
#include <QDebug>

Logger::Logger(ILogOutput* output) : logOutput(output) {}

void Logger::setLogOutput(ILogOutput* output) {
  logOutput = output;
}

void Logger::log(const QString& message, LogLevel level) {
  QString formattedMessage = QString("[%1] [%2] %3")
  .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"),
       logLevelToString(level),
       message);

  if (logOutput) {
    logOutput->write(formattedMessage);
  } else {
    qDebug() << formattedMessage;
  }
}

QString Logger::logLevelToString(LogLevel level) const {
  switch (level) {
    case INFO: return "INFO";
    case WARNING: return "WARNING";
    case ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}
