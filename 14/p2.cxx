#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


int main() {
	vector<char> sequence;
	int x;
	cin >> x;
	while (x) {
		sequence.insert(sequence.begin(), x%10);
		x /= 10;}

	vector<char> scores; scores.reserve(1000000);

	auto backMatch = [&]() {
		if (scores.size() >= sequence.size()) {
			for (int i=0; i<sequence.size(); i++) {
				if (scores[scores.size()-1-i] != sequence[sequence.size()-1-i]) {
					return false; }}
			return true;}
		return false;};

	int ai = 0;
	scores.push_back(3);
	int bi = 1;
	scores.push_back(7);
	while (1) {
		int s = scores[ai] + scores[bi];

		int x = s/10;
		int y = s%10;
		if (x) {
			scores.push_back(x); 
			if (backMatch()) {
				cout << scores.size() - 6 << "\n";
				break;}}
		scores.push_back(y);
		if (backMatch()) {
			cout << scores.size() - 6 << "\n";
			break;}

		int askip = 1 + scores[ai];
		int bskip = 1 + scores[bi];
		ai = (ai+askip) % scores.size();
		bi = (bi+bskip) % scores.size(); }

	return 0; }
