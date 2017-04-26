#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>

#include <boost/functional/hash.hpp>

namespace yg {
constexpr std::uint16_t kTwo = 0;
constexpr std::uint16_t kThree = 1;
constexpr std::uint16_t kFour = 2;
constexpr std::uint16_t kFive = 3;
constexpr std::uint16_t kSix = 4;
constexpr std::uint16_t kSeven = 5;
constexpr std::uint16_t kEight = 6;
constexpr std::uint16_t kNine = 7;
constexpr std::uint16_t kTen = 8;
constexpr std::uint16_t kJack = 9;
constexpr std::uint16_t kQueen = 10;
constexpr std::uint16_t kKing = 11;
constexpr std::uint16_t kAce = 12;

constexpr std::array<std::uint16_t, 13> kValues{
    kTwo,  kThree, kFour, kFive,  kSix,  kSeven, kEight,
    kNine, kTen,   kJack, kQueen, kKing, kAce};
constexpr std::array<char, 13> kValueChars{'2', '3', '4', '5', '6', '7', '8',
                                           '9', 'T', 'J', 'Q', 'K', 'A'};

constexpr std::uint8_t kHearts = 0;
constexpr std::uint8_t kDiamonds = 1;
constexpr std::uint8_t kSpades = 2;
constexpr std::uint8_t kClubs = 3;

constexpr std::array<std::uint8_t, 4> kSuits{kHearts, kDiamonds, kSpades,
                                             kClubs};
constexpr std::array<char, 4> kSuitChars{'h', 'd', 's', 'c'};

// Maps of char to value. used for parsing.
//
// These should really be constexpr but I don't want to drag in
// another dependency just for that.
const std::unordered_map<char, std::uint16_t> kValueCharMap{
    {'2', kTwo},   {'3', kThree}, {'4', kFour}, {'5', kFive}, {'6', kSix},
    {'7', kSeven}, {'8', kEight}, {'9', kNine}, {'T', kTen},  {'J', kJack},
    {'Q', kQueen}, {'K', kKing},  {'A', kAce},
};
const std::unordered_map<char, std::uint8_t> kSuitCharMap{
    {'h', kHearts}, {'d', kDiamonds}, {'s', kSpades}, {'c', kClubs},
};

class Card {
 public:
  Card();
  explicit Card(std::string s);
  Card(std::uint16_t value, std::uint8_t suit);
  std::uint16_t value() const { return value_; }
  std::uint8_t suit() const { return suit_; }
  std::string str() const;
  bool operator<(const Card &rhs) const;
  bool operator==(const Card &rhs) const;
  bool operator!=(const Card &rhs) const;

 private:
  std::uint16_t value_;
  std::uint8_t suit_;
};

std::ostream &operator<<(::std::ostream &os, const Card &card);
}  // namespace yg

namespace std {
template <>
struct hash<yg::Card> {
  size_t operator()(const yg::Card &c) const {
    size_t seed = 0;
    boost::hash_combine(seed, std::hash<int>{}(c.value()));
    boost::hash_combine(seed, std::hash<int>{}(c.suit()));
    return seed;
  }
};
}