# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    inline namespace str {
      inline auto suffix_sort(string const& s) {
        vector<int> sa(s.size());
        vector<int> rk(s.size());
        vector<int> ht(s.size());
        if (s.empty()) return tuple(sa, rk, ht);
        vector<int> cnt(s.size());
        vector<int> tmp(s.size());
        auto const psum = [&] {
          cnt.assign(*max_element(rk.begin(), rk.end()) + 1, 0);
          for (int const rk: rk) ++cnt[rk];
          for (size_t i(1); i != cnt.size(); ++i) cnt[i] += cnt[i - 1];
        };
        copy(s.begin(), s.end(), rk.begin()), psum();
        for (size_t i(0); i != s.size(); ++i) sa[--cnt[rk[i]]] = i;
        for (int w(1); w == 1 || rk[sa.back()] != int(s.size() - 1); w <<= 1) {
          psum();
          auto const test = [&] (int const i) { tmp[--cnt[rk[i]]] = i; };
          for (auto i(sa.crbegin()); i != sa.crend(); ++i)
            if (*i >= w) test(*i - w);
          for (int i(1); i <= w; ++i) test(s.size() - i);
          auto const val = [&] (int const i)
          { return pair(rk[i], size_t(i + w) < s.size() ? rk[i + w] : -1); };
          sa.swap(tmp), tmp[sa[0]] = 0;
          for (auto i(next(sa.cbegin())); i != sa.cend(); ++i)
            tmp[*i] = tmp[*prev(i)] + (val(*i) != val(*prev(i)));
          rk.swap(tmp);
        }
        for (size_t i(0); i != s.size(); ++i) if (rk[i]) {
          ht[rk[i]] = i ? max(ht[rk[i - 1]] - 1, 0) : 0;
          while (s[i + ht[rk[i]]] == s[sa[rk[i] - 1] + ht[rk[i]]]) ++ht[rk[i]];
        }
        return tuple(sa, rk, ht);
      }
    }
  }
}

int main() {
  using namespace kh;
  string s;
  cin >> s;
  auto const [sa, rk, ht](suffix_sort(s));
  for (auto i(sa.cbegin()); i != sa.cend(); ++i)
    cout << *i + 1 << " \n"[next(i) == sa.cend()];
  cout.flush();
  // for (auto i(next(ht.cbegin())); i != ht.cend(); ++i)
  // cout << *i << " \n"[next(i) == ht.cend()];
  // cout.flush();
}
