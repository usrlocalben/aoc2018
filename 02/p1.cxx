#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


pair<int, int> freq(const string& text) {
	static unordered_map<char, int> tab;
	tab.clear();
	for (const auto ch : text) {
		tab[ch] += 1; }
	int ax2 = 0;
	int ax3 = 0;
	for (const auto& p : tab) {
		if (p.second == 2) ax2++;
		if (p.second == 3) ax3++; }
	return { ax2?1:0, ax3?1:0 };}


int solution(const vector<string>& arr) {
	int ax2 = 0;
	int ax3 = 0;
	for (const auto& text : arr) {
		auto result = freq(text);
		ax2 += result.first;
		ax3 += result.second; }
	return ax2 * ax3; }

	
int main() {
	vector<string> arr;
	{string line;
	while (getline(cin, line)) {
		arr.push_back(line); }}
	auto result = solution(arr);
	cout << result << "\n";
	return 0; }
