#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


int findReaction(const string& text, int begin) {
	for (int i=begin; i<text.size()-1; i++) {
		const auto a = text[i];
		const auto b = text[i+1];
		if ((tolower(a) == tolower(b)) &&
			(islower(a) != islower(b))) {
			return i; }}
	return -1; }


int main() {
	string lineSrc;
	cin >> lineSrc;
	//lineSrc = "dabAcCaCBAcCcaDA";

	int best = 50000;

	string line;
	for (char ig='a'; ig<='z'; ig++) {
		line = "";
		for (const auto ch : lineSrc) {
			if (tolower(ch) != ig) {
				line += ch; }}

		int sp = 0;
		while (1) {
			int rpos = findReaction(line, sp);
			if (rpos == -1) {
				break; }
			line = line.substr(0, rpos) + line.substr(rpos + 2, line.size());
			sp = max(rpos - 1, 0); }
		cout << ig << flush;
		
		best = min(best, int(line.size())); }

	cout << best << "\n";
	return 0; }
