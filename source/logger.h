#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

class ILogOutput {
public:
  virtual ~ILogOutput() = default;
  virtual void write(const QString& message) = 0;
};

class Logger {
public:
  enum LogLevel {
    INFO,
    WARNING,
    ERROR
  };

  Logger(ILogOutput* output = nullptr);
  void setLogOutput(ILogOutput* output);
  void log(const QString& message, LogLevel level = INFO);

private:
  QString logLevelToString(LogLevel level) const;
  ILogOutput* logOutput;
};

#endif // LOGGER_H
