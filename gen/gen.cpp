# include <bits/stdc++.h>

int main() {
  using namespace std;
  namespace fs = filesystem;
  freopen("output/sources.tex", "w", stdout);
  fs::path path("main");
  auto const cat = [] (auto const& entry) {
    ifstream fin(entry.path());
    string line;
    while (getline(fin, line))
      puts(line.c_str());
  };
  auto const cvt = [] (string filename) {
    for (size_t i(filename.size() - 1); ~i; --i)
      if (filename[i] == '_')
        filename.insert(next(filename.begin(), i), '\\');
    return filename;
  };
  puts("\\documentclass[a4paper]{article}");
  putchar('\n');
  puts("\\usepackage[a4paper, left=1in, right=1in, top=1in, bottom=1in]{geometry}");
  putchar('\n');
  puts("\\begin{document}");
  putchar('\n');
  puts("\\small");
  for (auto const& entry: fs::directory_iterator(path)) {
    putchar('\n');
    printf("\\section{%s}\n", cvt(entry.path().filename().string()).c_str());
    putchar('\n');
    puts("\\begin{verbatim}");
    cat(entry);
    puts("\\end{verbatim}");
    putchar('\n');
    puts("\\clearpage");
    fflush(stdout);
  }
  putchar('\n');
  puts("\\end{document}");
}
