#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

const int WANTED = 10;


int main() {
	int startAt;
	cin >> startAt;

	vector<char> scores; scores.reserve(startAt+WANTED);

	int ai = 0;
	scores.push_back(3);
	int bi = 1;
	scores.push_back(7);

	while (scores.size() < startAt+WANTED) {
		int s = scores[ai] + scores[bi];

		int x = s/10;
		int y = s%10;
		if (x) {
			scores.push_back(x); }
		scores.push_back(y);

		int askip = 1 + scores[ai];
		int bskip = 1 + scores[bi];
		ai = (ai+askip) % scores.size();
		bi = (bi+bskip) % scores.size(); }

	for (int idx=scores.size()-WANTED; idx<scores.size(); idx++) {
		cout << int(scores[idx]); }
	cout << "\n";
	return 0; }
