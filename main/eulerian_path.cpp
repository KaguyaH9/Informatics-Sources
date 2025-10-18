# include <bits/stdc++.h>

int main() {
  using namespace std;
  int t;
  cin >> t;
  int n, m;
  cin >> n >> m;
  vector<int> tail(m);
  vector<int> head(m);
  vector<int> vis(m);
  vector<vector<int>> ss(n + 1);
  vector<vector<int>> tt(n + 1);
  for (int i(0); i != m; ++i) {
    cin >> tail[i] >> head[i];
    switch (t) {
      case 1:
        tt[tail[i]].push_back(i);
        tt[head[i]].push_back(i);
        break;
      case 2:
        tt[tail[i]].push_back(i);
        ss[head[i]].push_back(i);
        break;
    }
  }
  switch (int sum(0); t) {
    case 1:
      for (int i(1); i <= n; ++i)
        sum += tt[i].size() % 2;
      if (sum <= 0) break;
      else return cout << "NO" << endl, 0;
    case 2:
      for (int i(1); i <= n; ++i)
        sum += abs(int(ss[i].size() - tt[i].size()));
      if (sum <= 0) break;
      else return cout << "NO" << endl, 0;
  }
  auto const end = [&] (int const i, int const x)
  { return tail[i] ^ head[i] ^ x; };
  auto const index = [&] (int const i, int const x)
  { return x == tail[i] ? +(i + 1) : -(i + 1); };
  vector<int> res;
  function<void(int)>
    se = [&] (int const x) {
      while (!tt[x].empty()) {
        int const i(tt[x].back());
        tt[x].pop_back();
        if (vis[i]) continue;
        else vis[i] = 1;
        se(end(i, x));
        res.push_back(index(i, x));
      }
    };
  for (int i(1); i <= n; ++i)
    if (!tt[i].empty()) {
      se(i);
      reverse(res.begin(), res.end());
      break;
    }
  if (find(vis.begin(), vis.end(), 0) != vis.end())
    cout << "NO" << endl;
  else {
    cout << "YES" << endl, assert(res.size() == size_t(m));
    for (int i(0); i != m; ++i) cout << res[i] << " \n"[i == m - 1];
    cout.flush();
  }
}
