#include "frame.h"
#include "bytestuffing.h"
#include "fragmentation.h"
#include "textwidgetoutput.h"
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
  TextWidgetOutput* logOutput = new TextWidgetOutput(view->getLogWidget());
  logger->setLogOutput(logOutput);
}

void SerialPortController::sendFrame(const QByteArray &data) {
  QList<Frame> frames = fragmentData(data, view->getSelectedFirstPort(), DATA_SIZE);
  QByteArray combinedData;

  for (Frame& frame : frames) {
    QByteArray byteArray = serializeFrame(frame);
    byteArray = applyByteStuffing(byteArray);
    combinedData.append(byteArray);
  }
  model->sendData(combinedData);
}

void SerialPortController::receiveFrame(const QByteArray& byteArray) {
  view->clearFrameStatus();
  QByteArray cleanedData = removeByteStuffing(byteArray);
  int frameSize = sizeof(Frame::flag) + sizeof(Frame::sourceAddress) + sizeof(Frame::destinationAddress) + DATA_SIZE + sizeof(Frame::FCS);
  int totalFrames = cleanedData.size() / frameSize;
  QList<Frame> frames;
  for (int i = 0; i < totalFrames; ++i) {
    QByteArray frameData = cleanedData.mid(i * frameSize, frameSize);
    Frame frame = deserializeFrame(frameData);
    view->displayFrameInStatus(frame);
    frames.append(frame);
  }
  QByteArray completeData = defragmentData(frames);
  view->displayDataInOutput(completeData);
}

void SerialPortController::setPorts(const QString& firstPortName, const QString& secondPortName) {
  if (arePortsValid(firstPortName, secondPortName)) {
    model->setPorts(firstPortName, secondPortName);
    logMessage(QString("Transmitter: %1 Receiver: %2")
                   .arg(firstPortName, secondPortName), Logger::LogLevel::INFO);
  } else {
    view->updateStatus(-1, 0);
    logMessage(QString("Serial ports %1 and %2 are not connected.")
                   .arg(firstPortName, secondPortName), Logger::LogLevel::WARNING);
  }
}

void SerialPortController::setParity(const QString& parity) {
  model->setParity(parity);
  logMessage(QString("Parity check set: %1").arg(parity), Logger::LogLevel::INFO);
}

void SerialPortController::sendData(const QByteArray& data) {
  sendFrame(data);
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
  receiveFrame(data);
}

void SerialPortController::onStatusUpdated(int baudRate, int bytesTransferred) {
  view->updateStatus(baudRate, bytesTransferred);
}
