#pragma once

#include <limits.h>
#include <stdint.h>

namespace yg {

class Bits {
 public:
  // Most of the implementation ideas come from:
  // http://foonathan.net/blog/2016/02/11/implementation-challenge-2.html
  static std::uint8_t popcnt(std::uint8_t x) {
    return popcnt_impl(popcnt_tag{}, x);
  }
  static std::uint8_t popcnt(std::uint16_t x) {
    return popcnt_impl(popcnt_tag{}, x);
  }
  static std::uint8_t popcnt(std::uint32_t x) {
    return popcnt_impl(popcnt_tag{}, x);
  }
  static std::uint8_t popcnt(std::uint64_t x) {
    return popcnt_impl(popcnt_tag{}, x);
  }
  static std::uint8_t clz(std::uint8_t x) { return clz_impl(clz_tag{}, x); }
  static std::uint8_t clz(std::uint16_t x) { return clz_impl(clz_tag{}, x); }
  static std::uint8_t clz(std::uint32_t x) { return clz_impl(clz_tag{}, x); }
  static std::uint8_t clz(std::uint64_t x) { return clz_impl(clz_tag{}, x); }
  static std::uint8_t ilog2(uint64_t x) { return x ? 64 - clz(x) - 1 : 0; }

  static std::uint64_t KeepHighest(std::uint64_t x) {
    return 1 << (64 - clz(x) - 1);
  }

  static std::uint64_t KeepNHighest(std::uint64_t x, uint8_t to_keep) {
    auto result = x;
    while (popcnt(result) > to_keep) {
      result = result & (result - 1);
    }
    return result;
  }

 private:
  Bits() {}

  struct clzll_tag {};
  struct clzl_tag : clzll_tag {};
  struct clz_tag : clzl_tag {};

  template <typename T, typename = typename std::enable_if<
                            sizeof(T) <= sizeof(unsigned int)>::type>
  static std::uint8_t clz_impl(clz_tag, T x) {
    if (!x) {
      return sizeof(T) * CHAR_BIT;
    }
    return __builtin_clz(x) -
           (sizeof(unsigned int) * CHAR_BIT - sizeof(T) * CHAR_BIT);
  }

  template <typename T, typename = typename std::enable_if<
                            sizeof(T) <= sizeof(unsigned long)>::type>
  static std::uint8_t clz_impl(clzl_tag, T x) {
    if (!x) {
      return sizeof(T) * CHAR_BIT;
    }
    return __builtin_clzl(x) -
           (sizeof(unsigned long) * CHAR_BIT - sizeof(T) * CHAR_BIT);
  }

  template <typename T, typename = typename std::enable_if<
                            sizeof(T) <= sizeof(unsigned long long)>::type>
  static std::uint8_t clz_impl(clzll_tag, T x) {
    if (!x) {
      return sizeof(T) * CHAR_BIT;
    }
    return __builtin_clzll(x) -
           (sizeof(unsigned long long) * CHAR_BIT - sizeof(T) * CHAR_BIT);
  }

  struct popcntll_tag {};
  struct popcntl_tag : popcntll_tag {};
  struct popcnt_tag : popcntl_tag {};

  template <typename T, typename = typename std::enable_if<
                            sizeof(T) <= sizeof(unsigned int)>::type>
  static std::uint8_t popcnt_impl(popcnt_tag, T x) {
    return __builtin_popcount(x);
  }
  template <typename T, typename = typename std::enable_if<
                            sizeof(T) <= sizeof(unsigned long)>::type>
  static std::uint8_t popcnt_impl(popcntl_tag, T x) {
    return __builtin_popcountl(x);
  }
  template <typename T, typename = typename std::enable_if<
                            sizeof(T) <= sizeof(unsigned long long)>::type>
  static std::uint8_t popcnt_impl(popcntll_tag, T x) {
    return __builtin_popcountll(x);
  }
};
}  // namespace yg
