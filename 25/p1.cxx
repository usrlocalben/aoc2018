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
#define watch(x) cout << (#x) << "(" << (x) << ")\n"
#define dbg(x) (#x) << "(" << (x) << ") "
#define fi first
#define se second

const string nl("\n");

using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
using vs = vector<string>;
#define uset unordered_set
#define umap unordered_map

const int oo = 0x3f3f3f3f;

struct ivec2 {
	int x, y;

	inline ivec2& operator+=(ivec2 b) { x += b.x; y += b.y; return *this; }
	inline ivec2& operator-=(ivec2 b) { x -= b.x; y -= b.y; return *this; }
	inline ivec2& operator*=(ivec2 b) { x *= b.x; y *= b.y; return *this; } };

struct ivec3 {
	int x, y, z;

	inline ivec3& operator+=(ivec3 b) { x += b.x; y += b.y; z += b.z; return *this; }
	inline ivec3& operator-=(ivec3 b) { x -= b.x; y -= b.y; z -= b.z; return *this; }
	inline ivec3& operator*=(ivec3 b) { x *= b.x; y *= b.y; z *= b.z; return *this; } };

struct ivec4 {
	int x, y, z, w;

	inline ivec4& operator+=(ivec4 b) { x += b.x; y += b.y; z += b.z; w += b.w; return *this; }
	inline ivec4& operator-=(ivec4 b) { x -= b.x; y -= b.y; z -= b.z; w -= b.w; return *this; }
	inline ivec4& operator*=(ivec4 b) { x *= b.x; y *= b.y; z *= b.z; w *= b.w; return *this; } };

inline ivec2 vmin(ivec2 a, ivec2 b) { return { min(a.x, b.x), min(a.y, b.y) }; }
inline ivec3 vmin(ivec3 a, ivec3 b) { return { min(a.x, b.x), min(a.y, b.y), min(a.z, b.z) }; }
inline ivec2 vmax(ivec2 a, ivec2 b) { return { max(a.x, b.x), max(a.y, b.y) }; }
inline ivec3 vmax(ivec3 a, ivec3 b) { return { max(a.x, b.x), max(a.y, b.y), max(a.z, b.z) }; }
inline int hmax(ivec2 a) { return max(a.x, a.y); }
inline int hmax(ivec3 a) { return max(a.x, max(a.y, a.z)); }
inline int hmin(ivec2 a) { return min(a.x, a.y); }
inline int hmin(ivec3 a) { return min(a.x, min(a.y, a.z)); }

inline int mlength(ivec2 a) { return abs(a.x) + abs(a.y); }
inline int mlength(ivec3 a) { return abs(a.x) + abs(a.y) + abs(a.z); }
inline int mlength(ivec4 a) { return abs(a.x) + abs(a.y) + abs(a.z) + abs(a.w); }

inline int area(ivec2 a) { return a.x * a.y; }

ostream& operator<<(ostream& stream, ivec2 item) {
	stream << "(" << item.x << ", " << item.y << ")";
	return stream; }
ostream& operator<<(ostream& stream, ivec3 item) {
	stream << "(" << item.x << ", " << item.y << ", " << item.z << ")";
	return stream; }
ostream& operator<<(ostream& stream, ivec4 item) {
	stream << "(" << item.x << ", " << item.y << ", " << item.z << ", " << item.w << ")";
	return stream; }

inline ivec2 operator-(ivec2 a, ivec2 b) { return { a.x-b.x, a.y-b.y }; }
inline ivec3 operator-(ivec3 a, ivec3 b) { return { a.x-b.x, a.y-b.y, a.z-b.z }; }
inline ivec4 operator-(ivec4 a, ivec4 b) { return { a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w }; }
inline ivec2 operator+(ivec2 a, ivec2 b) { return { a.x+b.x, a.y+b.y }; }
inline ivec3 operator+(ivec3 a, ivec3 b) { return { a.x+b.x, a.y+b.y, a.z+b.z }; }
inline ivec2 operator*(ivec2 a, ivec2 b) { return { a.x*b.x, a.y*b.y }; }
inline ivec3 operator*(ivec3 a, ivec3 b) { return { a.x*b.x, a.y*b.y, a.z*b.z }; }
inline ivec3 operator/(ivec3 a, int b) { return {a.x/b, a.y/b, a.z/b}; }

inline bool operator==(ivec2 a, ivec2 b) { return (a.x==b.x && a.y==b.y); }
inline bool operator==(ivec3 a, ivec3 b) { return (a.x==b.x && a.y==b.y && a.z==b.z); }

const ivec2 UP{0,-1};
const ivec2 DOWN{0,1};
const ivec2 LEFT{-1,0};
const ivec2 RIGHT{1,0};

