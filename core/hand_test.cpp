#include "core/hand.h"
#include "core/deck.h"
#include "gtest/gtest.h"

using namespace yg;

TEST(HandTest, testAddCard) {
  Hand h;
  Deck d;

  d.shuffle();

  for (int i = 0; i < 5; i++) {
    h.add_card(d.take());
  }

  EXPECT_EQ(5, h.size());
}

TEST(HandTest, testIsFlush) {
  Hand h;
  Deck d;

  for (int i = 0; i < 5; i++) {
    h.add_card(d.take());
  }
  EXPECT_TRUE(h.is_flush());
}

TEST(HandTest, testHighStraightFlush) {
  Hand h;
  Card c1{kAce, kHearts};
  Card c2{kKing, kHearts};
  Card c3{kQueen, kHearts};
  Card c4{kJack, kHearts};
  Card c5{kTen, kHearts};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_LT(h.rank(), 10);
  EXPECT_EQ(h.rank(), 0);
}

TEST(HandTest, testLowStraightFlush) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kThree, kHearts};
  Card c3{kFour, kHearts};
  Card c4{kFive, kHearts};
  Card c5{kSix, kHearts};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_EQ(h.rank(), 8);
}
TEST(HandTest, testWheelStraightFlush) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kThree, kHearts};
  Card c3{kFour, kHearts};
  Card c4{kFive, kHearts};
  Card c5{kAce, kHearts};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_LT(h.rank(), 10);
  EXPECT_EQ(h.rank(), 9);
}
TEST(HandTest, testWheelStraight) {
  Hand h;
  Card c1{kTwo, kDiamonds};
  Card c2{kThree, kHearts};
  Card c3{kFour, kHearts};
  Card c4{kFive, kHearts};
  Card c5{kAce, kHearts};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_GE(h.rank(), 1599);
  EXPECT_LT(h.rank(), 1609);
}

TEST(HandTest, testFlush) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kThree, kHearts};
  Card c3{kFour, kHearts};
  Card c4{kFive, kHearts};
  Card c5{kNine, kHearts};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_GE(h.rank(), 322);
  EXPECT_LT(h.rank(), 1599);
}
TEST(HandTest, testFour) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kTwo, kClubs};
  Card c3{kTwo, kDiamonds};
  Card c4{kTwo, kSpades};
  Card c5{kAce, kSpades};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_GE(h.rank(), 10);
  EXPECT_LT(h.rank(), 156);
}
TEST(HandTest, testFull) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kTwo, kClubs};
  Card c3{kTwo, kDiamonds};
  Card c4{kThree, kSpades};
  Card c5{kThree, kClubs};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_GE(h.rank(), 166);
  EXPECT_LT(h.rank(), 322);
}
TEST(HandTest, testThree) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kTwo, kClubs};
  Card c3{kTwo, kDiamonds};
  Card c4{kThree, kSpades};
  Card c5{kFive, kClubs};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_GE(h.rank(), 1609);
  EXPECT_LT(h.rank(), 2467);
}
TEST(HandTest, testTwoPair) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kTwo, kClubs};
  Card c3{kAce, kDiamonds};
  Card c4{kThree, kSpades};
  Card c5{kThree, kClubs};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_GE(h.rank(), 2467);
  EXPECT_LT(h.rank(), 3325);
}
TEST(HandTest, testPair) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kTwo, kClubs};
  Card c3{kAce, kDiamonds};
  Card c4{kThree, kSpades};
  Card c5{kSeven, kClubs};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_GE(h.rank(), 3325);
  EXPECT_LT(h.rank(), 6185);
}
TEST(HandTest, testHighCard) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kKing, kClubs};
  Card c3{kAce, kDiamonds};
  Card c4{kThree, kSpades};
  Card c5{kSeven, kClubs};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  EXPECT_GE(h.rank(), 6185);
  EXPECT_LT(h.rank(), 7462);
}
