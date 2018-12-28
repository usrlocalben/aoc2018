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

inline int area(ivec2 a) { return a.x * a.y; }

ostream& operator<<(ostream& stream, ivec2 item) {
	stream << "(" << item.x << ", " << item.y << ")";
	return stream; }
ostream& operator<<(ostream& stream, ivec3 item) {
	stream << "(" << item.x << ", " << item.y << ", " << item.z << ")";
	return stream; }

inline ivec2 operator-(ivec2 a, ivec2 b) { return { a.x-b.x, a.y-b.y }; }
inline ivec3 operator-(ivec3 a, ivec3 b) { return { a.x-b.x, a.y-b.y, a.z-b.z }; }
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

const int GOOD = 0;
const int BAD = 1;
int gidgen=0;

array<int, 2> boost = {0,0};

struct Group {
	int gid;
	int side;
	int units;
	int hp;
	int init;
	umap<string, int> sw;
	string type;
	int atk;
	int targetId = 0;
	int power() const { return units * (atk + boost[side]); }
};

ostream& operator<<(ostream& s, const Group& g) {
	s << "<Group gid=" << g.gid;
	s << " side=" << (g.side==GOOD?"immune":"infection");
	s << " units=" << g.units;
	s << " power=" << g.power();
	s << " init=" << g.init;
	s << ">";
	return s; }

const int IMMUNE_TO = 0;
const int WEAK_TO = 1;

