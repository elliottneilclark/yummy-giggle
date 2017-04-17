#pragma once

#include <cstdint>
#include <vector>

#include "core/card.h"
#include "core/deck.h"

namespace yg {
class ChooseIter
    : public std::iterator<std::input_iterator_tag, const std::vector<Card>> {
public:
  ChooseIter();
  ChooseIter(const Deck &, unsigned int);
  bool has_more() const;

  const std::vector<Card> &operator*() const;
  ChooseIter &operator++();
  ChooseIter begin() const;
  ChooseIter end() const;
  bool operator==(const ChooseIter &);
  bool operator!=(const ChooseIter &);

private:
  const unsigned int n_;
  mutable std::vector<Card> result_;
  std::vector<unsigned int> idx_;
  std::vector<Card> cards_;
  bool has_more_;
};
} // namespace yg
