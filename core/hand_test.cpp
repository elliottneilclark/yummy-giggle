#include "core/hand.h"
#include <iostream>
#include "core/deck.h"
#include "gtest/gtest.h"

using namespace yg;
using namespace std;

TEST(HandTest, testAddCard) {
  Hand h;
  Deck d;

  d.shuffle();

  for (int i = 0; i < 5; i++) {
    h.add_card(d.take());
    EXPECT_EQ(i + 1, h.size());
  }
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

  // EXPECT_LT(h.rank(), 10);
  // EXPECT_EQ(h.rank(), 0);
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

  //  EXPECT_EQ(h.rank(), 8);
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

  //  EXPECT_LT(h.rank(), 10);
  //  EXPECT_EQ(h.rank(), 9);
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

  //  EXPECT_GE(h.rank(), 1l << 56);
  //  EXPECT_LT(h.rank(), 1l << 57);
}

TEST(HandTest, testFlush) {
  Hand h;
  Card c1{kTwo, kHearts};
  Card c2{kThree, kHearts};
  Card c3{kFour, kHearts};
  Card c4{kFive, kHearts};
  Card c5{kSeven, kHearts};

  h.add_card(c1);
  h.add_card(c2);
  h.add_card(c3);
  h.add_card(c4);
  h.add_card(c5);

  //  EXPECT_GE(h.rank(), 1l << 55);
  //  EXPECT_LT(h.rank(), 1l << 56);
}
TEST(HandTest, testFour) {
  for (uint16_t v1 : kValues) {
    for (uint16_t v2 : kValues) {
      if (v1 == v2) continue;
      Hand h;
      Card c1{v1, kHearts};
      Card c2{v1, kClubs};
      Card c3{v1, kDiamonds};
      Card c4{v1, kSpades};
      Card c5{v2, kSpades};

      h.add_card(c1);
      h.add_card(c2);
      h.add_card(c3);
      h.add_card(c4);
      h.add_card(c5);

      //      EXPECT_GE(h.rank(), 1l << 53);
      //      EXPECT_LT(h.rank(), 1l << 54);
    }
  }
}
TEST(HandTest, testFull) {
  for (uint16_t v1 : kValues) {
    for (uint16_t v2 : kValues) {
      if (v1 == v2) continue;
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

      //      EXPECT_GE(h.rank(), 1l << 54);
      //      EXPECT_LT(h.rank(), 1l << 55);
    }
  }
}
TEST(HandTest, testThree) {
  for (uint16_t v1 : kValues) {
    for (uint16_t v2 : kValues) {
      if (v1 == v2) continue;
      for (uint16_t v3 : kValues) {
        if (v1 == v3 || v2 == v3) continue;
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

        //        EXPECT_GE(h.rank(), 1l << 57);
        //        EXPECT_LT(h.rank(), 1l << 58);
      }
    }
  }
}
TEST(HandTest, testTwoPair) {
  for (uint16_t v1 : kValues) {
    for (uint16_t v2 : kValues) {
      if (v1 == v2) continue;
      for (uint16_t v3 : kValues) {
        if (v1 == v3 || v2 == v3) continue;
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

        //        EXPECT_GE(h.rank(), 1l << 58);
        //        EXPECT_LT(h.rank(), 1l << 59);
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

    //    EXPECT_GE(h.rank(), 1l << 59);
    //    EXPECT_LT(h.rank(), 1l << 60);
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

  // EXPECT_GE(h.rank(), 1l << 60);
  // EXPECT_LT(h.rank(), 1l << 61);
}

TEST(HandTest, testComparePairAces) {
  for (uint16_t v1 : kValues) {
    if (v1 == kAce) continue;
    for (uint16_t v2 : kValues) {
      if (v1 == v2) continue;
      for (uint16_t v3 : kValues) {
        if (v3 == v1 || v3 == v3) continue;
        for (uint16_t v4 : kValues) {
          if (v4 == v1 || v4 == v2 || v4 == v3) continue;
          Hand h1;
          Card c1{kAce, kHearts};
          Card c2{kAce, kClubs};
          Card c3{kTwo, kClubs};
          Card c4{kThree, kClubs};
          Card c5{kFour, kClubs};

          h1.add_card(c1);
          h1.add_card(c2);
          h1.add_card(c3);
          h1.add_card(c4);
          h1.add_card(c5);

          Hand h2;
          Card b1{v1, kDiamonds};
          Card b2{v1, kSpades};
          Card b3{v2, kSpades};
          Card b4{v3, kSpades};
          Card b5{v4, kSpades};

          h2.add_card(b1);
          h2.add_card(b2);
          h2.add_card(b3);
          h2.add_card(b4);
          h2.add_card(b5);

          EXPECT_LT(h2, h1);
        }
      }
    }
  }
}
TEST(HandTest, testComparePairLow) {
  for (uint16_t v1 : kValues) {
    if (v1 == kTwo) continue;
    for (uint16_t v2 : kValues) {
      if (v1 == v2) continue;
      for (uint16_t v3 : kValues) {
        if (v3 == v1 || v3 == v3) continue;
        for (uint16_t v4 : kValues) {
          if (v4 == v1 || v4 == v2 || v4 == v3) continue;
          Hand h1;
          Card c1{kTwo, kHearts};
          Card c2{kTwo, kClubs};
          Card c3{kThree, kClubs};
          Card c4{kFour, kClubs};
          Card c5{kFive, kClubs};

          h1.add_card(c1);
          h1.add_card(c2);
          h1.add_card(c3);
          h1.add_card(c4);
          h1.add_card(c5);

          Hand h2;
          Card b1{v1, kDiamonds};
          Card b2{v1, kSpades};
          Card b3{v2, kSpades};
          Card b4{v3, kSpades};
          Card b5{v4, kSpades};

          h2.add_card(b1);
          h2.add_card(b2);
          h2.add_card(b3);
          h2.add_card(b4);
          h2.add_card(b5);

          EXPECT_LT(h1, h2);
        }
      }
    }
  }
}
TEST(HandTest, testCompareFull) {
  Hand h1;
  Card c1{kKing, kHearts};
  Card c2{kKing, kClubs};
  Card c3{kKing, kDiamonds};
  Card c4{kAce, kClubs};
  Card c5{kAce, kDiamonds};

  h1.add_card(c1);
  h1.add_card(c2);
  h1.add_card(c3);
  h1.add_card(c4);
  h1.add_card(c5);
  Hand h2;
  Card b1{kAce, kHearts};
  Card b2{kAce, kClubs};
  Card b3{kAce, kDiamonds};
  Card b4{kKing, kClubs};
  Card b5{kKing, kDiamonds};

  h2.add_card(b1);
  h2.add_card(b2);
  h2.add_card(b3);
  h2.add_card(b4);
  h2.add_card(b5);
  // EXPECT_LT(h2, h1);
}
TEST(HandTest, testCompareTwo) {
  Hand h1;
  Card c1{kKing, kHearts};
  Card c2{kKing, kClubs};
  Card c3{kAce, kClubs};
  Card c4{kAce, kDiamonds};
  Card c5{kTen, kDiamonds};

  h1.add_card(c1);
  h1.add_card(c2);
  h1.add_card(c3);
  h1.add_card(c4);
  h1.add_card(c5);
  Hand h2;
  Card c6{kNine, kDiamonds};

  h2.add_card(c1);
  h2.add_card(c2);
  h2.add_card(c3);
  h2.add_card(c4);
  h2.add_card(c6);
  // EXPECT_LT(h1, h2);
}
TEST(HandTest, testCompareAceHighCard) {
  Hand h1;
  Card c1{kAce, kHearts};
  Card c2{kTwo, kClubs};
  Card c3{kThree, kClubs};
  Card c4{kFour, kClubs};
  Card c5{kSix, kClubs};

  h1.add_card(c1);
  h1.add_card(c2);
  h1.add_card(c3);
  h1.add_card(c4);
  h1.add_card(c5);
  for (uint a = 0; a < 12; a++) {
    for (uint b = a + 1; b < 12; b++) {
      for (uint c = b + 1; c < 12; c++) {
        for (uint d = c + 1; d < 12; d++) {
          for (uint e = d + 2; e < 12; e++) {
            Hand h2;
            Card b1{kValues[a], kDiamonds};
            Card b2{kValues[b], kSpades};
            Card b3{kValues[c], kSpades};
            Card b4{kValues[d], kSpades};
            Card b5{kValues[e], kSpades};

            h2.add_card(b1);
            h2.add_card(b2);
            h2.add_card(b3);
            h2.add_card(b4);
            h2.add_card(b5);

            // EXPECT_LT(h1, h2);
          }
        }
      }
    }
  }
}
TEST(HandTest, testCompareFour) {
  Hand h1;
  Hand h2;

  h1.add_card({kAce, kHearts});
  h1.add_card({kAce, kDiamonds});
  h1.add_card({kAce, kSpades});
  h1.add_card({kAce, kClubs});
  h1.add_card({kKing, kClubs});
  h2.add_card({kAce, kHearts});
  h2.add_card({kAce, kDiamonds});
  h2.add_card({kAce, kSpades});
  h2.add_card({kAce, kClubs});
  h2.add_card({kQueen, kClubs});

  // EXPECT_LT(h1, h2);
}