int damageCalc(const Group& from, const Group& to) {
	if (auto search = to.sw.find(from.type); search!=to.sw.end()) {
		const auto& disposition = search->second;
		if (disposition == IMMUNE_TO) {
			return 0;}
		else if (disposition == WEAK_TO) {
			return from.power() * 2; }
		else {
			assert(false);
			return 0; }}
	else {
		return from.power(); }}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string line;
	vector<Group> groups;

	int curTeam = GOOD;

	while (getline(cin, line)) {
		if (consumePrefix(line, "Immune System")) {
			curTeam = GOOD; }
		else if (consumePrefix(line, "Infection")) {
			curTeam = BAD; }
		else if (line == "") {}
		else {
			Group g;
			g.gid = gidgen++;
			g.side = curTeam;

			if (line.find('(') == string::npos) {
				auto segments = split(line, ' ');
				g.units = stoi(segments[0]);
				g.hp = stoi(segments[4]);
				g.atk = stoi(segments[12]);
				g.type = segments[13];
				g.init = stoi(segments[17]); }
			else {
				auto segs1 = split(line, '(');
				auto segs2 = split(segs1[1], ')');

				auto seg1 = segs1[0];
				auto seg2 = segs2[0];
				auto seg3 = segs2[1];

				// seg1 "nnnn units each with nnnn hit points "
				auto segments = split(seg1, ' ');

				g.units = stoi(segments[0]);
				g.hp = stoi(segments[4]);

				// seg2 "(weak|immune) to (type)(?,type...); ..."
				segments = split(seg2, ';');
				for (auto segment : segments) {
					if (segment[0] == ' ') segment = segment.substr(1);
					int disposition = -1;
					if (consumePrefix(segment, "immune to ")) {
						disposition = IMMUNE_TO; }
					else if (consumePrefix(segment, "weak to ")) {
						disposition = WEAK_TO; }
					auto subsegs = split(segment, ',');
					for (auto subseg : subsegs) {
						if (subseg[0] == ' ') subseg = subseg.substr(1);
						//cout << "[" << subseg << "]\n";
						g.sw[subseg] = disposition; }}

				// seg3 " with an attack that does NNN (type) damage at initiative NN"
				segments = split(seg3, ' ');
				g.atk = stoi(segments[6]);
				g.type = segments[7];
				g.init = stoi(segments[11]);}
			groups.push_back(g);
		}}


	auto numTeamsLeft = [&]() {
		uset<int> teams;
		for (const auto& g : groups) {
			if (g.units > 0) {
				teams.insert(g.side); }}
		return sz(teams); };

	uset<int> chosen;
	vector<pair<tuple<int, int, int>, int>> targets;
	auto fight = [&]() {

		// power desc, init desc
		sort(groups.begin(), groups.end(), [](const auto& a, const auto& b) {
			if (a.power() > b.power()) return true;
			if (a.power() < b.power()) return false;
			return a.init > b.init;});

		chosen.clear();
		for (auto& attacker : groups) {
			attacker.targetId = -1;
			if (attacker.units <= 0) continue;

			targets.clear();
			for (const auto& candidate : groups) {
				if (chosen.find(candidate.gid) != chosen.end()) continue;
				if (candidate.side == attacker.side) continue;
				if (candidate.units <= 0) continue;

				auto damage = damageCalc(attacker, candidate);
				//cout << ag.gid << "->" << candidate.gid << ": " << dbg(damage) << nl;
				tuple<int, int, int> sortKey{ damage, candidate.power(), candidate.init };

				if (damage > 0) {
					//cout << "gid=" << attacker.gid << " ->? gid=" << candidate.gid << ", damage=" << damage << nl;
					targets.push_back({ sortKey, candidate.gid });}}

			if (!targets.empty()) {
				// damage desc, power desc, init desc
				nth_element(targets.begin(), targets.begin(), targets.end(), greater<pair<tuple<int, int, int>, int>>());
				attacker.targetId = targets.front().second;
				//cout << "  gid=" << attacker.gid << " will attack gid=" << attacker.targetId << nl;
				chosen.insert(attacker.targetId); }}

		//cout << dbg(sz(chosen)) << nl;

		sort(groups.begin(), groups.end(), [](const auto& a, const auto& b) {
			return a.init > b.init; });

		for (auto& attacker : groups) {
			if (attacker.targetId == -1) continue;
			assert(attacker.units > 0);

			auto search = find_if(groups.begin(), groups.end(), [&](const auto& item) {
								  return item.gid == attacker.targetId; });
			assert(search != groups.end());

			auto& target = *search;

			auto damage = damageCalc(attacker, target);
			int unitsLost = damage / target.hp;
			unitsLost = min(unitsLost, target.units);

			//cout << "attack: gid=" << attacker.gid << " -> gid=" << target.gid << ", " << unitsLost << " units killed\n";
			target.units -= unitsLost;}};

	auto initGroups = groups;

	// phase 1, probe for winning boost
	//cout << "P1\n";
	int winner;
	boost[GOOD] = -10000;
	do {
		boost[GOOD] += 10000;

		groups = initGroups;
		while (numTeamsLeft() > 1) {
			fight(); }
		//cout << "." << flush;

		for (const auto& g : groups) {
			if (g.units > 0) {
				winner = g.side;
				break;}}
		//cout << "p1: " << boost[GOOD] << " = " << (winner==GOOD?"GOOD":"BAD") << nl;
	} while (winner == BAD);


	//cout << "good can win with boost=" << boost[GOOD] << nl;

	// phase 2, binary partition the range
	//cout << "P2\n";
	winner = 0;
	int boostLower = 0;
	int boostUpper = boost[GOOD] + 1;
	while (boostUpper - boostLower > 1) {
		int b = (boostLower + (boostUpper-1)) / 2;
		boost[GOOD] = b;

		//cout << "<" << b << ">" << flush;
		groups = initGroups;

		int prevUnits = -1;
		while (numTeamsLeft() > 1) {
			fight();

			int units = 0;
			for (const auto& g : groups) {
				units += g.units; }
			if (units == prevUnits) {
				winner = -1;  // stalemate
				break;}
			prevUnits = units; }

		if (winner == -1) {
			// stalemate detected -- phase 3 needed
			break; }

		for (const auto& g : groups) {
			if (g.units > 0) {
				winner = g.side;
				break;}}

		//cout << "p1: " << b << " = " << (winner==GOOD?"GOOD":"BAD") << nl;

		if (winner == BAD) {
			boostLower = b+1; }
		else {
			boostUpper = b+1; }}

	if (winner == -1) {
	//cout << "P3\n";
	// phase 3, linear probing to avoid stalemate games
	for (; boostLower<boostUpper; boostLower++) {
		//cout << "<" << boostLower << ">" << flush;
		boost[GOOD] = boostLower;
		winner = 0;
		groups = initGroups;
		int prevUnits = -1;
		while (numTeamsLeft() > 1) {
			fight();

			int units = 0;
			for (const auto& g : groups) {
				units += g.units; }
			if (units == prevUnits) {
				winner = -1;  // stalemate
				break;}
			prevUnits = units; }

		if (winner == -1) {
			continue;}

		for (const auto& g : groups) {
			if (g.units > 0) {
				winner = g.side;
				break;}}

		//cout << "p1: " << boostLower << " = " << (winner==GOOD?"GOOD":"BAD") << nl;

		if (winner == GOOD) {
			break; }}}

	//cout << dbg(boostLower) << dbg(boostUpper) << nl;

	// boostLower is the lower bounds for winning
	groups = initGroups;
	boost[GOOD] = boostLower;
	while (numTeamsLeft() > 1) {
		fight(); }

	int cnt = 0;
	for (const auto& g : groups) {
		if (g.side == GOOD) {
			cnt += g.units; }}
	cout << cnt << nl;
	return 0; }
