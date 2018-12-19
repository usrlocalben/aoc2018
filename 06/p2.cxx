#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct ivec2 {
	int x, y; };

ivec2 vmin(ivec2 a, ivec2 b) {
	return ivec2{ min(a.x, b.x), min(a.y, b.y) }; }
ivec2 vmax(ivec2 a, ivec2 b) {
	return ivec2{ max(a.x, b.x), max(a.y, b.y) }; }

ostream& operator<<(ostream& stream, ivec2 item) {
	stream << "(" << item.x << ", " << item.y << ")";
	return stream; }

ivec2 operator-(ivec2 lhs, ivec2 rhs) {
	return ivec2{ lhs.x - rhs.x, lhs.y - rhs.y }; }
ivec2 operator+(ivec2 lhs, ivec2 rhs) {
	return ivec2{ lhs.x + rhs.x, lhs.y + rhs.y }; }

struct Rect {
	ivec2 left_top;
	ivec2 right_bottom;
	int area() const {
		return ((right_bottom.x - left_top.x) *
			(right_bottom.y - left_top.y)); } };


int mdistance(ivec2 a, ivec2 b) {
	return abs(b.x-a.x) + abs(b.y-a.y); }


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
	string line;
	ivec2 left_top{ 99999, 99999 };
	vector<ivec2> points;

	while (getline(cin, line)) {
		auto nums = split(line, ' ');
		auto pos = ivec2{ stoi(nums[0]), stoi(nums[1]) };
		left_top = vmin(left_top, pos);
		points.push_back(pos); }

	cout << "leftTop: " << left_top << "\n";

	ivec2 right_bottom{ 0, 0 };
	for (auto& point : points) {
		point = point - left_top;
		right_bottom = vmax(right_bottom, point); }

	cout << "rightBottom: " << right_bottom << "\n";
	auto dim = right_bottom + ivec2{1,1};

	vector<int> space(dim.x*dim.y, 0);
	const int limit = 10000;
	int regionSize = 0;
	for (int y=0; y<dim.y; y++) {
		for (int x=0; x<dim.x; x++) {
			ivec2 pos{x, y};
			auto& ax = space[y*dim.x + x];
			for (const auto& point : points) {
				ax += mdistance(pos, point); }
			if (ax < limit) {
				regionSize++; }}}

	cout << regionSize << "\n";
	return 0; }
