#pragma once

class Bits {
  public:
    static int popcnt(unsigned int i) {
      return __builtin_popcount(i);
    }

    static int popcnt(unsigned long l) {
      return __builtin_popcountl(l);
    }

    static int popcnt(unsigned long long ll) {
      return __builtin_popcountll(ll);
    }
    
    // http://foonathan.net/blog/2016/02/11/implementation-challenge-2.html

  private:
    Bits() {}
};

