#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

pair<int, string> diff(const string& ta, const string& tb) {
	string out;
	int ax = 0;
	for (int i=0; i<ta.size(); i++) {
		if (ta[i] == tb[i]) {
			out.push_back(ta[i]); }
		else {
			ax += 1; }}
	return {ax, out};}


int main() {
	vector<string> arr;
	{string line;
	while (getline(cin, line)) {
		arr.push_back(line); }}

	for (int ai=0; ai<arr.size(); ai++) {
		for (int bi=ai+1; bi<arr.size(); bi++) {
			const auto& ta = arr[ai];
			const auto& tb = arr[bi];
			auto [d, sames] = diff(ta, tb);
			if (d == 1) {
				cout << sames << "\n";
				return 0; }}}

	cout << "not found\n";
	return 1; }
