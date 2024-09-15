#ifndef SERIALPORTMODEL_H
#define SERIALPORTMODEL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>


#include <QObject>
#include <QSerialPort>

class SerialPortModel : public QObject {
  Q_OBJECT

private:
  QSerialPort* firstPort;
  QSerialPort* secondPort;

public:
  explicit SerialPortModel(QObject* parent = nullptr);
  ~SerialPortModel();

  void setPorts(const QString& firstPortName, const QString& secondPortName);
  void sendData(const QByteArray& data);

signals:
  void dataReceived(const QByteArray& data);

private slots:
  void readData();
};

#endif // SERIALPORTMODEL_H
