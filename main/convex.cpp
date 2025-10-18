# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace tools {
    template <typename Container>
      inline auto& back(Container& c, int const n)
      { return *prev(c.end(), n); }
  }
  inline namespace geometry {
    struct vector {
      double x, y;
      constexpr vector(): x(), y() {}
      constexpr vector(double const x, double const y): x(x), y(y) {}
      constexpr double length() const { return hypot(x, y); }
      constexpr double sqlen() const { return x * x + y * y; }
      constexpr double atan2() const { return std::atan2(y, x); }
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
      friend constexpr bool operator==(vector const u, vector const v)
      { return u.x == v.x && u.y == v.y; }
      friend constexpr bool operator!=(vector const u, vector const v)
      { return u.x != v.x || u.y != v.y; }
      constexpr static bool comp_pair(vector const u, vector const v)
      { return pair(u.x, u.y) < pair(v.x, v.y); }
    } typedef point;
    struct polygon {
      std::vector<point> c;
      polygon(std::vector<point> const& c): c(c) {}
      double perimeter() const {
        assert(!c.empty());
        double p((c.front() - c.back()).length());
        for (auto i(next(c.begin())); i != c.end(); ++i)
          p += (*i - *prev(i)).length();
        return p;
      }
    };
    struct polar {
      point o;
      constexpr polar(): o() {}
      constexpr polar(point const o): o(o) {}
      constexpr auto comp_angular() const
      { return [this] (point const p, point const q)
        { return (p - o).atan2() < (q - o).atan2(); }; }
      constexpr auto comp_radial() const
      { return [this] (point const p, point const q)
        { return (p - o).sqlen() < (q - o).sqlen(); }; }
    };
    inline polygon convex(std::vector<point> p, double const eps = 1e-12) {
      if (p.empty()) return p;
      sort(p.begin(), p.end(), point::comp_pair);
      p.erase(unique(p.begin(), p.end()), p.end());
      point const o(p.front());
      sort(next(p.begin()), p.end(), polar(o).comp_angular());
      decltype(p) c;
      for (point const p: p) {
        if (c.size() > 1 && abs((p - o) | (c.back() - o)) < eps) {
          c.back() = max(c.back(), p, polar(o).comp_radial());
          continue;
        }
        while (c.size() > 1) {
          point const c1(back(c, 1));
          point const c2(back(c, 2));
          if (((p - c2) | (c1 - c2)) <= 0) break;
          else c.pop_back();
        }
        c.push_back(p);
      }
      return c;
    }
  }
}

int main() {
  using namespace kh;
  int n;
  cin >> n;
  std::vector<point> p(n);
  for (auto& [x, y]: p) cin >> x >> y;
  cout << fixed << setprecision(2) << convex(p).perimeter() << endl;
}
