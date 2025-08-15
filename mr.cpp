// LibreOJ #143

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    constexpr long lpow(long x, long n, long const mod) {
      long y(1);
      while (n) {
        y = n & 1 ? __int128_t(1) * y * x % mod : y;
        x = __int128_t(1) * x * x % mod, n >>= 1;
      }
      return (y + mod) % mod;
    }
    constexpr bool mr_test(long const n, long x) {
      assert(n >= 1);
      if (n == 1) return false;
      long const u(__builtin_ctzl(n - 1));
      long const v((n - 1) >> u);
      x = lpow(x, v, n);
      if (x == 0 || x == 1) return true;
      for (long i(1); i <= u; ++i) {
        if (x == n - 1) return true;
        x = __int128_t(1) * x * x % n;
        if (x == 1) return false;
      }
      return assert(x != 1), false;
    }
    constexpr bool mr(long const n) {
      for (long const x
          : { 2, 325, 9'375, 28'178, 450'775, 9'780'504, 1'795'265'022 })
        if (!mr_test(n, x)) return false;
      return true;
    }
  }
}

int main() {
  using namespace std;
  using namespace kh;
  for (long x; cin >> x;)
    cout << (mr(x) ? 'Y' : 'N') << endl;
}
