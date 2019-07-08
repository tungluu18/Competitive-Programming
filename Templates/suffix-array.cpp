#include <bits/stdc++.h>

using namespace std;

namespace suffix_array {
    #define vi vector<int>
    #define pi pair<int, int>

    template <typename T, typename Function>
    vector<T> radix_sort(vector<T> &_arr, int _range, Function val) {
        const int n = _arr.size();
        vi counter(_range, 0);
        vector<T> output(n);
        for (auto x: _arr) { counter[val(x)]++; }
        for (int i = 1; i < _range; ++i) { counter[i] += counter[i - 1]; }
        for (int i = n - 1; i >= 0; --i) { output[--counter[val(_arr[i])]] = _arr[i]; }
        return output;
    }

    int first_key(pair<pair<int, int>, int> a) { return a.first.first; }

    int second_key(pair<pair<int, int>, int> a) { return a.first.second + 1; }

    vi build_sa(const string &_s) {
        int n = _s.size();
        vi sa(n), rank(n);
        vector <pair<pair<int, int>, int>> keys(n);
        for (int i = 0; i < n; ++i) { keys[i] = {{int(_s[i] - '0'), 0}, i}; }
        sort(keys.begin(), keys.end());
        for (int k = 1; k <= n; k *= 2) {
            rank[keys[0].second] = 0;
            for (int i = 1; i < n; ++i) {
                rank[keys[i].second] = rank[keys[i-1].second];
                if (keys[i].first != keys[i-1].first) { rank[keys[i].second] += 1; }
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

    int pattern_search(const string &_s, const vi &_sa, const string &pat) {
        int l = 0, r = _s.length(), n = _s.length();
        for (int i = 0; i < pat.size(); ++i) {
            int sl, sr, sm, next_l, next_r;

            sl = l, sr = r;
            while (sl < sr) {
                sm = (sl + sr) / 2;
                if (_sa[sm] + i < n && _s[_sa[sm] + i] >= pat[i]) { sr = sm; }
                else { sl = sm + 1; }
            }
            next_l = sl;
            if (_s[_sa[next_l] + i] != pat[i]) { return -1; }

            sl = l, sr = r;
            while (sl < sr) {
                sm = (sl + sr + 1) / 2;
                if (_sa[sm] + i < n && _s[_sa[sm] + i] > pat[i]) { sr = sm - 1; }
                else { sl = sm; }
            }
            next_r = sr;

            l = next_l, r = next_r;
        }
        return _sa[l];
    }
} // namespace suffix_array

int main() {
    string s = "banana";
    vector<int> sa = suffix_array::build_sa(s);
    for (int i = 0; i < sa.size(); ++i) { cout << sa[i] << endl; }

    string pat = "anana";
    cout << suffix_array::pattern_search(s, sa, pat) << endl;
}
