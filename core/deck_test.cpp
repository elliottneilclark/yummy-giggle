#include "core/deck.h"

#include <set>

#include "core/card.h"
#include "gtest/gtest.h"

using namespace yg;

TEST(DeckTest, testTake) {
  Deck d;
  EXPECT_EQ(52, d.Cards().size());
}
