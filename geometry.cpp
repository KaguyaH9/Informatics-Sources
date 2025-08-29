// Luogu P1742

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace geometry {
    struct vector {
      double x, y;
      constexpr vector(): x(), y() {}
      constexpr vector(double const x, double const y): x(x), y(y) {}
      constexpr double length() const { return hypot(x, y); }
      constexpr vector rotate90() const { return vector(-y, +x); }
      constexpr vector operator+() const { return vector(+x, +y); }
      constexpr vector operator-() const { return vector(-x, -y); }
      friend constexpr vector operator+(vector const u, vector const v)
      { return vector(u.x + v.x, u.y + v.y); }
      friend constexpr vector operator-(vector const u, vector const v)
      { return vector(u.x - v.x, u.y - v.y); }
      friend constexpr vector operator*(double const t, vector const v)
      { return vector(t * v.x, t * v.y); }
      friend constexpr vector operator*(vector const v, double const t)
      { return vector(v.x * t, v.y * t); }
      friend constexpr double operator&(vector const u, vector const v)
      { return u.x * v.x + u.y * v.y; }
      friend constexpr double operator|(vector const u, vector const v)
      { return u.x * v.y - u.y * v.x; }
    } typedef point;
    struct line {
      point e;
      vector d;
      constexpr line(): e(), d() {}
      constexpr line(point const e, vector const d): e(e), d(d) {}
      friend constexpr point operator&(line const l, line const m) {
        vector const v0(l.e - m.e);
        vector const v1(m.d);
        vector const v2(l.e + l.d - m.e);
        return l.e + l.d * ((v1 | v0) / ((v1 | v0) + (v2 | v1)));
      }
    };
    struct segment {
      point p, q;
      constexpr segment(): p(), q() {}
      constexpr segment(point const p, point const q): p(p), q(q) {}
      constexpr point midpoint() const { return 0.5 * (p + q); }
      constexpr line perp_bis() const
      { return line(midpoint(), (q - p).rotate90()); }
    };
    constexpr point circumcenter(point const a, point const b, point const c)
    { return segment(a, b).perp_bis() & segment(b, c).perp_bis(); }
    inline point circumcenter(std::vector<point> p) {
      static default_random_engine eng;
      shuffle(p.begin(), p.end(), eng);
      point c;
      double r(0);
      for (auto i(p.begin()); i != p.end(); ++i) {
        if ((*i - c).length() <= r) continue;
        c = *i, r = 0;
        for (auto j(p.begin()); j != i; ++j) {
          if ((*j - c).length() <= r) continue;
          c = 0.5 * (*i + *j);
          r = (*i - *j).length() / 2;
          for (auto k(p.begin()); k != j; ++k) {
            if ((*k - c).length() <= r) continue;
            c = circumcenter(*i, *j, *k);
            r = (*k - c).length();
          }
        }
      }
      return c;
    }
  }
}

int main() {
  using namespace kh;
  cout << fixed << setprecision(18);
  default_random_engine eng;
  int n;
  cin >> n;
  std::vector<point> p(n);
  for (auto& [x, y]: p) cin >> x >> y;
  point const c(circumcenter(p));
  double r(0);
  for (point const& p: p) r = max(r, (p - c).length());
  cout << r << endl;
  cout << c.x << ' ' << c.y << endl;
}
