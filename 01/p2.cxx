#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
	unordered_set<int> seen;
	vector<int> nums;

	{int x;
	while (cin >> x) {
		nums.push_back(x); }}

	int ax = 0;
	seen.insert(0);
	int idx = 0;
	while (1) {
		ax += nums[idx];
		if (auto search = seen.find(ax); search != seen.end()) {
			cout << ax << "\n";
			return 0; }
		else {
			seen.insert(ax); }
		idx = (idx+1)%nums.size();}

	cout << "not found\n";
	return 1; }
