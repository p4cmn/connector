#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QTextEdit>

class Logger {

private:
  QTextEdit* logWidget;

public:

  enum LogLevel {
    INFO,
    WARNING,
    ERROR
  };

  explicit Logger();
  void setLogWidget(QTextEdit* widget);
  void log(const QString& message, LogLevel level = INFO);

private:
  QString logLevelToString(LogLevel level) const;
};

#endif // LOGGER_H
