#include "logger.h"
#include <QDateTime>


Logger::Logger() : logWidget(nullptr) {}

void Logger::setLogWidget(QTextEdit* widget) {
  logWidget = widget;
}

void Logger::log(const QString& message, LogLevel level) {
  QString formattedMessage = QString("[%1] [%2] %3")
  .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
  .arg(logLevelToString(level))
  .arg(message);

  if (logWidget) {
    logWidget->append(formattedMessage);
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
