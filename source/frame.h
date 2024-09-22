#ifndef FRAME_H
#define FRAME_H

#include <cstdint>
#include <array>
#include <QByteArray>

constexpr int DATA_SIZE = 10;
constexpr int FLAG_SIZE = 2;

struct Frame {
  std::array<uint8_t, FLAG_SIZE> flag;
  uint8_t sourceAddress;
  uint8_t destinationAddress;
  std::array<uint8_t, DATA_SIZE> data;
  uint8_t FCS;

  Frame() {
    flag[0] = '$';
    flag[1] = 'a' + 9;
    destinationAddress = 0x00;
    FCS = 0x00;
  }
};

QByteArray serializeFrame(const Frame& frame);
Frame deserializeFrame(const QByteArray& byteArray);

#endif // FRAME_H
