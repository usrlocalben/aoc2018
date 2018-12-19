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
	vector<char> scores; scores.reserve(1000000);
	int ai = 0;
	int bi = 1;
	scores.push_back(3);
	scores.push_back(7);

	while (1) {
		int s = scores[ai] + scores[bi];

		int x = s/10;
		int y = s%10;
		if (x) {
			scores.push_back(x); 
			if (scores.size() >= 6 && scores.back() == 1) {
				if ((scores[scores.size()-2] == 7) &&
					(scores[scores.size()-3] == 9) &&
					(scores[scores.size()-4] == 0) &&
					(scores[scores.size()-5] == 3) &&
					(scores[scores.size()-6] == 4)) {
					cout << scores.size() - 6 << "\n";
					break;}}}
		scores.push_back(y);
		if (scores.size() >= 6 && scores.back() == 1) {
			if ((scores[scores.size()-2] == 7) &&
			    (scores[scores.size()-3] == 9) &&
			    (scores[scores.size()-4] == 0) &&
			    (scores[scores.size()-5] == 3) &&
			    (scores[scores.size()-6] == 4)) {
				cout << scores.size() - 6 << "\n";
				break;}}

		int askip = 1 + scores[ai];
		int bskip = 1 + scores[bi];
		ai = (ai+askip) % scores.size();
		bi = (bi+bskip) % scores.size(); }

	return 0; }
