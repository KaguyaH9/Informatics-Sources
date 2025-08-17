// LibreOJ #103

# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    class kmp {
      string s;
      vector<int> pi;
      public:
      kmp(string const& s): s(s), pi(s.length() + 1) {
        for (int i(1); i < int(s.length()); ++i) {
          pi[i + 1] = pi[i];
          while (pi[i + 1] && s[pi[i + 1]] != s[i])
            pi[i + 1] = pi[pi[i + 1]];
          pi[i + 1] += s[pi[i + 1]] == s[i];
        }
      }
      int operator()(string const& t) const {
        int res(0);
        for (int i(0), j(0); i != int(t.length()); ++i) {
          while (j && s[j] != t[i]) j = pi[j];
          res += (j += s[j] == t[i]) == int(s.length());
        }
        return res;
      }
    };
  }
}

int main() {
  using namespace std;
  using namespace kh;
  string a, b;
  cin >> a >> b;
  cout << kmp(b)(a) << endl;
}
