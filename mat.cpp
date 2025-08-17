// LibreOJ #100

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    int matmod;
    class modmat {
      int r, c;
      vector<vector<int>> m;
      public:
      modmat(int const r, int const c)
        : r(r), c(c), m(r, vector<int>(c)) {}
      modmat(int const r, int const c, int const x)
        : modmat(r, c) {
          assert(r == c);
          for (int i(0); i != r; ++i) m[i][i] = x;
        }
      int& operator()(int const x, int const y) { return m[x][y]; }
      int operator()(int const x, int const y) const { return m[x][y]; }
      friend modmat operator+(modmat const& a, modmat const& b) {
        assert(a.r == b.r);
        assert(a.c == b.c);
        modmat c(a.r, a.c);
        for (int i(0); i != a.r; ++i)
          for (int j(0); j != a.c; ++j)
            c(i, j) = (a(i, j) + b(i, j)) % matmod;
        return c;
      }
      friend modmat operator*(modmat const& a, modmat const& b) {
        assert(a.c == b.r);
        modmat c(a.r, b.c);
        for (int i(0); i != a.r; ++i)
          for (int j(0); j != a.c; ++j)
            for (int k(0); k != b.c; ++k)
              c(i, k) = (c(i, k) + 1l * a(i, j) * b(j, k)) % matmod;
        return c;
      }
    };
  }
}

int main() {
  using namespace std;
  using namespace kh;
  constexpr int P(1'000'000'007);
  matmod = P;
  int n, p, m;
  cin >> n >> p >> m;
  modmat a(n, p);
  modmat b(p, m);
  for (int i(0); i != n; ++i)
    for (int j(0); j != p; ++j)
      cin >> a(i, j);
  for (int i(0); i != p; ++i)
    for (int j(0); j != m; ++j)
      cin >> b(i, j);
  modmat const c(a * b);
  for (int i(0); i != n; ++i)
    for (int j(0); j != m; ++j)
      cout << (c(i, j) + P) % P << " \n"[j == m - 1];
  cout.flush();
}
