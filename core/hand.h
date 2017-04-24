#pragma once

#include <boost/optional.hpp>
#include <cstdint>
#include <iostream>
#include <vector>

#include "core/card.h"

namespace yg {

class Hand {
 public:
  Hand();
  Hand(const Hand &rhs);
  void add_card(Card c);
  void remove_last();
  void clear();
  uint64_t rank() const;
  int size() const { return cards_.size(); }
  friend std::ostream &operator<<(::std::ostream &os, const Hand &hand);
  bool operator<(const Hand &rhs) const;
  bool operator==(const Hand &rhs) const;

 private:
  void clear_rank();
  std::string card_str() const;
  uint64_t compute_rank() const;
  std::vector<Card> cards_;
  mutable boost::optional<uint64_t> computed_rank_;
};

std::ostream &operator<<(::std::ostream &os, const Hand &hand);

}  // namespace yg
