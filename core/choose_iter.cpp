#include "core/choose_iter.h"

#include <limits>

namespace yg {

ChooseIter::ChooseIter()
    : n_(0), result_(0), idx_(0), cards_(0), has_more_(false) {}

ChooseIter::ChooseIter(const Deck &d, unsigned int n)
    : n_(n), result_(n), idx_(n), cards_(52 - d.next_card()), has_more_(true) {
  const auto &cards = d.cards();
  int start = d.next_card();
  for (unsigned int i = start; i < 52; i++) {
    cards_[i - start] = cards[i];
  }

  // Fill the starting idx
  for (unsigned int x = 0; x < n_; x++) {
    idx_[x] = x;
    result_[x] = cards_[idx_[x]];
  }
}
ChooseIter ChooseIter::begin() const { return ChooseIter{*this}; }
ChooseIter ChooseIter::end() const { return ChooseIter{}; }
bool ChooseIter::has_more() const { return n_ > 0 && has_more_; }
const std::vector<Card> &ChooseIter::operator*() const { return result_; }
ChooseIter &ChooseIter::operator++() {
  // This is the heart of this class.
  unsigned int level = n_ - 1;

  do {
    // Advance the index of this level.
    idx_[level]++;

    // If this isn't the last level then the following
    // levels will need more cards.
    // So make sure that there are enough.
    unsigned int cards_needed_after = n_ - (level + 1);
    if (idx_[level] >= (cards_.size() - cards_needed_after)) {
      // This level has moved past the end or other levels will.
      // We should try and go down one level and reset

      // If we were already at the last level then
      // just give up and bail out.
      if (level == 0) {
        has_more_ = false;
        return *this;
      }
      level--;
    } else {
      // Store the current card.
      result_[level] = cards_[idx_[level]];

      // If we're not on the last level then make
      // the next level = to the current level
      // The next loop through will increment the
      // index.
      if (level < n_ - 1) {
        idx_[level + 1] = idx_[level];
      }

      // Move on up
      level++;
    }
  } while (level < n_);
  return *this;
}

// This is a big giant hack.
bool ChooseIter::operator==(const ChooseIter &rhs) {
  return has_more() == rhs.has_more();
}
bool ChooseIter::operator!=(const ChooseIter &rhs) {
  return has_more() != rhs.has_more();
}
}  // namespace yg
