#pragma once

#include <cstdint>
#include <array>
#include <string>

namespace yg {
const uint16_t kTwo = 1;
const uint16_t kThree = 1 << 1;
const uint16_t kFour = 1 << 2;
const uint16_t kFive = 1 << 3;
const uint16_t kSix = 1 << 4;
const uint16_t kSeven = 1 << 5;
const uint16_t kEight = 1 << 6;
const uint16_t kNine = 1 << 7;
const uint16_t kTen = 1 << 8;
const uint16_t kJack = 1 << 9;
const uint16_t kQueen = 1 << 10;
const uint16_t kKing = 1 << 11;
const uint16_t kAce = 1 << 12;

const std::array<uint16_t, 13> kValues{kTwo,   kThree, kFour, kFive, kSix,
                                       kSeven, kEight, kNine, kTen,  kJack,
                                       kQueen, kKing,  kAce};
const std::array<std::string, 13> kValueStrings{
    "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

const uint8_t kHearts = 1 << 0;
const uint8_t kDiamonds = 1 << 1;
const uint8_t kSpades = 1 << 2;
const uint8_t kClubs = 1 << 3;

const std::array<uint8_t, 4> kSuits{kHearts, kDiamonds, kSpades, kClubs};
const std::array<std::string, 4> kSuitStrings{"h", "d", "s", "c"};

class Card {
public:
  explicit Card(uint16_t value = kTwo, uint8_t suit = kHearts);
  uint16_t value() const { return value_; }
  uint8_t suit() const { return suit_; }
  std::string str() const;
  bool operator<(const Card &rhs) const;
  bool operator==(const Card &rhs) const;
  bool operator!=(const Card &rhs) const;

private:
  uint16_t value_;
  uint8_t suit_;
};

std::ostream &operator<<(::std::ostream &os, const Card &card);
} // namespace yg
