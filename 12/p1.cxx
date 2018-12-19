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
	string initial;
	getline(cin, initial);
	initial = initial.substr(15);

	string line;
	getline(cin, line);  // skip blank line

	unordered_map<string, char> patterns;

	while (getline(cin, line)) {
		auto segments = split(line, ' ');
		patterns[segments[0]] = segments[2][0]; }

	initial.insert(initial.begin(), 50, '.');
	initial.append(50, '.');
	cout << " 0: " << initial << "\n";
	//

	const int sz = initial.length();
	string tmp;
	string chunk;
	for (int n=1; n<=20; n++) {
		tmp = "..";
		for (int i=2; i<sz-2; i++) {
			chunk = initial.substr(i-2, 5);
			auto result = patterns.find(chunk)->second;
			tmp.push_back(result); }
		tmp += "..";
		cout << " " << n << ": " << tmp << "\n";
		initial = tmp; }

	int ax = 0;
	int num = -50;
	for (const auto ch : initial) {
		if (ch == '#') {
			ax += num; }
		num++; }

	cout << ax << "\n";
	return 0; }
