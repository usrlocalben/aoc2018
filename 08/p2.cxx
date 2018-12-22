#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


pair<int, int> solve(const vector<int>& arr, int i) {
	int oi = i;
	int numChildren = arr[i];
	int metaSize = arr[i+1];
	i += 2;

	int ax = 0;
	if (numChildren > 0) {
		vector<int> vals;
		for (int n=0; n<numChildren; n++) {
			auto [consumed, amt] = solve(arr, i);
			vals.push_back(amt);
			i += consumed; }
		for (int n=0; n<metaSize; n++) {
			int idx = arr[i++] - 1;
			int sel;
			if (idx < 0) {
				sel = 0; }
			else if (idx >= vals.size()) {
				sel = 0; }
			else {
				sel = vals[idx]; }
			ax += sel; }}
	else {
		// leaf
		for (int n=0; n<metaSize; n++) {
			ax += arr[i++]; }}
	//cout << "i:" << oi << " ax:" << ax << "\n";
	return { i - oi, ax }; }


int main() {
	//vector<int> arr = { 2, 3, 0, 3, 10, 11, 12, 1, 1, 0, 1, 99, 2, 1, 1, 2 };

	vector<int> arr;
	int x;
	int mm = 0;
	while (cin >> x) {
		mm = max(mm, x);
		arr.push_back(x); }

	auto [consumed, amt] = solve(arr, 0);
	//cout << "consumed: " << consumed << "\n";
	cout << amt << "\n";
	return 0; }
