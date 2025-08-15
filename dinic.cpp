# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
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
      long flow(size_t const idx) const { return e[idx | 1].cap; }
    };
  }
}

int main() {
  using namespace std;
  using namespace kh;
  int nl, nr, m;
  cin >> nl >> nr >> m;
  mf_net net(nl + nr + 2);
  int const s(0), t(nl + nr + 1);
  auto const idl = [nl, nr] (int const x) { return x; };
  auto const idr = [nl, nr] (int const x) { return x + nl; };
  for (int i(1); i <= nl; ++i) net.add(s, idl(i), 1);
  for (int i(1); i <= nr; ++i) net.add(idr(i), t, 1);
  vector<tuple<int, int, int>> e(m);
  for (auto& [v, u, idx]: e) {
    cin >> v >> u;
    idx = net.add(idl(v), idr(u), 1);
  }
  cout << net.mf(s, t) << endl;
  vector<int> ans(nl + 1);
  for (auto const& [v, u, idx]: e)
    if (net.flow(idx)) ans[v] = u;
  for (int i(1); i <= nl; ++i)
    i == nl ? cout << ans[i] << endl : cout << ans[i] << ' ';
}
