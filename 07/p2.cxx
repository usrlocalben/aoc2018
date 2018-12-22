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

	const int W = 4;
	vector<pair<int, int>> workers;
	vector<pair<int, int>> tmpworkers;

	int t = 0;
	vector<char> ready;
	unordered_set<char> pending;
	while (1) {

		tmpworkers.clear();
		pending.clear();
		for (auto& worker:workers) {
			if (--worker.second > 0) {
				pending.insert(worker.first);
				tmpworkers.push_back(worker); }
			else {
				nodes.erase(worker.first); }}
		swap(tmpworkers, workers);

		if (workers.empty() && nodes.empty()) {
			// workers idle and nothing left to do
			break; }

		int workersAvailable = W - workers.size();
		//cout << "wa:" << workersAvailable << "\n";
		for (int www=0; www<workersAvailable; www++) {
			ready.clear();
			for (const auto& node : nodes) {
				if (pending.find(node) != pending.end()) {
					continue; }
				int linkCount = 0;
				for (int i=0; i<26; i++) {
					if (nodes.find(i)!=nodes.end() && edges[node*26+i]) {
						linkCount++; }}
				if (linkCount == 0) {
					ready.push_back(node); }}

			sort(ready.begin(), ready.end());
			if (ready.empty()) {
				break; }

			auto node = ready.front();
			int timeNeeded = 60 + node + 1;
			workers.push_back({ node, timeNeeded });
			pending.insert(node); }

		/*cout << "T:" << t << " ";
		for (const auto& w :workers) {
			cout << char(w.first+'A') << " "; }
		cout << "\n";*/
		t++; }

	cout << t << "\n";
	return 0; }
