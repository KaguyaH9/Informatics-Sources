# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    template <typename T>
      using less_queue = priority_queue<T>;
    template <typename T>
      using greater_queue = priority_queue<T, vector<T>, greater<>>;
    constexpr auto cmin = [] (auto& a, auto const& b)
    { return b < a ? a = b, true : false; };
    constexpr auto cmax = [] (auto& a, auto const& b)
    { return a < b ? a = b, true : false; };
    class mf_net {
      struct node {
        vector<int> o;
        int dis;
        decltype(o)::const_iterator cur;
      };
      struct arc {
        int head;
        long cap;
        arc(int const h, long const c): head(h), cap(c) {}
      };
      vector<node> v;
      vector<arc> e;
      bool bfs(int const s, int const t) {
        for (node& v: v) v.dis = INT_MAX, v.cur = v.o.begin();
        queue<int> q;
        v[t].dis = 0, q.push(t);
        while (!q.empty()) {
          int const x(q.front()); q.pop();
          for (int const i: v[x].o)
            if (e[i ^ 1].cap && v[e[i].head].dis == INT_MAX)
              v[e[i].head].dis = v[x].dis + 1, q.push(e[i].head);
        }
        return v[s].dis != INT_MAX;
      }
      long dfs(int const s, int const t, long const ii) {
        if (s == t) return ii;
        if (!ii) return 0;
        long oo(0);
        for (auto& i(v[s].cur); i != v[s].o.end(); ++i)
          if (e[*i].cap && v[s].dis - 1 == v[e[*i].head].dis) {
            long const flow(dfs(e[*i].head, t, min(ii - oo, e[*i].cap)));
            oo += flow, e[*i].cap -= flow, e[*i ^ 1].cap += flow;
            if (oo == ii) return oo;
          }
        return oo;
      }
      public:
      mf_net(int const n): v(n), e() {}
      int add(int const s, int const t, long const c) {
        v[s].o.push_back(e.size()), e.emplace_back(t, c);
        v[t].o.push_back(e.size()), e.emplace_back(s, 0);
        return e.size() - 2;
      }
      long mf(int const s, int const t) {
        long flow(0);
        while (bfs(s, t)) flow += dfs(s, t, LONG_MAX);
        return flow;
      }
      long flow(int const idx) const { return e[idx | 1].cap; }
      void erase(int const idx) {
        e[idx | 0].cap = 0;
        e[idx | 1].cap = 0;
      }
    };
    class mcmf_net {
      constexpr static long Inf = LONG_MAX >> 1;
      struct node {
        vector<int> o;
        long dis, hgt, nxt;
      };
      struct arc {
        int head;
        long cap;
        long cost;
        arc(int const head, long const cap, long const cost)
          : head(head), cap(cap), cost(cost) {}
      };
      vector<node> v;
      vector<arc> e;
      long dijkstra(int const s, int const t) {
        for (node& v: v) v.dis = Inf;
        greater_queue<pair<long, int>> q;
        q.emplace(v[t].dis = 0, t);
        auto const relax = [&] (int const x, int const y, int const i) {
          if (!e[i].cap) return;
          long const w(e[i].cost - v[x].hgt + v[y].hgt);
          if (cmin(v[x].dis, v[y].dis + w))
            v[x].nxt = i, q.emplace(v[x].dis, x);
        };
        while (!q.empty()) {
          auto const [d, x](q.top()); q.pop();
          if (d != v[x].dis) continue;
          for (int const i: v[x].o) relax(e[i].head, x, i ^ 1);
        }
        for (node& v: v) v.hgt = min(v.hgt + v.dis, Inf);
        if (v[s].dis == Inf) return 0;
        long flow(Inf);
        for (int i(s); i != t; i = e[v[i].nxt].head)
          cmin(flow, e[v[i].nxt].cap);
        for (int i(s); i != t; i = e[v[i].nxt].head) {
          e[v[i].nxt ^ 0].cap -= flow;
          e[v[i].nxt ^ 1].cap += flow;
        }
        return assert(flow), flow;
      }
      public:
      mcmf_net(int const n): v(n), e() {}
      int add(int const s, int const t, long const cap, long const cost) {
        v[s].o.push_back(e.size()), e.emplace_back(t, cap, +cost);
        v[t].o.push_back(e.size()), e.emplace_back(s,   0, -cost);
        return e.size() - 1;
      }
      auto mcmf(int const s, int const t) {
        long flow(0), cost(0);
        while (true)
          if (long const f(dijkstra(s, t)); !f) break;
          else flow += f, cost += f * v[s].hgt;
        return make_pair(flow, cost);
      }
      long flow(int const idx) const { return e[idx ^ 1].cap; }
    };
    class bounded_net {
      struct arc {
        long lower;
        long upper;
        int index;
        arc(long const l, long const u, int const id):
          lower(l), upper(u), index(id) {}
      };
      int const n, s, t;
      mf_net net;
      vector<long> b;
      vector<arc> e;
      vector<int> idx;
      public:
      bounded_net(int const n)
        : n(n), s(n), t(n + 1), net(n + 2), b(n), e(), idx() {}
      int add(int const s, int const t, long const lower, long const upper) {
        assert(lower <= upper);
        e.emplace_back(lower, upper, net.add(s, t, upper - lower));
        b[s] += lower, b[t] -= lower;
        return e.size() - 1;
      }
      bool operator()() {
        idx.assign(n, -1);
        long sum(0);
        for (int i(0); i != n; ++i) {
          if (b[i] > 0) idx[i] = net.add(i, t, +b[i]);
          if (b[i] < 0) idx[i] = net.add(s, i, -b[i]);
          sum += abs(b[i]);
        }
        return 2 * net.mf(s, t) == sum;
      }
      void clean() {
        for (int i(0); i != n; ++i)
          if (idx[i] >= 0) net.erase(idx[i]);
      }
      long augment(int const s, int const t)
      { return net.mf(s, t); }
      long flow(int const idx) const
      { return e[idx].lower + net.flow(e[idx].index); }
      void erase(int const idx)
      { return net.erase(e[idx].index); }
    };
    class bounded_net_with_source {
      constexpr static long Inf = LONG_MAX >> 1;
      bounded_net net;
      public:
      bounded_net_with_source(int const n): net(n) {}
      int add(int const s, int const t, long const lower, long const upper)
      { return net.add(s, t, lower, upper); }
      long max(int const s, int const t) {
        net.add(t, s, 0, Inf);
        return net() ? net.clean(), net.augment(s, t) : -1;
      }
      long min(int const s, int const t) {
        int const ts(net.add(t, s, 0, Inf));
        if (!net()) return -1;
        long const base(net.flow(ts));
        net.erase(ts);
        return net.clean(), base - net.augment(t, s);
      }
      long flow(int const idx) const { return net.flow(idx); }
    };
  }
}

int main() {
  using namespace kh;
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  bounded_net_with_source net(n + 1);
  vector<int> idx(m);
  for (auto& idx: idx) {
    int u, v, lower, upper;
    cin >> u >> v >> lower >> upper;
    idx = net.add(u, v, lower, upper);
  }
  long const mf(net.min(s, t));
  if (mf >= 0) cout << mf << endl;
  else cout << "please go home to sleep" << endl;
}
