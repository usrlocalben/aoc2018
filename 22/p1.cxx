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

#define sz(x) (int(x.size()))
#define forn(i,n) for(int i=0;i<int(n);i++)


struct ivec2 {
	int x, y;

	ivec2& operator+=(ivec2 rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this; } };

ivec2 vmin(ivec2 a, ivec2 b) { return ivec2{ min(a.x, b.x), min(a.y, b.y) }; }
ivec2 vmax(ivec2 a, ivec2 b) { return ivec2{ max(a.x, b.x), max(a.y, b.y) }; }

int area(ivec2 a) { return a.x * a.y; }

const auto UP = ivec2{0,-1};
const auto DOWN = ivec2{0,1};
const auto LEFT = ivec2{-1,0};
const auto RIGHT = ivec2{1,0};

ostream& operator<<(ostream& stream, ivec2 item) {
	stream << "(" << item.x << ", " << item.y << ")";
	return stream; }

ivec2 operator-(ivec2 a, ivec2 b) { return ivec2{ a.x-b.x, a.y-b.y }; }
ivec2 operator+(ivec2 a, ivec2 b) { return ivec2{ a.x+b.x, a.y+b.y }; }
ivec2 operator*(ivec2 a, ivec2 b) { return ivec2{ a.x*b.x, a.y*b.y }; }

bool operator==(ivec2 a, ivec2 b) { return (a.x==b.x && a.y==b.y); }


struct Rect {
	ivec2 leftTop;
	ivec2 rightBottom; };


/* bfs
	dequeue<pair<XXX, int>> queue;
	unordered_set<XXX> visited;
	queue.push_back({ xxx, 0 });
	while (!queue.empty()) {
		const auto[hpos, hdist] = queue.front();  queue.pop_front();
		if (auto already = visited.find(hpos); already != visited.end()) { continue; }
		visited.insert(hpos);
		queue.push_back({ xxx, hdist+1 }); }
*/


ostream& operator<<(ostream& stream, vector<int> nums) {
	bool first = true;
	for (const auto& num : nums) {
		if (first) {
			stream << "[" << num;
			first = false; }
		else {
			stream << ", " << num; }}
	stream << "]";
	return stream; }



std::vector<std::string> split(const std::string& str, char ch) {
	std::vector<std::string> items;
	std::string src(str);
	auto nextmatch = src.find(ch);
	while (1) {
		auto item = src.substr(0, nextmatch);
		items.push_back(item);
		if (nextmatch == std::string::npos) { break; }
		src = src.substr(nextmatch + 1);
		nextmatch = src.find(ch); }

	return items; }


bool consumePrefix(string& text, const string& match) {
	const int matchLen = match.size();
	if (text.size() < matchLen) {
		return false; }
	if (text.substr(0, matchLen) == match) {
		text = text.substr(matchLen);
		return true; }
	return false; }


bool consumeSuffix(string& text, const string& match) {
	const int matchLen = match.size();
	if (text.size() < matchLen) {
		return false;}
	if (text.substr(text.size()-matchLen, matchLen) == match) {
		text = text.substr(0, text.size()-matchLen);
		return true; }
	return false; }


const auto ROCKY = int{0};
const auto WET = int{1};
const auto NARROW = int{2};

const int y0Factor = 16807;
const int x0Factor = 48271;

vector<int> geo;
int stride;

int EL(int x, int y);

int GI(int x, int y) {
	{int existing = geo[y*stride+x];
		if (existing != -1) {
			return existing;}}

	if (x==0 && y==0) {
		return 0;}
	else if (x==0) {
		return y*x0Factor;}
	else if (y==0) {
		return x*y0Factor;}
	else {
		int value = EL(x-1, y) * EL(x, y-1);
		geo[y*stride+x] = value;
		return value; }}

int depth;

int EL(int x, int y) {
	return (GI(x, y) + depth) % 20183;}


int main() {
	ivec2 target;
	string line;

	getline(cin, line);
	auto segments = split(line, ' ');
	depth = stoi(segments[1]);

	getline(cin, line);
	segments = split(line, ' ');
	segments = split(segments[1], ',');
	target = ivec2{ stoi(segments[0]), stoi(segments[1]) };

	//cout << depth << "\n";
	//cout << target << "\n";

	geo.resize((target.x+1)*(target.y+1), -1);
	stride = target.x+1;

	int ax = 0;
	for (int y=0; y<=target.y; y++) {
		for (int x=0; x<=target.x; x++) {
			if (x==0 && y==0) continue;
			if (x==target.x && y==target.y) continue;
			int el = EL(x, y);
			int type = el%3;
			ax += type; }}

	cout << ax << "\n";
	return 0; }
