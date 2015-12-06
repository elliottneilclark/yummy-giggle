#include "core/card.h"

#include <cmath>
#include <string>

namespace yg {

using std::log2;
using std::string;
using std::ostream;

Card::Card() : value_(kTwo), suit_(kHearts) {}
Card::Card(uint16_t value, uint8_t suit) : value_(value), suit_(suit) {}

string Card::str() const {
  int vIdx = static_cast<int>(log2(value_));
  int sIdx = static_cast<int>(log2(suit_));
  return kValueStrings[vIdx] + kSuitStrings[sIdx];
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
