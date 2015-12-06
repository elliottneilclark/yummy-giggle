#pragma once

#include <array>
#include <unordered_map>
#include <iostream>
#include <cstdint>
#include <string>

#include "core/card.h"

namespace yg {

class Hand {
public:
  Hand();
  Hand(const Hand &rhs);
  void add_card(Card c);
  void remove_last();
  int64_t rank() const;
  int size() const { return next_slot_; }
  friend std::ostream &operator<<(::std::ostream &os, const Hand &hand);
  bool operator<(const Hand &rhs) const;
  bool operator==(const Hand &rhs) const;

private:
  std::string card_str() const;
  int64_t compute_rank() const;
  int64_t straight_rank(uint16_t value_mask, bool is_flush) const;
  bool is_flush() const;
  std::unordered_map<uint8_t, uint16_t> count_cards() const;
  std::array<Card, 5> cards_;
  uint8_t next_slot_;
  mutable int64_t computed_rank_;
};

std::ostream &operator<<(::std::ostream &os, const Hand &hand);

} // namespace yg
