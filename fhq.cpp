# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    inline namespace tools {
      template <typename T>
        inline auto concat(vector<T> const& a, vector<T> const& b) {
          vector<T> c(a.size() + b.size());
          merge(a.begin(), a.end(), b.begin(), b.end(), c.begin(),
              [] (auto...) { return false; });
          return c;
        }
    }
    inline namespace ds {
      class fhq {
        static default_random_engine eng;
        static uniform_int_distribution rand;
        struct node {
          int d[2];
          int p;
          int siz;
          bool rev;
          int val;
          node(): d(), p(), siz(), rev(), val() {}
          node(int const dl, int const dr, int const val):
            d{ dl, dr }, p(rand(eng)), siz(1), rev(), val(val) {}
          node(int const val): node(0, 0, val) {}
        };
        vector<node> v;
        int rt;
        int up(int const g)
        { return v[g].siz = v[v[g].d[0]].siz + v[v[g].d[1]].siz + 1, g; }
        void dn(int const g) {
          if (v[g].rev) {
            swap(v[g].d[0], v[g].d[1]);
            v[v[g].d[0]].rev ^= 1;
            v[v[g].d[1]].rev ^= 1;
            v[g].rev = false;
          }
        }
        template <typename... T>
          int newnode(T const&... args)
          { return v.emplace_back(args...), v.size() - 1; }
        auto split2(int const g, int const p) {
          assert(0 <= p);
          assert(p <= v[g].siz);
          if (p == 0) return pair(0, g);
          if (p == v[g].siz) return pair(g, 0);
          dn(g);
          if (p <= v[v[g].d[0]].siz) {
            auto const [l, r](split2(v[g].d[0], p));
            return pair(l, (v[g].d[0] = r, up(g)));
          } else {
            auto const [l, r](split2(v[g].d[1], p - v[v[g].d[0]].siz - 1));
            return pair((v[g].d[1] = l, up(g)), r);
          }
        }
        int merge2(int const l, int const r) {
          return l && r ? v[l].p < v[r].p ?
            dn(r), v[r].d[0] = merge2(l, v[r].d[0]), up(r) :
            (dn(l), v[l].d[1] = merge2(v[l].d[1], r), up(l)) :
            l + r;
        }
        public:
        fhq(): v(1), rt() {}
        fhq(vector<int> const& a): fhq()
        { for (int const a: a) rt = merge2(rt, newnode(a)); }
        void reverse(int const l, int const r) {
          auto const [v1, v23](split2(rt, l));
          auto const [v2, v3](split2(v23, r - l));
          v[v2].rev ^= 1, rt = merge2(v1, merge2(v2, v3));
        }
        auto operator()() {
          function<vector<int>(int)>
            se = [this, &se] (int const x) {
              if (!x) return vector<int>();
              else return dn(x), concat(se(v[x].d[0]),
                  concat(vector<int>(1, v[x].val), se(v[x].d[1])));
            };
          return se(rt);
        }
      };
      default_random_engine fhq::eng;
      uniform_int_distribution<int> fhq::rand;
    }
  }
}

int main() {
  using namespace kh;
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  fhq treap(a);
  for (int i(1); i <= m; ++i) {
    int l, r;
    cin >> l >> r, --l;
    treap.reverse(l, r);
  }
  a = treap();
  for (int i(0); i != n; ++i)
    cout << a[i] << " \n"[i == n - 1];
  cout.flush();
}
