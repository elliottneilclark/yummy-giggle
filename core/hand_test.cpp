#include "core/hand.h"
#include "core/deck.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace yg;
using namespace std;

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

  EXPECT_GE(h.rank(), 15990);
  EXPECT_LT(h.rank(), 16090);
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

  EXPECT_GE(h.rank(), 3220);
  EXPECT_LT(h.rank(), 15990);
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
  for (uint16_t v1 : kValues) {
    for (uint16_t v2 : kValues) {
      if (v1 == v2)
        continue;
      Hand h;
      Card c1{v1, kHearts};
      Card c2{v1, kClubs};
      Card c3{v1, kDiamonds};
      Card c4{v2, kSpades};
      Card c5{v2, kClubs};

      h.add_card(c1);
      h.add_card(c2);
      h.add_card(c3);
      h.add_card(c4);
      h.add_card(c5);

      EXPECT_GE(h.rank(), 1660);
      EXPECT_LT(h.rank(), 3220);
    }
  }
}
TEST(HandTest, testThree) {
  for (uint16_t v1 : kValues) {
    for (uint16_t v2 : kValues) {
      if (v1 == v2)
        continue;
      for (uint16_t v3 : kValues) {
        if (v1 == v3 || v2 == v3)
          continue;
        Hand h;
        Card c1{v1, kHearts};
        Card c2{v1, kClubs};
        Card c3{v1, kDiamonds};
        Card c4{v2, kSpades};
        Card c5{v3, kClubs};

        h.add_card(c1);
        h.add_card(c2);
        h.add_card(c3);
        h.add_card(c4);
        h.add_card(c5);

        EXPECT_GE(h.rank(), 16090);
        EXPECT_LT(h.rank(), 24670);
      }
    }
  }
}
TEST(HandTest, testTwoPair) {
  for (uint16_t v1 : kValues) {
    for (uint16_t v2 : kValues) {
      if (v1 == v2)
        continue;
      for (uint16_t v3 : kValues) {
        if (v1 == v3 || v2 == v3)
          continue;
        Hand h;
        Card c1{v1, kHearts};
        Card c2{v1, kClubs};
        Card c3{v2, kDiamonds};
        Card c4{v2, kSpades};
        Card c5{v3, kClubs};

        h.add_card(c1);
        h.add_card(c2);
        h.add_card(c3);
        h.add_card(c4);
        h.add_card(c5);

        EXPECT_GE(h.rank(), 246700);
        EXPECT_LT(h.rank(), 332500);
      }
    }
  }
}
TEST(HandTest, testPair) {
  for (uint i = 0; i < kValues.size(); i++) {
    Hand h;
    Card c1{kValues[i], kHearts};
    Card c2{kValues[i], kDiamonds};

    Card c3{kValues[(i + 1) % kValues.size()], kSpades};
    Card c4{kValues[(i + 2) % kValues.size()], kSpades};
    Card c5{kValues[(i + 3) % kValues.size()], kSpades};

    h.add_card(c1);
    h.add_card(c2);
    h.add_card(c3);
    h.add_card(c4);
    h.add_card(c5);

    EXPECT_GE(h.rank(), 332500);
    EXPECT_LT(h.rank(), 618500);
  }
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

  EXPECT_GE(h.rank(), 618500);
  EXPECT_LT(h.rank(), 746200);
}
