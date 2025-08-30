# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace geometry {
    struct vector {
      double x, y;
      constexpr vector(): x(), y() {}
      constexpr vector(double const x, double const y): x(x), y(y) {}
      constexpr double length() const { return hypot(x, y); }
      constexpr double pownorm2() const { return x * x + y * y; }
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
    struct circle {
      point c;
      double r;
      constexpr circle(): c(), r() {}
      constexpr circle(point const c, double const r): c(c), r(r) {}
      constexpr bool contains(point const p) const
      { return (p - c).pownorm2() <= r * r; }
    };
    constexpr double heron(double const a, double const b, double const c) {
      assert(a + b >= c);
      assert(b + c >= a);
      assert(c + a >= b);
      double const s((a + b + c) / 2);
      return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    constexpr circle circumcircle(point const a, point const b)
    { return circle(0.5 * (a + b), (a - b).length() / 2); }
    constexpr point circumcenter(point const a, point const b, point const c)
    { return segment(a, b).perp_bis() & segment(b, c).perp_bis(); }
    constexpr circle circumcircle(point const a, point const b, point const c) {
      point const cc(circumcenter(a, b, c));
      return circle(cc, (a - cc).length());
    }
    constexpr circle smallest_circle(point const a, point const b, point const c) {
      double const x((a - b).pownorm2());
      double const y((b - c).pownorm2());
      double const z((c - a).pownorm2());
      if (x + y <= z) return circumcircle(c, a);
      if (y + z <= x) return circumcircle(a, b);
      if (z + x <= y) return circumcircle(b, c);
      return circumcircle(a, b, c);
    }
    inline circle smallest_circle(std::vector<point> p) {
      static default_random_engine eng;
      shuffle(p.begin(), p.end(), eng);
      circle c;
      for (auto i(p.begin()); i != p.end(); ++i) {
        if (c.contains(*i)) continue;
        c = circle(*i, 0);
        for (auto j(p.begin()); j != i; ++j) {
          if (c.contains(*j)) continue;
          c = circumcircle(*i, *j);
          for (auto k(p.begin()); k != j; ++k) {
            if (c.contains(*k)) continue;
            c = circumcircle(*i, *j, *k);
          }
        }
      }
      return c;
    }
  }
}
