#include "gtest/gtest.h"
#include "core/card.h"

TEST(CardTest, testGetValue) {
  Card c{kThree, kClubs};
  EXPECT_EQ(c.value(), 1 << 1);
}

TEST(CardTest, testGetSuit) {
  Card c{kThree, kClubs};
  EXPECT_EQ(c.suit(), 8);

  Card c2{kFour, kHearts};
  EXPECT_EQ(c2.suit(), 1);

  Card c3{kFive, kDiamonds};
  EXPECT_EQ(c3.suit(), 2);
}

TEST(CardTest, testStr) {
  Card c1{kQueen, kSpades};
  EXPECT_EQ(c1.str(), "Qs");
}

TEST(CardTest, testEquals) {
  Card c1{kFour, kClubs};
  Card c2{kFour, kClubs};
  Card c3{kFour, kDiamonds};
  Card c4{kFive, kClubs};
  EXPECT_EQ(c1, c2);
  ASSERT_NE(c1, c3);
  ASSERT_NE(c1, c4);
}
