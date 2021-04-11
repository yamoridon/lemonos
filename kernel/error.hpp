#pragma once

#include <array>

class Error {
 public:
  enum Code { kSuccess, kFull, kEmtpy, kLastOfCode };

  Error(Code code) : code_{code} {}

  operator bool() const { return code_ != kSuccess; }

  const char* Name() const {
    return code_names_[static_cast<int>(this->code_)];
  }

 private:
  static constexpr std::array<const char*, 3> code_names_ = {"kSuccess",
                                                             "kFull", "kEmpty"};

  Code code_;
};
