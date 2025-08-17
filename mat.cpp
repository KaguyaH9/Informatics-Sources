// LibreOJ #100

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    template <int M>
      class mat {
        int r, c;
        vector<vector<int>> m;
        public:
        mat(int const r, int const c)
          : r(r), c(c), m(r, vector<int>(c)) {}
        mat(int const r, int const c, int const x)
          : mat(r, c) {
            assert(r == c);
            for (int i(0); i != r; ++i) m[i][i] = x;
          }
        int& operator()(int const x, int const y) { return m[x][y]; }
        int operator()(int const x, int const y) const { return m[x][y]; }
        friend mat operator+(mat const& a, mat const& b) {
          assert(a.r == b.r);
          assert(a.c == b.c);
          mat c(a.r, a.c);
          for (int i(0); i != a.r; ++i)
            for (int j(0); j != a.c; ++j)
              c(i, j) = (a(i, j) + b(i, j)) % M;
          return c;
        }
        friend mat operator*(mat const& a, mat const& b) {
          assert(a.c == b.r);
          mat c(a.r, b.c);
          for (int i(0); i != a.r; ++i)
            for (int j(0); j != a.c; ++j)
              for (int k(0); k != b.c; ++k)
                c(i, k) = (c(i, k) + 1l * a(i, j) * b(j, k)) % M;
          return c;
        }
      };
  }
}

int main() {
  using namespace std;
  using namespace kh;
  constexpr int P(1'000'000'007);
  typedef mat<P> mat;
  int n, p, m;
  cin >> n >> p >> m;
  mat a(n, p);
  mat b(p, m);
  for (int i(0); i != n; ++i)
    for (int j(0); j != p; ++j)
      cin >> a(i, j);
  for (int i(0); i != p; ++i)
    for (int j(0); j != m; ++j)
      cin >> b(i, j);
  mat const c(a * b);
  for (int i(0); i != n; ++i)
    for (int j(0); j != m; ++j)
      cout << (c(i, j) + P) % P << " \n"[j == m - 1];
  cout.flush();
}
