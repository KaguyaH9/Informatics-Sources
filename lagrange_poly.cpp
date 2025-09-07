# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    template <int P>
      constexpr int inv(int x) {
        x = (x % P + P) % P;
        assert(0 < x && x < P);
        int y(1);
        while (x != 1) {
          y = 1l * y * -(P / x) % P;
          x = P % x;
        }
        return (y + P) % P;
      }
    template <int P>
      inline auto inv(vector<int> x) {
        if (x.empty()) return x;
        vector<int> fc(x.size());
        vector<int> iv(x.size());
        for (size_t i(0); i != x.size(); ++i)
          fc[i] = i ? 1l * fc[i - 1] * x[i] % P : x[i];
        iv.back() = inv<P>(fc.back());
        for (size_t i(x.size() - 1); i; --i)
          iv[i - 1] = 1l * iv[i] * x[i] % P;
        for (size_t i(0); i != x.size(); ++i)
          x[i] = 1l * (i ? fc[i - 1] : 1) * iv[i] % P;
        return x;
      }
    template <int P>
      class lagrange_poly {
        struct point {
          int x, y;
          int w;
          constexpr point(): x(), y(), w() {}
          constexpr point(int x, int y): x(x), y(y), w(y) {}
        };
        constexpr static int inv(int x) {
          x = (x % P + P) % P;
          assert(0 < x && x < P);
          int y(1);
          while (x != 1) {
            y = 1l * y * -(P / x) % P;
            x = P % x;
          }
          return (y + P) % P;
        }
        vector<point> p;
        public:
        lagrange_poly(): p() {}
        void insert(int x, int y) {
          x = (x % P + P) % P;
          y = (y % P + P) % P;
          vector<int> dif(p.size());
          for (size_t i(0); i != p.size(); ++i)
            dif[i] = x - p[i].x;
          auto const inv(src::inv<P>(dif));
          p.emplace_back(x, y);
          for (size_t i(0); i != p.size() - 1; ++i) {
            assert(x != p[i].x);
            p[i].w = 1l * p[i].w * -inv[i] % P;
            p.back().w = 1l * p.back().w * inv[i] % P;
          }
        }
        int operator()(int const x) const {
          int prod(1);
          int res(0);
          for (auto const& [xi, yi, wi]: p) {
            if (x == xi) return yi;
            res = 1l * res * (x - xi) % P;
            res = (res + 1l * prod * wi) % P;
            prod = 1l * prod * (x - xi) % P;
          }
          return (res + P) % P;
        }
      };
  }
}

int main() {
  using namespace kh;
  constexpr int P(998'244'353);
  int n;
  cin >> n;
  lagrange_poly<P> l;
  for (int i(1); i <= n; ++i) {
    int o, x, y, k;
    switch (cin >> o; o) {
      case 1: cin >> x >> y, l.insert(x, y); break;
      case 2: cin >> k, cout << l(k) << endl; break;
    }
  }
}
