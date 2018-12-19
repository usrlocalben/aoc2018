#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


pair<int, int> scana(const vector<int>& arr, int i) {
	int numChildren = arr[i];
	int metaSize = arr[i+1];
	int oi = i;
	i += 2;
	int ax = 0;
	while (numChildren--) {
		auto [consumed, amt] = scana(arr, i);
		ax += amt;
		i += consumed; }
	for (int n=0; n<metaSize; n++) {
		ax += arr[i++]; }
	return { i - oi, ax }; }


int main() {
	//vector<int> arr = { 2, 3, 0, 3, 10, 11, 12, 1, 1, 0, 1, 99, 2, 1, 1, 2 };

	vector<int> arr;
	int x;
	int mm = 0;
	while (cin >> x) {
		mm = max(mm, x);
		arr.push_back(x); }

	auto [consumed, amt] = scana(arr, 0);
	cout << "consumed: " << consumed << "\n";
	cout << "amt: " << amt << "\n";
	return 0; }
