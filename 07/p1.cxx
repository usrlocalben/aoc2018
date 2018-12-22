#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


vector<string> split(const string& str, char ch) {
	vector<string> out;
	string src(str);
	auto match = src.find(ch);
	while (1) {
		auto item = src.substr(0, match);
		out.push_back(item);
		if (match == string::npos) {
			break; }
		src = src.substr(match + 1);
		match = src.find(ch); }
	return out; }


int main() {
	string line;
	unordered_set<char> nodes;
	vector<char> edges(26*26, 0);
	while (getline(cin, line)) {
		auto segments = split(line, ' ');
		char nn = segments[7][0] - 'A';
		char dn = segments[1][0] - 'A';
		nodes.insert(nn);
		nodes.insert(dn);
		edges[nn*26+dn] = 1; }

	vector<char> ready;
	while (!nodes.empty()) {
		ready.clear();
		for (const auto& node : nodes) {
			int linkCount = 0;
			for (int i=0; i<26; i++) {
				if (nodes.find(i)!=nodes.end() && edges[node*26+i]) {
					linkCount++; }}
			if (linkCount == 0) {
				ready.push_back(node); }}

		sort(ready.begin(), ready.end());
		auto node = ready.front();
		cout << char(node+'A');
		nodes.erase(node); }
	cout << "\n";
	return 0; }
