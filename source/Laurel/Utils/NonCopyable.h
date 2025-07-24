#pragma once

namespace Laurel {
class NonCopyable {
  public:
    constexpr NonCopyable() = default;

  private:
    NonCopyable(const NonCopyable&)            = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
} // namespace Laurel