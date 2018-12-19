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
	int offset = -50;
	int ax = 0;
	for (int n=1; n<=10000; n++) {
		tmp = "..";
		for (int i=2; i<sz-2; i++) {
			chunk = initial.substr(i-2, 5);
			auto result = patterns.find(chunk)->second;
			tmp.push_back(result); }
		tmp += "..";
		cout << " " << n << ": " << tmp << "\n";
		initial = tmp.substr(1) + ".";
		offset++;

		ax = 0;
		{int num = offset;
		for (const auto ch : initial) {
			if (ch == '#') {
				ax += num; }
			num++; }}
		cout << offset << ", " << ax << "\n";}

	// eventually it stablizies
	// all plants shift +1 in each generation, or +72
	
	{int64_t n = 50000000000;
	n -= 10000;
	n *= 72;
	cout << ax + n << "\n";}
	return 0; }
