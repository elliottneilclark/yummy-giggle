#include <array>
#include <unordered_map>
#include <iostream>
#include <cstdint>

#include "core/card.h"

namespace yg {

class Hand {
public:
  void add_card(Card c);
  int64_t rank() const;
  int size() const { return cards_.size(); }
  bool is_flush() const;
  friend std::ostream &operator<<(::std::ostream &os, const Hand &hand);
  bool operator<(const Hand &rhs) const;

private:
  int64_t straight_rank(uint16_t value_mask, bool is_flush) const;
  std::unordered_map<uint8_t, uint16_t> count_cards() const;
  std::array<Card, 5> cards_;
  uint8_t next_slot_ = 0;
};

std::ostream &operator<<(::std::ostream &os, const Hand &hand);

} // namespace yg
