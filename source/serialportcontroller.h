#ifndef SERIALPORTCONTROLLER_H
#define SERIALPORTCONTROLLER_H

#include <QObject>
#include "logger.h"
#include "mainwindow.h"
#include "serialportmodel.h"

class SerialPortController : public QObject {
  Q_OBJECT

private:
  SerialPortModel* model;
  MainWindow* view;
  Logger* logger;
  QList<QPair<QString, QString>> validPortPairs;

public:
  explicit SerialPortController(SerialPortModel* model,
                                MainWindow* view,
                                Logger* logger,
                                const QList<QPair<QString, QString>>& validPortPairs,
                                QObject* parent = nullptr);

  void initializeLogger();

  void sendFrame(const QByteArray& data);
  void receiveFrame(const QByteArray& data);

private:
  bool arePortsValid(const QString& firstPortName, const QString& secondPortName);

public slots:
  void setPorts(const QString& firstPortName, const QString& secondPortName);
  void setParity(const QString& parity);
  void sendData(const QByteArray& data);

private slots:
  void onDataReceived(const QByteArray& data);
  void onStatusUpdated(int baudRate, int bytesTransferred);
  void logMessage(const QString& message, Logger::LogLevel level);
};

#endif // SERIALPORTCONTROLLER_H
