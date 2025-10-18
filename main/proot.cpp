// Luogu P6091

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    constexpr bool isprime(int const n) {
      assert(n >= 1);
      if (n == 1) return false;
      for (int i(2); i * i <= n; ++i)
        if (!(n % i)) return false;
      return true;
    }
    constexpr int phi(int const n) {
      assert(n >= 1);
      int phi(n);
      for (int i(2), t(n); i <= t; ++i)
        if (i * i > t) phi = phi / t * (t - 1), t /= t;
        else if (!(t % i)) {
          phi = phi / i * (i - 1);
          do t /= i; while (!(t % i));
        }
      return phi;
    }
    constexpr int pow(int x, int n, int const mod) {
      assert(mod >= 1);
      assert(-mod <= x && x <= +mod);
      assert(n >= 0);
      int y(1);
      while (n) {
        y = n & 1 ? 1l * y * x % mod : y;
        x = 1l * x * x % mod, n >>= 1;
      }
      return (y + mod) % mod;
    }
    inline auto pf(int const n) {
      assert(n >= 1);
      vector<int> pf;
      for (int i(2), t(n); i <= t; ++i)
        if (i * i > t) pf.push_back(t), t /= t;
        else if (!(t % i)) {
          pf.push_back(i);
          do t /= i; while (!(t % i));
        }
      return pf;
    }
    inline bool isproot
      (int const n, int const g, int const phi, vector<int> const& pf) {
        assert(n >= 1), assert(1 <= g && g < n);
        if (pow(g, phi, n) != 1) return false;
        for (int const pf: pf) if (pow(g, phi / pf, n) == 1) return false;
        return true;
      }
    inline bool isproot(int const n, int const g)
    { return isproot(n, g, phi(n), pf(phi(n))); }
    inline bool has_proot(int const n) {
      assert(n >= 1);
      if (n == 2) return true;
      if (n == 4) return true;
      if (!(n % 4)) return false;
      return pf(n % 2 ? n : n / 2).size() == 1;
    }
    inline int any_proot(int const n) {
      assert(n >= 1);
      if (!has_proot(n)) return 0;
      int const phi(kh::phi(n));
      auto const pf(kh::pf(phi));
      for (int g(1); g != n; ++g)
        if (isproot(n, g, phi, pf))
          return g;
      return __builtin_unreachable(), 0;
    }
  }
}

int main() {
  using namespace std;
  using namespace kh;
  int t;
  cin >> t;
  for (int i(1); i <= t; ++i) {
    int n, d;
    cin >> n >> d;
    int const phi(kh::phi(n));
    int const g(any_proot(n));
    vector<int> r;
    if (g)
      for (int j(0), pow(1); j != phi; ++j, pow = 1l * pow * g % n)
        if (__gcd(j, phi) == 1) r.push_back(pow);
    sort(r.begin(), r.end());
    cout << r.size() << endl;
    if (r.size() < size_t(d)) cout << endl;
    else {
      for (size_t j(d - 1); j < r.size(); j += d)
        cout << r[j] << " \n"[j + d >= r.size()];
      cout.flush();
    }
  }
}
