// Luogu P5357

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    template <int M>
      constexpr int pow(int x, int n) {
        int y(1);
        while (n) {
          y = n & 1 ? 1l * y * x % M : y;
          x = 1l * x * x % M, n >>= 1;
        }
        return y;
      }
    class acam {
      struct node {
        int tr[26], link, next[26], cnt;
        node(): tr(), link(), next(), cnt() {}
      };
      vector<string> s;
      vector<node> v;
      vector<int> ord;
      int newnode() { return v.emplace_back(), v.size() - 1; }
      auto insert(string const& s) {
        vector<int> path(1, 0);
        for (int const c: s) {
          if (!v[path.back()].tr[c - 'a'])
            v[path.back()].tr[c - 'a'] = newnode();
          path.push_back(v[path.back()].tr[c - 'a']);
        }
        return path;
      }
      auto find(string const& s) const {
        vector<int> path(1, 0);
        for (int const c: s) {
          assert(v[path.back()].tr[c - 'a']);
          path.push_back(v[path.back()].tr[c - 'a']);
        }
        return path;
      }
      auto run(string const& s) const {
        vector<int> path(1, 0);
        for (int const c: s)
          path.push_back(v[path.back()].next[c - 'a']);
        return path;
      }
      public:
      acam(vector<string> const& s): s(s), v(1) {
        for (string const& s: s) ++v[insert(s).back()].cnt;
        size_t cur(0);
        ord.push_back(0);
        while (cur != ord.size()) {
          int const x(ord[cur++]);
          for (int i(0); i != 26; ++i) {
            if (!v[x].tr[i])
              v[x].next[i] = v[v[x].link].next[i];
            else {
              v[x].next[i] = v[x].tr[i];
              v[v[x].tr[i]].link = x ? v[v[x].link].next[i] : 0;
              ord.push_back(v[x].tr[i]);
            }
          }
        }
      }
      auto operator()(string const& t) const {
        vector<int> sum(v.size());
        sum[0] = 1;
        for (int const x: run(t)) ++sum[x];
        for (auto i(ord.rbegin()); *i; ++i)
          sum[v[*i].link] += sum[*i];
        vector<int> ans;
        for (string const& s: s)
          ans.push_back(sum[find(s).back()]);
        return ans;
      }
    };
  }
}

int main() {
  using namespace std;
  using namespace kh;
  int n;
  cin >> n;
  vector<string> t(n);
  for (string& t: t) cin >> t;
  string s;
  cin >> s;
  auto const ans(acam(t)(s));
  for (int const ans: ans) cout << ans << endl;
}
