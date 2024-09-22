#ifndef FORMATESCAPE_H
#define FORMATESCAPE_H

#include <QString>
#include <QByteArray>

QString formatDataWithEscaping(const QByteArray& data, char escapeByte) {
  QString formattedData;
  for (char byte : data) {
    QString hexByte = QString::number(static_cast<unsigned char>(byte), 16)
    .rightJustified(2, '0')
        .toUpper();
    if (byte == escapeByte) {
      formattedData.append("<span style='color:red;'>").append(hexByte).append("</span> ");
    } else {
      formattedData.append(hexByte).append(" ");
    }
  }
  return formattedData.trimmed();
}

#endif // FORMATESCAPE_H
