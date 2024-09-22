#ifndef TEXTWIDGETOUTPUT_H
#define TEXTWIDGETOUTPUT_H

#include "logger.h"
#include <QTextEdit>

class TextWidgetOutput : public ILogOutput {
private:
  QTextEdit* logWidget;

public:
  TextWidgetOutput(QTextEdit* widget) : logWidget(widget) {}

  void write(const QString& message) override {
    if (logWidget) {
      logWidget->append(message);
    }
  }
};

#endif // TEXTWIDGETOUTPUT_H
