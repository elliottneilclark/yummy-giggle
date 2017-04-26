#include "core/card.h"
#include "gtest/gtest.h"

using namespace yg;

TEST(CardTest, testGetValue) {
  auto c = Card{kThree, kClubs};
  EXPECT_EQ(c.value(), 1);
}

TEST(CardTest, testGetSuit) {
  auto c = Card{kThree, kClubs};
  EXPECT_EQ(c.suit(), 3);

  auto c2 = Card{kFour, kHearts};
  EXPECT_EQ(c2.suit(), 0);

  auto c3 = Card{kFive, kDiamonds};
  EXPECT_EQ(c3.suit(), 1);
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

TEST(CardTest, testParse) {
  EXPECT_EQ(Card{"Qs"}, (Card{kQueen, kSpades}));
  EXPECT_EQ(Card{"3d"}, (Card{kThree, kDiamonds}));
}
