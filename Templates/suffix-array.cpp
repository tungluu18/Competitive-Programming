#include <bits/stdc++.h>

using namespace std;

namespace debug {
  #define vi vector<int>

  void vector_int(vi a) {
    for (auto &_ : a) cout << _ << " ";
    cout << endl;
  }

  void vector_pair(vector<pair<int, int>> _arr) {
    for (auto _ : _arr) cout <<"{" << _.first << ", " << _.second << "} ";
    cout << endl;
  }

  #undef vi
} // namespace debug

namespace suffix_array {
  #define vi vector<int>
  #define pi pair<int, int>

  template <typename T, typename Function>
  vector<T> radix_sort(vector<T> &_arr, int _range, Function val) {
    const int n = _arr.size();
    vi counter(_range, 0);
    vector<T> output(n);
    for (auto x: _arr) counter[val(x)]++;
    for (int i = 1; i < _range; ++i) counter[i] += counter[i - 1];
    for (int i = n - 1; i >= 0; --i) output[--counter[val(_arr[i])]] = _arr[i];
    return output;
  }

  int first_key(pair<pair<int, int>, int> a) { return a.first.first; }

  int second_key(pair<pair<int, int>, int> a) { return a.first.second + 1; }

  vi build_sa(const string &_s) {
    int n = _s.size();
    vi sa(n), rank(n);
    vector <pair<pair<int, int>, int>> keys(n);
    for (int i = 0; i < n; ++i) {
      keys[i].first.first = int(_s[i] - 'A');
      keys[i].first.second = 0;
      keys[i].second = i;
    }
    keys = radix_sort(keys, 100, first_key);
    for (int k = 1; k <= n; k *= 2) {
      rank[keys[0].second] = 0;
      for (int i = 1; i < n; ++i) {
        const pi prev_keys = keys[i-1].first;
        rank[keys[i].second] = rank[keys[i-1].second];
        if (keys[i].first != prev_keys) { rank[keys[i].second] += 1; }
      }
      for (int i = 0; i < n; ++i) {
        const int pos = keys[i].second;
        keys[i].first.first = rank[pos];
        keys[i].first.second = pos + k >= n ? -1 : rank[pos + k];
      }
      keys = radix_sort(keys, n + 1, second_key);
      keys = radix_sort(keys, n, first_key);
    }
    for (int i = 0; i < n; ++i) { sa[i] = keys[i].second; }
    return sa;
  }

  vi build_lcp(const string &_s, bool _have_sa = false, vi _sa = vi()) {
    if (!_have_sa) { _sa = build_sa(_s); }
    int n = _s.size();
    vi lcp;
    lcp.resize(n);
    return lcp;
  }

  #undef vi
  #undef pi
} // namespace suffix_array

int main() {
  string s;
  cin >> s;
  vector<int> sa = suffix_array::build_sa(s);
  for (int i = 0; i < sa.size(); ++i) { cout << sa[i] << endl; }
}
