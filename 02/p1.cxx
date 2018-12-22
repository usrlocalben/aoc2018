#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


pair<bool, bool> freq(const string& text) {
	static unordered_map<char, int> tab;
	tab.clear();
	for (const auto ch : text) {
		tab[ch] += 1; }
	bool ax2 = false;
	bool ax3 = false;
	for (const auto& p : tab) {
		if (p.second == 2) ax2 = true;
		if (p.second == 3) ax3 = true;}
	return { ax2, ax3 };}


int main() {
	vector<string> arr;
	{string line;
	while (getline(cin, line)) {
		arr.push_back(line); }}

	int ax2 = 0;
	int ax3 = 0;
	for (const auto& text : arr) {
		auto result = freq(text);
		ax2 += result.first;
		ax3 += result.second; }

	cout << (ax2*ax3) << "\n";
	return 0; }
