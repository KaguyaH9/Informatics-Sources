# include <bits/stdc++.h>

int main() {
  using namespace std;
  default_random_engine eng;
  uniform_int_distribution<uint64_t> randint;
  int n;
  cin >> n;
  vector<pair<int, int>> e(n - 1);
  vector<vector<int>> nn(n + 1);
  for (auto& [a, b]: e) {
    cin >> a >> b;
    nn[a].push_back(b);
    nn[b].push_back(a);
  }
  vector<uint64_t> val(n + 1);
  for (uint64_t& val: val) val = randint(eng);
  vector<int> size(n + 1);
  vector<uint64_t> hash(n + 1);
  function<void(int, int)>
    se = [&] (int const g, int const m) {
      size[g] = 1, hash[g] = 0;
      for (int const d: nn[g]) if (d != m) {
        se(d, g);
        size[g] += size[d];
        hash[g] += hash[d];
      }
      hash[g] ^= val[size[g]];
    };
  se(1, 0);
  cout << unordered_set(next(hash.begin()), hash.end()).size() << endl;
}
