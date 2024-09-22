#include "frame.h"
#include <cstring>

QByteArray serializeFrame(const Frame& frame) {
  QByteArray byteArray;
  byteArray.append(reinterpret_cast<const char*>(frame.flag.data()), frame.flag.size());
  byteArray.append(static_cast<char>(frame.sourceAddress));
  byteArray.append(static_cast<char>(frame.destinationAddress));
  byteArray.append(reinterpret_cast<const char*>(frame.data.data()), frame.data.size());
  byteArray.append(static_cast<char>(frame.FCS));
  return byteArray;
}

Frame deserializeFrame(const QByteArray& byteArray) {
  Frame frame;
  int index = 0;

  std::memcpy(frame.flag.data(), byteArray.data() + index, FLAG_SIZE);
  index += FLAG_SIZE;

  frame.sourceAddress = static_cast<uint8_t>(byteArray[index++]);
  frame.destinationAddress = static_cast<uint8_t>(byteArray[index++]);

  std::memcpy(frame.data.data(), byteArray.data() + index, DATA_SIZE);
  index += DATA_SIZE;

  frame.FCS = static_cast<uint8_t>(byteArray[index]);

  return frame;
}
