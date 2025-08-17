// LibreOJ #102

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    template <typename T>
      using less_queue = priority_queue<T>;
    template <typename T>
      using greater_queue = priority_queue<T, vector<T>, greater<>>;
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
          if (v[y].dis + w < v[x].dis) {
            v[x].nxt = i;
            q.emplace(v[x].dis = v[y].dis + w, x);
          }
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
          flow = min(flow, e[v[i].nxt].cap);
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
  }
}

int main() {
  using namespace std;
  using namespace kh;
  int n, m;
  cin >> n >> m;
  mcmf_net net(n + 1);
  for (int i(1); i <= m; ++i) {
    int s, t, c, w;
    cin >> s >> t >> c >> w;
    net.add(s, t, c, w);
  }
  auto const [flow, cost](net.mcmf(1, n));
  cout << flow << ' ' << cost << endl;
}
