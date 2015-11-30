#include "core/deck.h"

#include <set>

#include "core/card.h"
#include "gtest/gtest.h"

using namespace yg;

TEST(DeckTest, testTake) {
  Deck d;
  std::set<Card> cards;
  while (d.has_more()) {
    cards.insert(d.take());
  }
  EXPECT_EQ(52, cards.size());
}

TEST(DeckTest, testShuffle) {
  Deck d;
  d.shuffle();
  uint8_t starting_suit = d.take().suit();
  int same_suit = 0;
  while (d.has_more() && d.take().suit() == starting_suit) {
    same_suit++;
  }
  ASSERT_LT(same_suit, 13);
}

TEST(DeckTest, testRemove) {
  Deck d;
  std::set<Card> cards;
  Card c1{kKing, kHearts};
  Card c2{kJack, kHearts};
  Card c3{kAce, kClubs};

  d.remove(c1);
  d.remove(c2);
  d.remove(c3);

  d.shuffle();

  while (d.has_more()) {
    cards.insert(d.take());
  }

  for (auto c : cards) {
    EXPECT_NE(c1, c);
    EXPECT_NE(c2, c);
    EXPECT_NE(c3, c);
  }
  EXPECT_EQ(49, cards.size());
}
