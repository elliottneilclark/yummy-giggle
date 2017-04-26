#pragma once

#include <boost/optional.hpp>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "core/card.h"

namespace yg {

class Hand {
 public:
  Hand();
  Hand(const Hand &rhs);
  void AddCard(Card c);
  void RemoveLast();
  void Clear();
  uint64_t Rank() const;
  int size() const { return cards_.size(); }
  friend std::ostream &operator<<(::std::ostream &os, const Hand &hand);
  bool operator<(const Hand &rhs) const;
  bool operator>(const Hand &rhs) const;
  bool operator<=(const Hand &rhs) const;
  bool operator>=(const Hand &rhs) const;
  bool operator==(const Hand &rhs) const;

 private:
  std::string str() const;
  uint64_t ComputeRank() const;
  std::vector<Card> cards_;
  mutable boost::optional<uint64_t> computed_rank_;
};

std::ostream &operator<<(::std::ostream &os, const Hand &hand);

}  // namespace yg
