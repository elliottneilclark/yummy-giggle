#include <gtest/gtest.h>

#include <stdint.h>

#include "utils/bits.h"

using namespace yg;

TEST(TestBits, testIlog2) {
  EXPECT_EQ(0, Bits::ilog2(0));
  EXPECT_EQ(0, Bits::ilog2(1));
  EXPECT_EQ(1, Bits::ilog2(2));
  EXPECT_EQ(2, Bits::ilog2(4));
}

TEST(TestBits, testCLZ) {
  EXPECT_EQ(15, Bits::clz(std::uint16_t{1}));
  EXPECT_EQ(31, Bits::clz(std::uint32_t{1}));
  EXPECT_EQ(63, Bits::clz(std::uint64_t{1}));
}
