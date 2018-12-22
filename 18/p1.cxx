#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


int main() {
	string line;
	vector<string> map;
	int width;
	bool first = true;
	string pad;
	while (getline(cin, line)) {
		if (first) {
			first = false;
			width = line.size();
			pad = string(int(width+2), ' ');
			map.push_back(pad); }
		line = " " + line + " ";
		map.push_back(line); }
	map.push_back(pad);

	vector<string> tmp = map;

	const int yBegin = 1;
	const int yEnd = map.size()-1;
	const int xBegin = 1;
	const int xEnd = width+1;

	const char GROUND = '.';
	const char TREES = '|';
	const char LUMBERYARD = '#';


	for (int n=0; n<10; n++) {
		for (int y=yBegin; y<yEnd; y++) {
			for (int x=xBegin; x<xEnd; x++) {

				const auto htype = map[y][x];

				int gCnt = 0;
				int tCnt = 0;
				int lCnt = 0;
				for (int yy=y-1; yy<=y+1; yy++) {
					for (int xx=x-1; xx<=x+1; xx++) {
						if (yy==y && xx==x) continue;
						if (map[yy][xx] == GROUND) {
							gCnt++; }
						else if (map[yy][xx] == TREES) {
							tCnt++; }
						else if (map[yy][xx] == LUMBERYARD) {
							lCnt++; }}}

				if (htype == GROUND) {
					tmp[y][x] = (tCnt >= 3 ? TREES : GROUND); }
				else if (htype == TREES) {
					tmp[y][x] = (lCnt >= 3 ? LUMBERYARD : TREES); }
				else if (htype == LUMBERYARD) {
					tmp[y][x] = ((lCnt>=1 && tCnt>=1) ? LUMBERYARD : GROUND); }}}
		//cout << "-----\n" << flush;

		//for (const auto& line : tmp) {
		//	cout << line << "\n"; }

		swap(map, tmp); }

	int tCnt = 0;
	int lCnt = 0;
	for (int y=yBegin; y<yEnd; y++) {
		for (int x=xBegin; x<xEnd; x++) {
			if (map[y][x] == TREES) {
				tCnt++; }
			else if (map[y][x] == LUMBERYARD) {
				lCnt++; }}}

	cout << (tCnt*lCnt) << "\n";
	return 0; }
