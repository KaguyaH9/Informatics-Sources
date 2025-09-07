# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    template <int P>
      class poly: vector<int> {
        constexpr static int pow(int x, int n) {
          int y(1);
          while (n) {
            y = n & 1 ? 1l * y * x % P : y;
            x = 1l * x * x % P, n >>= 1;
          }
          return y;
        }
        static vector<int> w;
        void init_w(int const lg) {
          assert(!w.empty()), assert(w.front() == 1);
          if (size_t(1) << lg <= w.size()) return;
          assert(lg < __builtin_ctz(P - 1));
          int const r((P - 1) >> __builtin_ctz(P - 1));
          w.assign(1 << lg, 1);
          for (int& x(w[1 << (lg - 1)]); ; ++x)
            if (pow(x, r << lg) != 1) {
              x = pow(x, r);
              while (pow(x, 1 << (lg + 1)) != 1)
                x = 1l * x * x % P;
              break;
            }
          for (int i(1 << (lg - 1)); i >> 1; i >>= 1)
            w[i >> 1] = 1l * w[i] * w[i] % P;
          for (int i(0); i != 1 << lg; ++i)
            w[i] = 1l * w[i & -i] * w[i & (i - 1)] % P;
          assert(1l * w[1] * w[1] % P == P - 1);
        }
        public:
        poly() = default;
        poly(int const n): vector(n) {}
        poly(initializer_list<int> const init): vector(init) {}
        int deg() const { return int(size()) - 1; }
        int& operator[](int const x) { return vector::operator[](x); }
        int operator[](int const x) const { return vector::operator[](x); }
        poly& inplace_dif(int const lg) {
          init_w(lg);
          assert(size() <= size_t(1) << lg);
          resize(1 << lg);
          for (int i(1 << (lg - 1)); i; i >>= 1)
            for (int j(0), k(0); j != 1 << lg; j += i << 1, ++k)
              for (int l(0); l != i; ++l) {
                int const x(at(j | l | 0));
                int const y(at(j | l | i));
                at(j | l | 0) = (x + 1l * w[k] * y) % P;
                at(j | l | i) = (x - 1l * w[k] * y) % P;
              }
          return *this;
        }
        poly& inplace_dit(int const lg) {
          assert(w.size() >= size_t(1) << lg);
          assert(size() == size_t(1) << lg);
          for (int i(1); i != 1 << lg; i <<= 1)
            for (int j(0), k(0); j != 1 << lg; j += i << 1, ++k)
              for (int l(0); l != i; ++l) {
                int const x(at(j | l | 0));
                int const y(at(j | l | i));
                at(j | l | 0) = 1l * (x + y) * w[0] % P;
                at(j | l | i) = 1l * (x - y) * w[k] % P;
              }
          int const inv(P - ((P - 1) >> lg));
          for (int& x: *this) x = 1l * x * inv % P;
          reverse(next(begin()), end());
          return *this;
        }
        poly& inplace_zeta(int const lg) {
          assert(size() == size_t(1) << lg);
          for (int i(1); i != 1 << lg; i <<= 1)
            for (int j(0); j != 1 << lg; j += i << 1)
              for (int k(0); k != i; ++k)
                (at(j | k | i) += at(j | k)) %= P;
          return *this;
        }
        poly& inplace_mobius(int const lg) {
          assert(size() == size_t(1) << lg);
          for (int i(1); i != 1 << lg; i <<= 1)
            for (int j(0); j != 1 << lg; j += i << 1)
              for (int k(0); k != i; ++k)
                (at(j | k | i) -= at(j | k)) %= P;
          return *this;
        }
        poly dif(int const lg) const
        { return poly(*this).inplace_dif(lg); }
        poly dit(int const lg) const
        { return poly(*this).inplace_dit(lg); }
        poly zeta(int const lg) const
        { return poly(*this).inplace_zeta(lg); }
        poly mobius(int const lg) const
        { return poly(*this).inplace_mobius(lg); }
        friend poly operator*(poly const& f, poly const& g) {
          int const lg(__lg(max(f.deg() + g.deg(), 1)) + 1);
          poly const ff(f.dif(lg));
          poly const gg(g.dif(lg));
          poly h(1 << lg);
          for (int i(0); i != 1 << lg; ++i)
            h[i] = 1l * ff[i] * gg[i] % P;
          return h.dit(lg);
        }
        static poly subset_conf(poly const& f, poly const& g) {
          if (f.empty() && g.empty()) return poly();
          int const n(__lg(max(f.deg(), g.deg())) + 1);
          vector<poly> ff(n + 1, 1 << n);
          vector<poly> gg(n + 1, 1 << n);
          for (int i(0); i != 1 << n; ++i) ff[__builtin_popcount(i)][i] = f[i];
          for (int i(0); i != 1 << n; ++i) gg[__builtin_popcount(i)][i] = g[i];
          for (poly& f: ff) f.inplace_zeta(n);
          for (poly& g: gg) g.inplace_zeta(n);
          vector<poly> hh(n + 1, 1 << n);
          for (int i(0); i <= n; ++i)
            for (int j(0); i + j <= n; ++j)
              for (int k(0); k != 1 << n; ++k)
                hh[i + j][k] = (hh[i + j][k] + 1l * ff[i][k] * gg[j][k]) % P;
          for (poly& h: hh) h.inplace_mobius(n);
          poly h(1 << n);
          for (int i(0); i != 1 << n; ++i) h[i] = hh[__builtin_popcount(i)][i];
          return h;
        }
      };
    template <int P>
      vector<int> poly<P>::w(1, 1);
  }
}

int main() {
  using namespace kh;
  constexpr int P(1'000'000'009);
  typedef poly<P> poly;
  int n;
  cin >> n;
  poly f(1 << n);
  poly g(1 << n);
  for (int i(0); i != 1 << n; ++i) cin >> f[i];
  for (int i(0); i != 1 << n; ++i) cin >> g[i];
  poly const h(poly::subset_conf(f, g));
  for (int i(0); i != 1 << n; ++i)
    cout << (h[i] + P) % P << " \n"[i == (1 << n) - 1];
  cout.flush();
}
