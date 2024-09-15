#ifndef SERIALPORTCONTROLLER_H
#define SERIALPORTCONTROLLER_H

#include <QObject>
#include "serialportmodel.h"
#include "mainwindow.h"

class SerialPortController : public QObject {
  Q_OBJECT

private:
  SerialPortModel* model;
  MainWindow* view;

public:
  explicit SerialPortController(SerialPortModel* model, MainWindow* view, QObject* parent = nullptr);

public slots:
  void setPorts(const QString& firstPortName, const QString& secondPortName);
  void sendData(const QByteArray& data);

private slots:
  void onDataReceived(const QByteArray& data);
};

#endif // SERIALPORTCONTROLLER_H
