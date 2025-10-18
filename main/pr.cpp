# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    inline auto concat(vector<long> const& a, vector<long> const& b) {
      vector<long> c(a.size() + b.size());
      merge(a.begin(), a.end(), b.begin(), b.end(), c.begin(),
          [] (...) { return false; });
      return c;
    }
    inline auto merge(vector<long> const& a, vector<long> const& b) {
      vector<long> c(a.size() + b.size());
      merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
      return c;
    }
    constexpr long pow(long x, long n, long const mod) {
      assert(n >= 0);
      assert(mod > 0);
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
      x = pow(x, v, n);
      if (x == 0 || x == 1) return true;
      for (long i(1); i <= u; ++i) {
        if (x == n - 1) return true;
        x = __int128_t(1) * x * x % n;
        if (x == 1) return false;
      }
      return assert(x != 1), false;
    }
    constexpr bool mr(long const n) {
      assert(n >= 1);
      for (long const x
          : { 2, 325, 9'375, 28'178, 450'775, 9'780'504, 1'795'265'022 })
        if (!mr_test(n, x)) return false;
      return true;
    }
    inline long find_any_factor(long const n) {
      assert(n >= 1);
      uniform_int_distribution<long> randn(0, n - 1);
      while (true) {
        static default_random_engine eng;
        auto const next = [n, a = randn(eng)] (long const x)
        { return (__int128_t(x) * x + a) % n; };
        for (long s(randn(eng)), t(next(s)), prod(1), cur(0), tar(1);
            s != t; s = next(s), t = next(next(t))) {
          long const diff(abs(s - t) % n);
          assert(0 < prod), assert(prod < n);
          prod = __int128_t(prod) * diff % n;
          if (!prod) return __gcd(diff, n);
          if (++cur == tar) {
            long const gcd(__gcd(prod, n));
            if (gcd != 1) return gcd;
            cur = 0, tar = min(tar << 1, 0x100l);
          }
        }
      }
    }
    inline auto pr(long const n) {
      assert(n >= 1);
      if (n == 1) return vector<long>();
      if (mr(n)) return vector(1, n);
      long const f(find_any_factor(n));
      return merge(pr(f), pr(n / f));
    }
  }
}

int main() {
  using namespace std;
  using namespace kh;
  int t;
  cin >> t;
  for (int i(1); i <= t; ++i) {
    long n;
    cin >> n;
    if (mr(n)) cout << "Prime" << endl;
    else cout << pr(n).back() << endl;
  }
}
