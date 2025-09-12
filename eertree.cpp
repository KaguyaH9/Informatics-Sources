# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    class eertree {
      struct node {
        int tr[26], len, link;
        int dep;
        node(int const len): tr(), len(len), link(-1), dep() {}
      };
      vector<node> v;
      deque<char> s;
      int head, last;
      long ne;
      template <typename... T>
        int newnode(T const&... args)
        { return v.emplace_back(args...), v.size() - 1; }
      public:
      eertree()
        : v{ 0, -1 }, s{ '\0', '\0' }, head(1), last(1), ne()
        { v[0].link = 1; }
      eertree(string const& s)
        : eertree()
      { push_back(s); }
      int length() const { return s.size() - 2; }
      int push_back(char const c) {
        s.insert(prev(s.end()), c);
        while (s[s.size() - v[last].len - 3] != c)
          last = v[last].link;
        if (!v[last].tr[c - 'a']) {
          int const tr(newnode(v[last].len + 2));
          v[last].tr[c - 'a'] = tr;
          if (last == 1) v[tr].link = 0;
          else {
            v[tr].link = v[last].link;
            while (s[s.size() - v[v[tr].link].len - 3] != c)
              v[tr].link = v[v[tr].link].link;
            v[tr].link = v[v[tr].link].tr[c - 'a'];
          }
          v[tr].dep = v[v[tr].link].dep + 1;
        }
        ne += v[last = v[last].tr[c - 'a']].dep;
        if (v[last].len == length()) head = last;
        return v[last].dep;
      }
      int push_front(char const c) {
        s.insert(next(s.begin()), c);
        while (s[2 + v[head].len] != c)
          head = v[head].link;
        if (!v[head].tr[c - 'a']) {
          int const tr(newnode(v[head].len + 2));
          v[head].tr[c - 'a'] = tr;
          if (head == 1) v[tr].link = 0;
          else {
            v[tr].link = v[head].link;
            while (s[2 + v[v[tr].link].len] != c)
              v[tr].link = v[v[tr].link].link;
            v[tr].link = v[v[tr].link].tr[c - 'a'];
          }
          v[tr].dep = v[v[tr].link].dep + 1;
        }
        ne += v[head = v[head].tr[c - 'a']].dep;
        if (v[head].len == length()) last = head;
        return v[head].dep;
      }
      void push_back(string const& s)
      { for (char const c: s) push_back(c); }
      void push_front_rev(string const& s)
      { for (char const c: s) push_front(c); }
      void push_front(string const& s)
      { push_front_rev(string(s.rbegin(), s.rend())); }
      long cnt_palin_subs() const { return ne; }
    };
  }
}

int main() {
  using namespace kh;
  string s;
  cin >> s;
  eertree pam;
  vector ans(1, 0);
  for (char& c: s) {
    c = (c - 97 + ans.back()) % 26 + 97;
    ans.push_back(pam.push_back(c));
  }
  ans.erase(ans.begin());
  for (auto i(ans.cbegin()); i != ans.cend(); ++i)
    cout << *i << " \n"[next(i) == ans.cend()];
  cout.flush();
}
