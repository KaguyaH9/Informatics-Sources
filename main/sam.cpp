# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    class sam {
      struct node {
        int tr[26], len, link;
        bool pre; int nep;
        vector<int> d;
        node(): tr(), len(), link(), pre(), nep(), d() {}
        node(int const len): tr(), len(len), link(), pre(), nep(), d() {}
        node(int const (&tr)[26], int const len, int const link):
          tr(), len(len), link(link), pre(), nep(), d()
        { memcpy(this->tr, tr, sizeof(tr)); }
      };
      vector<node> v;
      template <typename... T>
        int newnode(T const&... args)
        { return v.emplace_back(args...), v.size() - 1; }
      int extend(int lst, char const c) {
        int const cur(newnode(v[lst].len + 1));
        v[cur].pre = true;
        while (!v[lst].tr[c - 'a']) {
          v[lst].tr[c - 'a'] = cur;
          lst = v[lst].link;
        }
        int const tr(v[lst].tr[c - 'a']);
        if (tr == cur) return cur;
        if (v[tr].len == v[lst].len + 1) return v[cur].link = tr, cur;
        int const clone(newnode(v[tr].tr, v[lst].len + 1, v[tr].link));
        v[cur].link = v[tr].link = clone;
        while (v[lst].tr[c - 'a'] == tr) {
          v[lst].tr[c - 'a'] = clone;
          lst = v[lst].link;
        }
        return cur;
      }
      public:
      sam(): v(1) {}
      sam(string const& s): sam() {
        int o(0);
        for (char const c: s) o = extend(o, c);
        for (size_t i(1); i != v.size(); ++i)
          v[v[i].link].d.push_back(i);
        function<void(int)> se = [this, &se] (int const g) {
          v[g].nep = v[g].pre;
          for (int const d: v[g].d) se(d), v[g].nep += v[d].nep;
        };
        se(0);
      }
      long f0() {
        long res(0);
        for (node const& v: v) if (v.nep != 1)
          res = max(res, 1l * v.nep * v.len);
        return res;
      }
    };
    class gsam {
      struct node {
        int tr[26], len, link;
        int pre; int nep;
        vector<int> d;
        node(): tr(), len(), link(), pre(), nep(), d() {}
        node(int const len): tr(), len(len), link(), pre(), nep(), d() {}
        node(int const (&tr)[26], int const len, int const link):
          tr(), len(len), link(link), pre(), nep(), d()
        { memcpy(this->tr, tr, sizeof(tr)); }
      };
      vector<node> v;
      template <typename... T>
        int newnode(T const&... args)
        { return v.emplace_back(args...), v.size() - 1; }
      int extend(int lst, char const c) {
        if (v[lst].tr[c - 'a']) {
          int const tr(v[lst].tr[c - 'a']);
          if (v[tr].len == v[lst].len + 1) return ++v[tr].pre, tr;
          int const clone(newnode(v[tr].tr, v[lst].len + 1, v[tr].link));
          v[tr].link = clone;
          while (v[lst].tr[c - 'a'] == tr) {
            v[lst].tr[c - 'a'] = clone;
            lst = v[lst].link;
          }
          return ++v[clone].pre, clone;
        }
        int const cur(newnode(v[lst].len + 1));
        ++v[cur].pre;
        while (!v[lst].tr[c - 'a']) {
          v[lst].tr[c - 'a'] = cur;
          lst = v[lst].link;
        }
        int const tr(v[lst].tr[c - 'a']);
        if (tr == cur) return cur;
        if (v[tr].len == v[lst].len + 1) return v[cur].link = tr, cur;
        int const clone(newnode(v[tr].tr, v[lst].len + 1, v[tr].link));
        v[cur].link = v[tr].link = clone;
        while (v[lst].tr[c - 'a'] == tr) {
          v[lst].tr[c - 'a'] = clone;
          lst = v[lst].link;
        }
        return cur;
      }
      public:
      gsam(): v(1) {}
      gsam(string const& s): gsam() {
        int o(0);
        for (char const c: s) o = extend(o, c);
        for (size_t i(1); i != v.size(); ++i)
          v[v[i].link].d.push_back(i);
        function<void(int)> se = [this, &se] (int const g) {
          v[g].nep = v[g].pre;
          for (int const d: v[g].d) se(d), v[g].nep += v[d].nep;
        };
        se(0);
      }
      gsam(vector<string> const& s): gsam() {
        for (string const& s: s) {
          int o(0);
          for (char const c: s) o = extend(o, c);
        }
        for (size_t i(1); i != v.size(); ++i)
          v[v[i].link].d.push_back(i);
        function<void(int)> se = [this, &se] (int const g) {
          v[g].nep = v[g].pre;
          for (int const d: v[g].d) se(d), v[g].nep += v[d].nep;
        };
        se(0);
      }
      long f1() const {
        long res(0);
        for (node const& u: v)
          res += u.len - v[u.link].len;
        return res;
      }
      int f2() const { return v.size(); }
    };
  }
}

int main() {
  using namespace std;
  using namespace kh;
  int n;
  cin >> n;
  vector<string> s(n);
  for (string& s: s) cin >> s;
  gsam gsam(s);
  cout << gsam.f1() << endl;
  cout << gsam.f2() << endl;
}
