#include "core/card.h"
#include <vector>
#include <unordered_map>

namespace yg {
class Hand {
public:
  void add_card(Card c);
  int rank() const;
  int size() const { return cards_.size(); }
  bool is_flush() const;

private:
  int straight_rank(uint16_t value_mask, bool is_flush) const;
  std::unordered_map<uint8_t, uint16_t> count_cards() const;
  std::vector<Card> cards_;
};
}
