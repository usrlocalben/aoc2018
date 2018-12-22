#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <optional>
#include <queue>
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
const auto TARGET = int{3};

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

	
struct State {
	ivec2 pos;
	int equip;

	int pack() const {
		int out = pos.x;
		out <<= 13;
		out |= pos.y;
		out <<= 13;
		out |= pos.x;
		out <<= 3;
		out |= equip;
		return out; }

	static State unpack(int data) {
		State out;
		out.equip = data&0x7;
		data >>= 3;
		out.pos.x = data & 0x1fff;
		data >>= 13;
		out.pos.y = data & 0x1fff;
		return out; } };


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

	geo.resize(1024*1024, -1);
	stride = 1024;

	const int INF = 999999999;

	const int TORCH = 1;
	const int GEAR = 2;
	const int NONE = 4;

	// rocky, wet, narrow, target
	const auto badGear = array<int, 4>{ NONE, TORCH, GEAR, NONE|GEAR };

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
	unordered_set<int> visited;
	unordered_map<int, int> dist;

	auto getDistance = [&](int key) {
		if (auto search = dist.find(key); search != dist.end()) {
			return search->second; }
		else {
			return INF; }};

	const auto initial = State{ ivec2{0,0}, TORCH };
	queue.push({ 0, initial.pack() });
	dist[initial.pack()] = 0;
	vector<pair<int, int>> outLinks;

	int answer = -1;
	while (!queue.empty()) {
		auto [hdist, hpos] = queue.top(); queue.pop();
		if (visited.find(hpos) != visited.end()) {
			continue;}
		visited.insert(hpos);

		auto state = State::unpack(hpos);
		//cout << "H:" << state.pos << "\n";
		if (state.pos == target && state.equip==TORCH) {
			//cout << "found target\n";
			answer = hdist;
			break;}
		int hereType = EL(state.pos.x, state.pos.y) % 3;

		outLinks.clear();
		// y -1...+1
		for (int n=-1; n<=1; n+=2) {
			ivec2 nextPos = state.pos + ivec2{0, n};
			int nextType;
			if (nextPos.y < 0) continue; // OOB
			if (nextPos == target) {
				nextType = TARGET; }
			else {
				nextType = EL(nextPos.x, nextPos.y) % 3; }

			auto nextBadGear = badGear[nextType];
			if (state.equip & badGear[nextType]) continue; // wrong gear

			State nextState{ nextPos, state.equip };
			outLinks.push_back({ nextState.pack(), 1 });}
		// x -1...+1
		for (int n=-1; n<=1; n+=2) {
			ivec2 nextPos = state.pos + ivec2{n, 0};
			int nextType;
			if (nextPos.x < 0) continue; // OOB
			if (nextPos == target) {
				nextType = TARGET; }
			else {
				nextType = EL(nextPos.x, nextPos.y) % 3; }

			auto nextBadGear = badGear[nextType];
			if (state.equip & badGear[nextType]) continue; // wrong gear

			State nextState{ nextPos, state.equip };
			outLinks.push_back({ nextState.pack(), 1 });}
		
		for (int tool=1; tool<8; tool<<=1) {
			if (tool == state.equip) continue;
			if (tool & badGear[hereType]) continue;
			State nextState{ state.pos, tool };
			outLinks.push_back({ nextState.pack(), 7 });}
		for (const auto& link : outLinks) {
			auto weight = link.second;
			auto dstPos = link.first;
			int candidate = getDistance(hpos) + weight;
			if (getDistance(dstPos) > candidate) {
				dist[dstPos] = candidate;
				queue.push({ candidate, dstPos }); }}}

	cout << answer << "\n";
	return 0; }
