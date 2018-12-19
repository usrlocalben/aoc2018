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
	ivec2 left_top;
	ivec2 right_bottom; };

struct Claim {
	int id;
	Rect rect; };

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


int main() {

	vector<int> sheet(1000*1000, 0);
	string line;
	while (getline(cin, line)) {
		Claim c = parseClaim(line);

		for (int y=c.rect.left_top.y; y<c.rect.right_bottom.y; y++) {
			for (int x=c.rect.left_top.x; x<c.rect.right_bottom.x; x++) {
				sheet[y*1000 + x]++; }}}

	int ax = 0;
	for (int y=0; y<1000; y++) {
		for (int x=0; x<1000; x++) {
			if (sheet[y*1000+x] > 1) {
				ax += 1; }}}

	cout << ax << "\n";
	return 0; }
