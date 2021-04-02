#include <cstddef>
#include <cstdint>

#include "font.hpp"
#include "frame_buffer_config.h"
#include "graphics.hpp"

void* operator new(size_t size, void* buf) { return buf; }

void operator delete(void* obj) noexcept {}

std::byte pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

extern "C" void __cxa_pure_virtual() {
  while (1) __asm__("hlt");
}

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
  switch (frame_buffer_config.pixel_format) {
    case kPixelRGBResv8BitPerColor:
      pixel_writer = new (pixel_writer_buf)
          RGBResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
    case kPixelBGRResv8BitPerColor:
      pixel_writer = new (pixel_writer_buf)
          BGRResv8BitPerColorPixelWriter{frame_buffer_config};
      break;
  }

  for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
      pixel_writer->Write(x, y, {255, 255, 255});
    }
  }
  for (int y = 0; y < 100; ++y) {
    for (int x = 0; x < 200; ++x) {
      pixel_writer->Write(x, y, {0, 255, 0});
    }
  }

  int i = 0;
  for (char c = '!'; c <= '~'; ++c, ++i) {
    WriteAscii(*pixel_writer, 8 * i, 50, c, {0, 0, 0});
  }

  while (1) __asm__("hlt");
}
