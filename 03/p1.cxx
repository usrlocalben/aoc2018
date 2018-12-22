#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct ivec2 {
	int x, y; };


struct Rect {
	ivec2 leftTop;
	ivec2 rightBottom; };


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


struct Claim {
	int id;
	Rect rect; };


Claim parseClaim(const string& text) {
	auto segments = split(text, ' ');

	// segment0 = "#999"
	int id = stoi(segments[0].substr(1));

	// segment1 = "@", unused
	// ...
	
	// segment 2 = "3,1:" xy pos
	auto tmp = split(segments[2], ',');
	int x = stoi(tmp[0]);
	int y = stoi(tmp[1]);

	// segment 3 = "4x4"
	tmp = split(segments[3], 'x');
	int width = stoi(tmp[0]);
	int height = stoi(tmp[1]);

	Rect r{
		ivec2{ x, y },
		ivec2{ x + width, y + height } };
	Claim c{ id, r };
	return c; }


const int DIM = 1000;


int main() {
	vector<int> sheet(DIM*DIM, 0);
	string line;
	while (getline(cin, line)) {
		Claim c = parseClaim(line);

		for (int y=c.rect.leftTop.y; y<c.rect.rightBottom.y; y++) {
			for (int x=c.rect.leftTop.x; x<c.rect.rightBottom.x; x++) {
				sheet[y*DIM + x]++; }}}

	int ax = 0;
	for (const auto& cell : sheet) {
		if (cell > 1) {
			ax++; }}

	cout << ax << "\n";
	return 0; }
