# include <bits/stdc++.h>

namespace kh {
  using namespace std;
  inline namespace src {
    constexpr auto cmin = [] (auto& a, auto const& b)
    { return b < a ? a = b, true : false; };
    constexpr auto cmax = [] (auto& a, auto const& b)
    { return a < b ? a = b, true : false; };
  }
}
