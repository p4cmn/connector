#include "serialportcontroller.h"


SerialPortController::SerialPortController(SerialPortModel* model, MainWindow* view, QObject* parent)
    : QObject(parent),
    model(model),
    view(view) {

  connect(view, &MainWindow::sendButtonClicked, this, &SerialPortController::sendData);
  connect(view, &MainWindow::portsSelected, this, &SerialPortController::setPorts);
  connect(model, &SerialPortModel::dataReceived, this, &SerialPortController::onDataReceived);
}

void SerialPortController::setPorts(const QString& firstPortName, const QString& secondPortName) {
  model->setPorts(firstPortName, secondPortName);
}

void SerialPortController::sendData(const QByteArray& data) {
  model->sendData(data);
}

void SerialPortController::onDataReceived(const QByteArray& data) {
  view->updateOutputField(data);
}
