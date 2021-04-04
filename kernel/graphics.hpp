#pragma once

#include <cstdint>

#include "frame_buffer_config.h"

struct PixelColor {
  uint8_t r, g, b;
};

class PixelWriter {
 public:
  PixelWriter(const FrameBufferConfig& config);
  virtual ~PixelWriter() = default;
  virtual void Write(int x, int y, const PixelColor& c) = 0;

 protected:
  uint8_t* PixelAt(int x, int y);

 private:
  const FrameBufferConfig& config_;
};

class RGBResv8BitPerColorPixelWriter : public PixelWriter {
 public:
  using PixelWriter::PixelWriter;
  virtual void Write(int x, int y, const PixelColor& c) override;
};

class BGRResv8BitPerColorPixelWriter : public PixelWriter {
 public:
  using PixelWriter::PixelWriter;
  virtual void Write(int x, int y, const PixelColor& c) override;
};

template <typename T>
struct Vector2D {
  T x, y;
};

void DrawRectangle(PixelWriter& writer, const Vector2D<int>& pos,
                   const Vector2D<int>& size, const PixelColor& c);
void FillRectangle(PixelWriter& writer, const Vector2D<int>& pos,
                   const Vector2D<int>& size, const PixelColor& c);
