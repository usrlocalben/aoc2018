#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>


using namespace std;

int serial;
const int DIM = 300;
const int INF = 999999;


const int level(int x, int y) {
	int rackId = x + 10;
	int pl = rackId * y;
	pl += serial;
	pl *= rackId;
	pl = (pl / 100) % 10;
	pl -= 5;
	return pl; }


int main() {
	cin >> serial;

	vector<int> cells(DIM*DIM, 0);
	for (int y=0; y<DIM; y++) {
		for (int x=0; x<DIM; x++) {
			cells[y*DIM+x] = level(x+1, y+1); }}

	vector<int> sums(DIM*DIM, 0);
	int bestX = -1;
	int bestY = -1;
	int best = -INF;
	for(int y=0; y<DIM-2; y++) {
		//cout << "." << flush;
		for(int x=0; x<DIM-2; x++) {
			int ax = 0;
			for (int sy=y; sy<y+3; sy++) {
				for (int sx=x; sx<x+3; sx++) {
					ax += cells[sy*DIM+sx]; }}
			if (ax > best) {
				best = ax;
				bestX = x;
				bestY = y; }}}

	cout << (bestX+1) << "," << (bestY+1) << "\n";
	//cout << cells[78*DIM+121] << "\n";
	return 0; }
