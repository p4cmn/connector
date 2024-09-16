#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "logger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  QString getSelectedFirstPort() const;
  QString getSelectedSecondPort() const;
  QTextEdit* getLogWidget() const;

signals:
  void sendButtonClicked(const QByteArray& data);
  void portsSelected(const QString& firstPort, const QString& secondPort);
  void paritySelected(const QString &parity);

public slots:
  void updateOutputField(const QByteArray& data);
  void updateStatus(int baudRate, int bytesTransferred);

private slots:
  void onSendButtonClicked();

private:
  Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
