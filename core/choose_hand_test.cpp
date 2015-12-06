#include "core/choose_hand.h"

#include <memory>

#include "gtest/gtest.h"
#include "core/hand.h"
#include "core/card.h"

using namespace yg;
using namespace std;

TEST(TestChooseHand, testFour) {
  ChooseHand ch;
  ch.add_card({kAce, kHearts});
  ch.add_card({kAce, kDiamonds});
  ch.add_card({kAce, kSpades});
  ch.add_card({kAce, kClubs});
  ch.add_card({kTwo, kHearts});
  ch.add_card({kThree, kHearts});
  ch.add_card({kKing, kHearts});

  unique_ptr<Hand> h = ch.best_hand();

  EXPECT_TRUE(h != nullptr);
  Hand expected;
  expected.add_card({kAce, kHearts});
  expected.add_card({kAce, kDiamonds});
  expected.add_card({kAce, kSpades});
  expected.add_card({kAce, kClubs});
  expected.add_card({kKing, kHearts});
  EXPECT_EQ(expected, *h);
}

TEST(TestChooseHand, testHighFlush) {
  ChooseHand ch;
  ch.add_card({kAce, kSpades});
  ch.add_card({kKing, kSpades});
  ch.add_card({kQueen, kSpades});
  ch.add_card({kJack, kSpades});
  ch.add_card({kTen, kSpades});
  ch.add_card({kNine, kSpades});
  ch.add_card({kEight, kSpades});

  unique_ptr<Hand> h = ch.best_hand();

  EXPECT_TRUE(h != nullptr);
  Hand expected;
  expected.add_card({kAce, kSpades});
  expected.add_card({kKing, kSpades});
  expected.add_card({kQueen, kSpades});
  expected.add_card({kJack, kSpades});
  expected.add_card({kTen, kSpades});
  EXPECT_EQ(expected, *h);
}
