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
	deque<pair<XXX, int>> queue;
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


const auto NORTH2 = ivec2{0,-2};
const auto SOUTH2 = ivec2{0, 2};
const auto WEST2 = ivec2{-2, 0};
const auto EAST2 = ivec2{ 2, 0};


template <typename VISITOR>
bool walk(const string& text, ivec2 curPos, int i, int sel, VISITOR& visitor) {
	//cout << "walk(" << curPos << ", i=" << i << ", sel=" << sel << "\n";

	int groupNum = 0;
	bool active = (groupNum == sel);
	while(text[i] != '$') {
		auto from = curPos;
		//cout << ">>> " << text[i] << "\n";
		switch (text[i]) {
		case 'N': {
			if (active) {
				curPos += NORTH2;
				visitor(from, curPos); }}
			break;
		case 'S':  {
			if (active) {
				curPos += SOUTH2;
				visitor(from, curPos); }}
			break;
		case 'E': {
			if (active) {
				curPos += EAST2;
				visitor(from, curPos); }}
			break;
		case 'W': {
			if (active) {
				curPos += WEST2;
				visitor(from, curPos); }}
			break;
		case '|':
			active = ((++groupNum) == sel);
			break;
		case '(': {
		    if (!active) {
				// skip over subexprs in this group
				int d = 1;
				i++;
				while (d > 0) {
					//cout << ">>S " << text[i] << "\n";
					if (text[i] == ')') {
						d--;}
					else if (text[i] == '(') {
						d++;}
					i++; }
				i--; }
			else {
				int subSel = 0;
				bool more = true;
				do {
					more = walk(text, curPos, i+1, subSel, visitor);
					subSel++;
				} while (more);
				return true;}}
			break;
		case ')': {
			//cout << "closing... sel=" << sel << ", groupNum=" << groupNum << "\n";
			if (sel > groupNum) {
				return false; }
			break;}
		default: assert(false); }
		i++; }

	return true;}


const int INF = 9999999;


int main() {
	string dirs;
	getline(cin, dirs);

	unordered_map<int, unordered_set<int>> rooms;

	// find bounding box
	ivec2 leftTop = { INF, INF };
	ivec2 rightBottom = { -INF, -INF };
	walk(dirs, ivec2{0,0}, 1, 0, [&](ivec2 from, ivec2 to) {
		 leftTop = vmin(leftTop, to);
		 rightBottom = vmax(rightBottom, to);});

	// offset to keep map coord >0
	auto offset = ivec2{0,0} - leftTop;

	// walk and store rooms and edges
	leftTop = { INF, INF };
	rightBottom = { -INF, -INF };
	walk(dirs, offset, 1, 0, [&](ivec2 from, ivec2 to) {
		 leftTop = vmin(leftTop, to);
		 rightBottom = vmax(rightBottom, to);

		 int fromId = (from.x<<16)|from.y;
		 int toId = (to.x<<16)|to.y;
		 rooms[fromId].insert(toId);
		 rooms[toId].insert(fromId); });

	unordered_map<int, int> roomDistance;

	deque<pair<int, int>> queue;
	unordered_set<int> visited;
	queue.push_back({ (offset.x<<16)|offset.y, 0 });
	while (!queue.empty()) {
		const auto[hpos, hdist] = queue.front();  queue.pop_front();
		if (auto already = visited.find(hpos); already != visited.end()) { continue; }
		visited.insert(hpos);

		roomDistance[hpos] = hdist;
		for (const auto& item : rooms[hpos]) {
			queue.push_back({ item, hdist+1 }); }}

	int cnt = 0;
	for (const auto& item : roomDistance) {
		if (item.second >= 1000) {
			cnt++; }}
	cout << cnt << "\n";
	return 0; }
