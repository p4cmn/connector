#include "serialportcontroller.h"


SerialPortController::SerialPortController(SerialPortModel* model,
  MainWindow* view,
  Logger* logger,
  const QList<QPair<QString, QString>>& validPortPairs,
  QObject* parent)
    : QObject(parent),
    model(model),
    view(view),
    logger(logger),
    validPortPairs(validPortPairs) {

  initializeLogger();

  connect(view, &MainWindow::sendButtonClicked, this, &SerialPortController::sendData);
  connect(view, &MainWindow::portsSelected, this, &SerialPortController::setPorts);
  connect(view, &MainWindow::paritySelected, this, &SerialPortController::setParity);
  connect(model, &SerialPortModel::dataReceived, this, &SerialPortController::onDataReceived);
  connect(model, &SerialPortModel::statusUpdated, this, &SerialPortController::onStatusUpdated);
}

void SerialPortController::initializeLogger() {
  logger->setLogWidget(view->getLogWidget());
}

void SerialPortController::setPorts(const QString& firstPortName, const QString& secondPortName) {
  if (arePortsValid(firstPortName, secondPortName)) {
    model->setPorts(firstPortName, secondPortName);
    logMessage("Transmitter: " + firstPortName + " Receiver: " + secondPortName, Logger::LogLevel::INFO);
  } else {
    view->updateStatus(-1, 0);
    logMessage("Serial ports " + firstPortName + " and " + secondPortName + " are not connected.", Logger::LogLevel::WARNING);
  }
}

void SerialPortController::setParity(const QString &parity) {
  model->setParity(parity);
  logMessage("Parity check set: " + parity, Logger::LogLevel::INFO);
}

void SerialPortController::sendData(const QByteArray& data) {
  if (arePortsValid(view->getSelectedFirstPort(), view->getSelectedSecondPort())) {
    model->sendData(data);
    logMessage("Data sent: " + QString(data), Logger::LogLevel::INFO);
  } else {
    view->updateStatus(-1, 0);
    logMessage("Invalid port selection. Data not sent.", Logger::LogLevel::WARNING);
  }
}

void SerialPortController::logMessage(const QString& message, Logger::LogLevel level) {
  if (logger) {
    logger->log(message, level);
  }
}

bool SerialPortController::arePortsValid(const QString& firstPortName, const QString& secondPortName) {
  return validPortPairs.contains(qMakePair(firstPortName, secondPortName));
}

void SerialPortController::onDataReceived(const QByteArray& data) {
  view->updateOutputField(data);
  logMessage("Data received: " + QString(data), Logger::LogLevel::INFO);
}

void SerialPortController::onStatusUpdated(int baudRate, int bytesTransferred) {
  view->updateStatus(baudRate, bytesTransferred);
}
