#include "core/card.h"

#include <cmath>

#include "utils/bits.h"

namespace yg {

using std::log2;
using std::string;
using std::ostream;

Card::Card() : value_(kTwo), suit_(kHearts) {}
Card::Card(std::uint16_t value, std::uint8_t suit)
    : value_(value), suit_(suit) {}
Card::Card(string s)
    : Card(kValueCharMap.at(s.at(0)), kSuitCharMap.at(s.at(1))) {}
Card::Card(char value, char suit)
    : Card(kValueCharMap.at(value), kSuitCharMap.at(suit)) {}

string Card::str() const {
  return string(1, kValueChars[value_]) + string(1, kSuitChars[suit_]);
}

bool Card::operator<(const Card &rhs) const {
  return value_ < rhs.value_ || (value_ == rhs.value_ && suit_ < rhs.suit_);
}

bool Card::operator==(const Card &rhs) const {
  return value_ == rhs.value_ && suit_ == rhs.suit_;
}

bool Card::operator!=(const Card &rhs) const {
  return value_ != rhs.value_ || suit_ != rhs.suit_;
}

ostream &operator<<(ostream &os, const Card &card) { return os << card.str(); }
}  // namespace yg
