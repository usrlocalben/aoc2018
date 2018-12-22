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
	int numChildren = arr[i];
	int metaSize = arr[i+1];
	int oi = i;
	i += 2;
	int ax = 0;
	while (numChildren--) {
		auto [consumed, amt] = solve(arr, i);
		ax += amt;
		i += consumed; }
	for (int n=0; n<metaSize; n++) {
		ax += arr[i++]; }
	return { i - oi, ax }; }


int main() {
	vector<int> arr;
	int x;
	while (cin >> x) {
		arr.push_back(x); }

	const auto [consumed, amt] = solve(arr, 0);
	//cout << "consumed: " << consumed << "\n";
	cout << amt << "\n";
	return 0; }
