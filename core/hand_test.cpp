#include "core/hand.h"

#include <iostream>
#include <gtest/gtest.h>

#include "core/deck.h"

using namespace yg;
using namespace std;

TEST(HandTest, testAddCard) {
  Hand h;
  Deck d;

  auto cards = d.Cards();

  for (int i = 0; i < 5; i++) {
    h.AddCard(cards[i]);
    EXPECT_EQ(i + 1, h.size());
  }
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

          h1.AddCard(c1);
          h1.AddCard(c2);
          h1.AddCard(c3);
          h1.AddCard(c4);
          h1.AddCard(c5);

          Hand h2;
          Card b1{v1, kDiamonds};
          Card b2{v1, kSpades};
          Card b3{v2, kSpades};
          Card b4{v3, kSpades};
          Card b5{v4, kSpades};

          h2.AddCard(b1);
          h2.AddCard(b2);
          h2.AddCard(b3);
          h2.AddCard(b4);
          h2.AddCard(b5);

          EXPECT_GT(h1, h2);
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

          h1.AddCard(c1);
          h1.AddCard(c2);
          h1.AddCard(c3);
          h1.AddCard(c4);
          h1.AddCard(c5);

          Hand h2;
          Card b1{v1, kDiamonds};
          Card b2{v1, kSpades};
          Card b3{v2, kSpades};
          Card b4{v3, kSpades};
          Card b5{v4, kSpades};

          h2.AddCard(b1);
          h2.AddCard(b2);
          h2.AddCard(b3);
          h2.AddCard(b4);
          h2.AddCard(b5);

          EXPECT_GT(h1, h2);
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

  h1.AddCard(c1);
  h1.AddCard(c2);
  h1.AddCard(c3);
  h1.AddCard(c4);
  h1.AddCard(c5);
  Hand h2;
  Card b1{kAce, kHearts};
  Card b2{kAce, kClubs};
  Card b3{kAce, kDiamonds};
  Card b4{kKing, kClubs};
  Card b5{kKing, kDiamonds};

  h2.AddCard(b1);
  h2.AddCard(b2);
  h2.AddCard(b3);
  h2.AddCard(b4);
  h2.AddCard(b5);
  EXPECT_GT(h2, h1);
}
TEST(HandTest, testCompareTwo) {
  Hand h1;
  Card c1{kKing, kHearts};
  Card c2{kKing, kClubs};
  Card c3{kAce, kClubs};
  Card c4{kAce, kDiamonds};
  Card c5{kTen, kDiamonds};

  h1.AddCard(c1);
  h1.AddCard(c2);
  h1.AddCard(c3);
  h1.AddCard(c4);
  h1.AddCard(c5);
  Hand h2;
  Card c6{kNine, kDiamonds};

  h2.AddCard(c1);
  h2.AddCard(c2);
  h2.AddCard(c3);
  h2.AddCard(c4);
  h2.AddCard(c6);
  EXPECT_GT(h1, h2);
}
TEST(HandTest, testCompareAceHighCard) {
  Hand h1;
  Card c1{kAce, kHearts};
  Card c2{kTwo, kClubs};
  Card c3{kThree, kClubs};
  Card c4{kFour, kClubs};
  Card c5{kSix, kClubs};

  h1.AddCard(c1);
  h1.AddCard(c2);
  h1.AddCard(c3);
  h1.AddCard(c4);
  h1.AddCard(c5);
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

            h2.AddCard(b1);
            h2.AddCard(b2);
            h2.AddCard(b3);
            h2.AddCard(b4);
            h2.AddCard(b5);

            EXPECT_GT(h1, h2);
          }
        }
      }
    }
  }
}
TEST(HandTest, testCompareFour) {
  Hand h1;
  Hand h2;

  h1.AddCard({kAce, kHearts});
  h1.AddCard({kAce, kDiamonds});
  h1.AddCard({kAce, kSpades});
  h1.AddCard({kAce, kClubs});
  h1.AddCard({kKing, kClubs});

  h2.AddCard({kAce, kHearts});
  h2.AddCard({kAce, kDiamonds});
  h2.AddCard({kAce, kSpades});
  h2.AddCard({kAce, kClubs});
  h2.AddCard({kQueen, kClubs});

  EXPECT_GT(h1, h2);
  EXPECT_NE(0, h1.Rank() | kFourOfAKind);
}

TEST(HandTest, testCompareStraightWheel) {
  // The wheel
  auto h1 = Hand{"Ad2c3s4dKs5h"};
  // Ace high
  auto h2 = Hand{"Ad2c3sTd8s5h"};

  EXPECT_GT(h1, h2);
  EXPECT_NE(0, h1.Rank() | kStraight);
}