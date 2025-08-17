// LibreOJ #104

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    constexpr auto cmin = [] (auto& a, auto const& b)
    { return b < a ? a = b, true : false; };
    constexpr auto cmax = [] (auto& a, auto const& b)
    { return a < b ? a = b, true : false; };
    class treap {
      static default_random_engine eng;
      static uniform_int_distribution rand;
      struct node {
        int mo, d[2];
        int p;
        int key, min, max;
        int cnt, sub;
        node(): mo(), d(), p(), key(), min(), max(), cnt(), sub() {}
        node(int const key):
          mo(), d(), p(rand(eng)),
          key(key), min(key), max(key), cnt(), sub() {}
        node& init() { return p = rand(eng), *this; }
      };
      vector<node> v;
      int newnode(int const key)
      { return v.emplace_back(key), v.size() - 1; }
      void up(int const g) {
        v[g].sub = v[g].cnt;
        v[g].sub += v[v[g].d[0]].sub;
        v[g].sub += v[v[g].d[1]].sub;
        v[g].min = v[v[g].d[0]].sub ? v[v[g].d[0]].min :
          v[g].cnt ? v[g].key : v[v[g].d[1]].sub ? v[v[g].d[1]].min : INT_MAX;
        v[g].max = v[v[g].d[1]].sub ? v[v[g].d[1]].max :
          v[g].cnt ? v[g].key : v[v[g].d[0]].sub ? v[v[g].d[0]].max : INT_MIN;
      }
      void connect(int const d, int const mo, int const idx) {
        if (d) v[d].mo = mo;
        if (mo) v[mo].d[idx] = d, up(mo);
      }
      int index(int const d) const {
        if (v[v[d].mo].d[0] == d) return 0;
        if (v[v[d].mo].d[1] == d) return 1;
        __builtin_unreachable();
      }
      void rotate(int const g) {
        int const mo(v[g].mo), gmo(v[mo].mo);
        int const idg(index(g)), idm(index(mo));
        connect(v[g].d[idg ^ 1], mo, idg);
        connect(mo, g, idg ^ 1);
        connect(g, gmo, idm);
      }
      void correct(int g) {
        while (v[v[g].mo].p < v[g].p) rotate(g);
        while (g) up(g), g = v[g].mo;
      }
      int touch(int const x) {
        int g(1);
        while (v[g].key != x) {
          if (!v[g].d[v[g].key < x])
            connect(newnode(x), g, v[g].key < x);
          g = v[g].d[v[g].key < x];
        }
        return g;
      }
      public:
      treap(): v(2) { v.back().p = INT_MAX; }
      void add(int const x, int const d) {
        int const g(touch(x));
        if (!(v[g].cnt += d)) v[g].max = v[g].min = v[g].key;
        else v[g].min = INT_MAX, v[g].max = INT_MIN;
        correct(g);
      }
      void ins(int const x) { add(x, +1); }
      void era(int const x) { add(x, -1); }
      int rank(int const x) const {
        int g(1), res(1);
        while (g) {
          res += v[g].key < x ? v[v[g].d[0]].sub : 0;
          res += v[g].key < x ? v[g].cnt : 0;
          g = v[g].d[v[g].key < x];
        }
        return res;
      }
      int nth(int n) const {
        assert(1 <= n && n <= v[1].sub);
        int g(1);
        while (g) {
          assert(1 <= n && n <= v[g].sub);
          if (n <= v[v[g].d[0]].sub)
            g = v[g].d[0];
          else {
            n -= v[v[g].d[0]].sub;
            if (n <= v[g].cnt) return v[g].key;
            else n -= v[g].cnt, g = v[g].d[1];
          }
        }
        __builtin_unreachable();
      }
      int prev(int const x) const {
        int g(1), res(INT_MIN);
        while (g) {
          if (x <= v[g].key) g = v[g].d[0];
          else {
            cmax(res, v[g].cnt ? v[g].key :
                v[v[g].d[0]].sub ? v[v[g].d[0]].max : INT_MIN);
            g = v[g].d[1];
          }
        }
        return res;
      }
      int next(int const x) const {
        int g(1), res(INT_MAX);
        while (g) {
          if (v[g].key <= x) g = v[g].d[1];
          else {
            cmin(res, v[g].cnt ? v[g].key :
                v[v[g].d[1]].sub ? v[v[g].d[1]].min : INT_MAX);
            g = v[g].d[0];
          }
        }
        return res;
      }
    };
    default_random_engine treap::eng;
    uniform_int_distribution<int> treap::rand;
  }
}

int main() {
  using namespace std;
  using namespace kh;
  int n;
  cin >> n;
  treap treap;
  for (int i(1); i <= n; ++i) {
    int opt, x;
    cin >> opt >> x;
    switch (opt) {
      case 1: treap.ins(x); break;
      case 2: treap.era(x); break;
      case 3: cout << treap.rank(x) << endl; break;
      case 4: cout << treap.nth(x) << endl; break;
      case 5: cout << treap.prev(x) << endl; break;
      case 6: cout << treap.next(x) << endl; break;
    }
  }
}
