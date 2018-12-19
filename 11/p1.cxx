#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

const int serial = 4151;

using namespace std;


const int level(int x, int y) {
	int rackId = x + 10;
	int pl = rackId * y;
	pl += serial;
	pl *= rackId;
	pl = (pl / 100) % 10;
	pl -= 5;
	return pl; }


int main() {
	vector<int> cells(300*300, 0);
	for (int y=0; y<300; y++) {
		cout << "." << flush;
		for (int x=0; x<300; x++) {
			cells[y*300+x] = level(x+1, y+1); }}

	vector<int> sums(300*300, 0);
	int bestX = -1;
	int bestY = -1;
	int best = -999999;

	for(int y=0; y<300-2; y++) {
		cout << "." << flush;
		for(int x=0; x<300-2; x++) {
			int ax = 0;
			for (int sy=y; sy<y+3; sy++) {
				for (int sx=x; sx<x+3; sx++) {
					ax += cells[sy*300+sx]; }}
			if (ax > best) {
				best = ax;
				bestX = x;
				bestY = y; }}}

	cout << "bx:" << (bestX+1) << ", by:" << (bestY+1) << "\n";
	//cout << cells[78*300+121] << "\n";
	return 0; }
