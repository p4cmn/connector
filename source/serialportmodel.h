#ifndef SERIALPORTMODEL_H
#define SERIALPORTMODEL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPortModel : public QObject {
  Q_OBJECT

private:
  QSerialPort* firstPort;
  QSerialPort* secondPort;
  int bytesTransferred;

public:
  explicit SerialPortModel(QObject* parent = nullptr);
  ~SerialPortModel();

  void setPorts(const QString& firstPortName, const QString& secondPortName);
  void setParity(const QString& parity);
  void sendData(const QByteArray& data);

signals:
  void dataReceived(const QByteArray& data);
  void statusUpdated(int baudRate, int bytesTransferred);

private slots:
  void readData();
};

#endif // SERIALPORTMODEL_H
