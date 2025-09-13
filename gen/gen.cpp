# include <bits/stdc++.h>

int main() {
  using namespace std;
  namespace fs = filesystem;
  fs::path path(".");
  auto const cat = [] (auto const& entry) {
    ifstream fin(entry.path());
    string line;
    while (getline(fin, line))
      cout << line << endl;
  };
  for (auto const& entry: fs::directory_iterator(path)) {
    if (entry.path().filename().string().front() == '.') continue;
    if (entry.path().filename().string() == "gen") continue;
    if (entry.path().filename().string() == "output") continue;
    cout << "##" << ' ' << entry.path().filename().string() << endl;
    cout << endl;
    cout << "```" << endl;
    cat(entry);
    cout << "```" << endl;
    cout << endl;
    cout << "<div style=\"page-break-after: always;\"></div>" << endl;
    cout << endl;
  }
}
