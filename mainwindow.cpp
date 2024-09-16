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

QTextEdit* MainWindow::getLogWidget() const {
  return ui->logWidget;
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
