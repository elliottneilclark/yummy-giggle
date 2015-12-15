#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <unordered_map>

namespace yg {
constexpr uint16_t kTwo = 1;
constexpr uint16_t kThree = 1 << 1;
constexpr uint16_t kFour = 1 << 2;
constexpr uint16_t kFive = 1 << 3;
constexpr uint16_t kSix = 1 << 4;
constexpr uint16_t kSeven = 1 << 5;
constexpr uint16_t kEight = 1 << 6;
constexpr uint16_t kNine = 1 << 7;
constexpr uint16_t kTen = 1 << 8;
constexpr uint16_t kJack = 1 << 9;
constexpr uint16_t kQueen = 1 << 10;
constexpr uint16_t kKing = 1 << 11;
constexpr uint16_t kAce = 1 << 12;

constexpr std::array<uint16_t, 13> kValues{kTwo,   kThree, kFour, kFive, kSix,
                                           kSeven, kEight, kNine, kTen,  kJack,
                                           kQueen, kKing,  kAce};
constexpr std::array<char, 13> kValueChars{'2', '3', '4', '5', '6', '7', '8',
                                           '9', 'T', 'J', 'Q', 'K', 'A'};

constexpr uint8_t kHearts = 1 << 0;
constexpr uint8_t kDiamonds = 1 << 1;
constexpr uint8_t kSpades = 1 << 2;
constexpr uint8_t kClubs = 1 << 3;

constexpr std::array<uint8_t, 4> kSuits{kHearts, kDiamonds, kSpades, kClubs};
constexpr std::array<char, 4> kSuitChars{'h', 'd', 's', 'c'};

// Maps of char to value. used for parsing.
//
// These should really be constexpr but I don't want to drag in
// another dependency just for that.
const std::unordered_map<char, uint16_t> kValueCharMap{
    {'2', kTwo},   {'3', kThree}, {'4', kFour}, {'5', kFive}, {'6', kSix},
    {'7', kSeven}, {'8', kEight}, {'9', kNine}, {'T', kTen},  {'J', kJack},
    {'Q', kQueen}, {'K', kKing},  {'A', kAce},
};
const std::unordered_map<char, uint8_t> kSuitCharMap{
    {'h', kHearts}, {'d', kDiamonds}, {'s', kSpades}, {'c', kClubs},
};

class Card {
public:
  Card();
  explicit Card(std::string s);
  Card(uint16_t value, uint8_t suit);
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
