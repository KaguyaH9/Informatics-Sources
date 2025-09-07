# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    class nimber {
      unsigned long x;
      public:
      constexpr nimber(): x() {}
      constexpr nimber(unsigned long const x): x(x) {}
      explicit constexpr operator unsigned long() const { return x; }
      friend constexpr nimber operator+(nimber const x, nimber const y)
      { return (unsigned long)(x) ^ (unsigned long)(y); }
      friend nimber operator*(nimber const x, nimber const y) {
        static int mem[0x100][0x100];
        if (static bool once = true; once) {
          once = false;
          memset(mem, 0xff, sizeof mem);
        }
        unsigned long const xx(x);
        unsigned long const yy(y);
        if (xx < 0x100 && yy < 0x100 && mem[xx][yy] >= 0) return mem[xx][yy];
        if (xx <= 1 || yy <= 1) return xx * yy;
        int const k(__lg(__lg(max(xx, yy))));
        nimber const x0(xx & ((1l << (1 << k)) - 1));
        nimber const y0(yy & ((1l << (1 << k)) - 1));
        nimber const x1(xx >> (1 << k));
        nimber const y1(yy >> (1 << k));
        nimber const p0(x0 * y0);
        nimber const p1(x1 * y1);
        nimber const p2((x0 + x1) * (y0 + y1));
        nimber const w1((unsigned long)(p0 + p2) << (1 << k));
        nimber const w2(p1 * nimber(1l << ((1 << k) - 1)));
        unsigned long const res(p0 + w1 + w2);
        if (xx < 0x100 && yy < 0x100) mem[xx][yy] = res;
        return res;
      }
    };
  }
}

int main() {
  using namespace kh;
  int t;
  unsigned sa, sb, sc;
  cin >> t >> sa >> sb >> sc;
  auto const rng = [&sa, &sb, &sc] {
    sa ^= sa << 16;
    sa ^= sa >> 5;
    sa ^= sa << 1;
    unsigned const t(sa);
    sa = sb;
    sb = sc;
    sc ^= t ^ sa;
    return sc;
  };
  unsigned lastans(0);
  for (int i(1); i <= t; ++i) {
    unsigned const x(rng() + lastans);
    unsigned const y(rng());
    lastans = (unsigned long)(nimber(x) * nimber(y));
  }
  cout << lastans << endl;
}
