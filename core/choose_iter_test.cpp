#include "core/choose_iter.h"

#include "gtest/gtest.h"

using namespace yg;
using namespace std;

TEST(TestChooseIter, testCreate) {
  Deck d;
  ChooseIter itr{d, 2};
}
TEST(TestChooseIter, testCanOneLoop) {
  Deck d;
  ChooseIter itr{d, 1};

  int c = 0;

  for (const auto &cards : itr) {
    EXPECT_EQ(1, cards.size());
    c++;
  }
  EXPECT_EQ(52, c);
}

TEST(TestChooseIter, testCanTwoLoop) {
  Deck d;
  ChooseIter itr{d, 2};

  int c = 0;

  for (auto &cards : itr) {
    EXPECT_EQ(2, cards.size());
    c++;
  }
  EXPECT_EQ(1326, c);
}
TEST(TestChooseIter, testCanFiveLoop) {
  Deck d;
  ChooseIter itr{d, 5};

  int c = 0;

  for (auto &cards : itr) {
    EXPECT_EQ(5, cards.size());
    c++;
  }
  EXPECT_EQ(2598960, c);
}
TEST(TestChooseIter, testCanFiftyOneLoop) {
  Deck d;
  ChooseIter itr{d, 51};

  int c = 0;

  for (auto &cards : itr) {
    EXPECT_EQ(51, cards.size());
    c++;
  }
  EXPECT_EQ(52, c);
}
