#include "core/card.h"

#include <cmath>

namespace yg {

using std::log2;
using std::string;
using std::ostream;

Card::Card() : value_(kTwo), suit_(kHearts) {}
Card::Card(uint16_t value, uint8_t suit) : value_(value), suit_(suit) {}
Card::Card(string s)
    : value_(kValueCharMap.at(s.at(0))), suit_(kSuitCharMap.at(s.at(1))) {}

string Card::str() const {
  int vIdx = static_cast<int>(log2(value_));
  int sIdx = static_cast<int>(log2(suit_));
  return string(1, kValueChars[vIdx]) + string(1, kSuitChars[sIdx]);
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
} // namespace yg