const auto NORTH = UP;
const auto SOUTH = DOWN;
const auto EAST = RIGHT;
const auto WEST = LEFT;


struct Rect {
	ivec2 lt;
	ivec2 rb;
	ivec2 dim() const { return { rb.x-lt.x, rb.y-lt.y }; }
	int area() const { return ::area(dim()); } };


/* bfs
	deque<pair<XXX, int>> queue;
	uset<XXX> visited;
	queue.push_back({ xxx, 0 });
	while (!queue.empty()) {
		const auto[hpos, hdist] = queue.front();  queue.pop_front();
		if (auto already = visited.find(hpos); already != visited.end()) { continue; }
		visited.insert(hpos);
		queue.push_back({ xxx, hdist+1 }); }
*/

/* dijkstra
	priority_queue<ii, vii, greater<ii>> queue;
	uset<int> visited;
	umap<int, int> dist;

	auto getDistance = [&](int key) {
		if (auto search = dist.find(key); search != dist.end()) {
			return search->second; }
		else {
			return oo; }};

	queue.push({ 0, INITIAL_POSITION });
	dist[INITIAL_POSITION] = 0;
	vector<pair<int, int>> outLinks;

	int answer = -1;
	while (!queue.empty()) {
		auto [hdist, hpos] = queue.top(); queue.pop();
		if (visited.find(hpos) != visited.end()) {
			continue;}
		visited.insert(hpos);

		// do something with hpos @ hdist
		if (hpos == DESTINATION) {
			//cout << "found target\n";
			answer = hdist;
			break;}

		// fill outlinks
		outLinks.clear();
		// outLinks.push_back({ COST, NEXT_NODE });

		for (const auto& link : outLinks) {
			const auto& cost = link.fi;
			const auto& nextPos = link.se;
			int thisCost = getDistance(hpos) + cost;
			if (getDistance(nextPos) > thisCost) {
				dist[nextPos] = thisCost;
				queue.push({ thisCost, nextPos }); }}}
*/

ostream& operator<<(ostream& stream, const vi& nums) {
	bool first = true;
	for (const auto& num : nums) {
		if (first) {
			stream << "[" << num;
			first = false; }
		else {
			stream << ", " << num; }}
	stream << "]";
	return stream; }


vs split(const string& str, char ch) {
	vs items;
	string src(str);
	auto nextmatch = src.find(ch);
	while (1) {
		items.emplace_back(src.substr(0, nextmatch));
		if (nextmatch == string::npos) { break; }
		src = src.substr(nextmatch + 1);
		nextmatch = src.find(ch); }
	return items; }


bool consumePrefix(string& text, const string& match) {
	if ((text.size() >= sz(match)) &&
		(text.substr(0, sz(match)) == match)) {
		text = text.substr(sz(match));
		return true; }
	return false; }


bool consumeSuffix(string& text, const string& match) {
	if ((text.size() >= sz(match)) &&
	    (text.substr(sz(text)-sz(match), sz(match)) == match)) {
		text = text.substr(0, sz(text)-sz(match));
		return true; }
	return false; }

/*
	string line;
	for (int y=0; y<YYY; y++) {
		line.clear();
		for (int x=0; x<XXX; x++) {
			line.push_back(foo); }
		cout << line << nl;}
*/

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	vector<ivec4> stars;
	while (getline(cin, line)) {
		auto segs = split(line, ',');
		ivec4 p{ stoi(segs[0]), stoi(segs[1]), stoi(segs[2]), stoi(segs[3]) };
		stars.push_back(p); }

	vector<pair<bool, uset<int>>> packs;
	uset<int> packfit;

	forn(si,sz(stars)) {
		packfit.clear();
		const auto& cur = stars[si];

		forn(pi,sz(packs)) {
			const auto& packAlive = packs[pi].first;
			auto& pack = packs[pi].second;
			if (!packAlive) continue;

			for (const auto other : pack) {
				if (mlength(stars[other] - cur) <= 3) {
					packfit.insert(pi);
					break;}}}

		if (sz(packfit) == 0) {
			// start a new pack with point
			packs.push_back({ true, uset<int>{si} }); }
		else if (sz(packfit) == 1) {
			// add point to pack[packfit.front]
			int destPack;
			for (const auto& pid : packfit) {
				destPack = pid; }
			packs[destPack].second.insert(si); }
		else {
			// merge all packs in packfit
			uset<int> newpack;
			for (const auto pid : packfit) {
				for (const auto psid : packs[pid].second) {
					newpack.insert(psid); }
				packs[pid].first = false; }
			// add point to resulting pack
			newpack.insert(si);
			packs.push_back({ true, newpack });}}

	int cnt = 0;
	for (const auto& pack : packs) {
		if (pack.first == true) {
			cnt++; }}
	cout << cnt << nl;
	return 0; }
