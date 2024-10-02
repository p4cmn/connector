#ifndef FRAME_H
#define FRAME_H

#include <cstdint>
#include <QByteArray>

constexpr size_t DATA_SIZE = 10;
constexpr size_t FLAG_SIZE = 2;
constexpr size_t FCS_SIZE = 1;

struct Frame {
  QByteArray flag;
  uint8_t sourceAddress;
  uint8_t destinationAddress;
  QByteArray data;
  QByteArray FCS;

  Frame() : flag(FLAG_SIZE, 0), data(DATA_SIZE, 0), FCS(FCS_SIZE, 0) {}
};

QByteArray serializeFrame(const Frame& frame);
Frame deserializeFrame(const QByteArray& byteArray);

#endif // FRAME_H
