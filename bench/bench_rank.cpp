#include <benchmark/benchmark.h>
#include <random>
#include <string>

#include "core/deck.h"
#include "core/hand.h"

static yg::Hand CreateHand(int num_cards) {
  static std::random_device rd;
  static std::mt19937 mt(rd());
  auto cards = yg::Deck{}.Cards();
  std::shuffle(cards.begin(), cards.end(), mt);
  auto hand = yg::Hand{};
  for (int i = 0; i < num_cards; i++) {
    hand.AddCard(cards[i]);
  }
  return hand;
}

static void BM_rank_random(benchmark::State& state) {
  auto hand = CreateHand(state.range(0));
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(hand.Rank());
    hand.ClearRank();
  }
}

static void BM_rank_str(benchmark::State& state, std::string hand_str) {
  auto hand = yg::Hand{hand_str};
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(hand.Rank());
    hand.ClearRank();
  }
}

BENCHMARK_CAPTURE(BM_rank_str, straigh_flush, std::string{"AsKsQsJsTs4h8d"});
BENCHMARK_CAPTURE(BM_rank_str, full_house_two_pair, std::string{"2h2d2c8d8sKdKs"});
BENCHMARK_CAPTURE(BM_rank_str, four_of_a_kind_5, std::string{"AdAcAsAhTs"});
BENCHMARK(BM_rank_random)->Arg(5)->Arg(7);

BENCHMARK_MAIN();