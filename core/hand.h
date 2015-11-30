#include <array>
#include <unordered_map>
#include <iostream>
#include <cstdint>

#include "core/card.h"

namespace yg {

class Hand {
 public:
  void add_card(Card c);
  int rank() const;
  int size() const { return cards_.size(); }
  bool is_flush() const;
  friend std::ostream &operator<<(::std::ostream &os, const Hand &hand);
 private:
  int straight_rank(uint16_t value_mask, bool is_flush) const;
  std::unordered_map<uint8_t, uint16_t> count_cards() const;
  int remaining_rank(uint16_t values, int base_rank) const;
  std::array<Card,5> cards_;
  uint8_t next_slot_ = 0;
};

std::ostream &operator<<(::std::ostream &os, const Hand &hand);

}  // namespace yg
