#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
    ui->portSelector1->addItem(info.portName());
    ui->portSelector2->addItem(info.portName());
  }

  ui->paritySelector->addItem("None");
  ui->paritySelector->addItem("Even");
  ui->paritySelector->addItem("Odd");

  connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendButtonClicked);
  connect(ui->portSelector1, &QComboBox::currentTextChanged, this, [this]() {
    emit portsSelected(ui->portSelector1->currentText(), ui->portSelector2->currentText());
  });
  connect(ui->portSelector2, &QComboBox::currentTextChanged, this, [this]() {
    emit portsSelected(ui->portSelector1->currentText(), ui->portSelector2->currentText());
  });
  connect(ui->paritySelector, &QComboBox::currentTextChanged, this, [this]() {
    emit paritySelected(ui->paritySelector->currentText());
  });
}

MainWindow::~MainWindow() {
  delete ui;
}

QString MainWindow::getSelectedFirstPort() const {
  return ui->portSelector1->currentText();
}

QString MainWindow::getSelectedSecondPort() const {
  return ui->portSelector2->currentText();
}

QString MainWindow::getReceivedData() const {
  return ui->outputField->toPlainText();
}

QTextEdit* MainWindow::getLogWidget() const {
  return ui->logWidget;
}

void MainWindow::clearFrameStatus() {
  ui->frameTextEdit->clear();
}

void MainWindow::displayFrameInStatus(const Frame& frame) {
  QString frameInfo = QString("Flag: %1%2 | Source: %3 | Destination: %4 | Data: %5 | FCS: %6")
  .arg(static_cast<char>(frame.flag[0]))
      .arg(static_cast<char>(frame.flag[1]))
      .arg(frame.sourceAddress)
      .arg(frame.destinationAddress)
      .arg(QString::fromUtf8(reinterpret_cast<const char*>(frame.data.data()), DATA_SIZE).trimmed())
      .arg(frame.FCS);
  ui->frameTextEdit->append(frameInfo);
}

void MainWindow::displayRawFrameInStatus(const QByteArray& rawFrameData) {
  QString rawFrameInfo = QString("Raw Frame Data: %1").arg(QString::fromUtf8(rawFrameData.toHex(' ')));
  ui->frameTextEdit->append(rawFrameInfo);
}

void MainWindow::displayDataInOutput(const QByteArray& data) {
  ui->outputField->setText(QString::fromUtf8(data));
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    ui->inputField->setText(ui->inputField->text() + "\\r");
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

void MainWindow::onSendButtonClicked() {
  QByteArray data = ui->inputField->text().toUtf8();
  emit sendButtonClicked(data);
}

void MainWindow::updateOutputField(const QByteArray &data) {
  ui->outputField->setText(QString::fromUtf8(data));
}

void MainWindow::updateStatus(int baudRate, int bytesTransferred) {
  ui->speedLabel->setText(QString::number(baudRate));
  ui->bytesLabel->setText(QString::number(bytesTransferred));
}
