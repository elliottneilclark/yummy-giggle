#include <benchmark/benchmark.h>
#include <random>

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

static void BM_rank_seven(benchmark::State& state) {
  auto hand = CreateHand(7);
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(hand.Rank());
    hand.ClearRank();
    benchmark::ClobberMemory();
  }
}

static void BM_rank_five(benchmark::State& state) {
  auto hand = CreateHand(5);
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(hand.Rank());
    hand.ClearRank();
    benchmark::ClobberMemory();
  }
}

BENCHMARK(BM_rank_seven);
BENCHMARK(BM_rank_five);

BENCHMARK_MAIN();