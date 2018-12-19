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

struct ivec2 {
	int x, y; };

ivec2 operator+(ivec2 lhs, ivec2 rhs) {
	return ivec2{ lhs.x+rhs.x, lhs.y+rhs.y }; }
bool operator==(ivec2 lhs, ivec2 rhs) {
	return (lhs.x==rhs.x && lhs.y==rhs.y); }
int area(ivec2 a) {
	return a.x * a.y; }

int pidgen = 0;

struct Player {
	char team;
	ivec2 pos;
	int life = 200;
	int id;

	Player(char team, ivec2 pos) :team(team), pos(pos), id(pidgen++) {}
	};

const auto NORTH = ivec2{0, -1};
const auto SOUTH = ivec2{0, 1};
const auto EAST = ivec2{1, 0};
const auto WEST = ivec2{-1, 0};

const array<ivec2, 4> DIRS{ NORTH, WEST, EAST, SOUTH };

template <typename T>
bool readingOrder(const T& a, const T& b) {
	if (a.y < b.y) {
		return true; }
	else if (a.y > b.y) {
		return false; }
	else {
		return a.x < b.x; };}

int main() {
	string line;
	vector<string> map;
	vector<Player> players;
	int y=0;
	while (getline(cin, line)) {
		for (int x=0; x<line.length(); x++) {
			const auto ch = line[x];
			switch (ch) {
			case 'G':
				players.push_back(Player{'G', ivec2{x,y}});
				line[x] = '.';
				break;
			case 'E':
				players.push_back(Player{'E', ivec2{x,y}});
				line[x] = '.';
				break;
			default:
				break;}}
		map.push_back(line);
		y++; }

	const ivec2 mapDim{ int(map[0].length()), int(map.size()) };

	auto sortPlayers = [&]() {
		sort(players.begin(), players.end(), [](const auto& a, const auto& b) {
			 return readingOrder(a.pos, b.pos); });};

	auto isOpen = [&](ivec2 coord) {
		if (coord.y < 0 || coord.y >= mapDim.y) {
			return false; }
		if (coord.x < 0 || coord.x >= mapDim.x) {
			return false; }
		if (map[coord.y][coord.x] == '#') {
			return false; }// wall on map
		for (const auto& player : players) {
			if (coord == player.pos && player.life > 0) {
				return false; }} // occupied by a player
		return true; };

	auto targetInRangeOf = [&](Player& p) -> Player* {
		vector<pair<Player*, int>> targets;
		targets.reserve(4);
		for (auto& other : players) {
			if (other.life>0 && p.id != other.id && p.team != other.team) {
				if (p.pos + NORTH == other.pos) {
					targets.push_back({ &other, 0 }); }
				else if (p.pos + WEST == other.pos) {
					targets.push_back({ &other, 1 }); }
				else if (p.pos + EAST == other.pos) {
					targets.push_back({ &other, 2 }); }
				else if (p.pos + SOUTH == other.pos) {
					targets.push_back({ &other, 3 }); }}}
		if (targets.empty()) {
			return nullptr; }
		sort(targets.begin(), targets.end(), [](const auto& a, const auto& b) {
			if (a.first->life < b.first->life) {
				return true; }
			else if (a.first->life > b.first->life) {
				return false;  }
			else {
				return (a.second < b.second); }});
		return targets[0].first; };

	const int UNREACHABLE = 999999;
	vector<pair<ivec2, int>> dsts;
	vector<bool> visited;
	vector<int> path;
	deque<pair<ivec2, int>> queue;
	auto maybeMove = [&](Player& p) -> Player* {
		dsts.clear();
		for (auto& other : players) {
			if (other.life>0 && p.team != other.team) {
				for (const auto dir : DIRS) {
					const auto candidate = other.pos + dir;
					if (isOpen(candidate)) {
						int found = -1;
						int idx = 0;
						for (const auto& dst:dsts) {
							if (dst.first == candidate) {
								found = idx; }
							idx++; }
						if (found == -1) {
							dsts.push_back({candidate, UNREACHABLE}); }}}}}

		if (dsts.empty()) {
			return nullptr; } // no targets available

		visited.clear();
		visited.resize(area(mapDim), false);

		queue.clear();
		queue.push_back({p.pos, 0});
		while (!queue.empty()) {
			const auto [hpos, hdist] = queue.front(); queue.pop_front();
			if (!visited[hpos.y*mapDim.x + hpos.x]) {
				visited[hpos.y*mapDim.x + hpos.x] = true;

				for (auto& dst : dsts) {
					const auto& dstCoord = dst.first;
					auto& dstDistance = dst.second;
					if (dstCoord == hpos) {
						dstDistance = hdist; }}

				for (const auto dir : DIRS) {
					const auto candidate = hpos + dir;
					if (isOpen(candidate)) {
						queue.push_back({ candidate, hdist+1 }); }}}}

		sort(dsts.begin(), dsts.end(), [](const auto& a, const auto& b) {
			if (a.second < b.second) {
				return true;}
			else if (a.second > b.second) {
				return false;}
			else {
				return readingOrder(a.first, b.first); }});
				
		if (dsts.front().second == UNREACHABLE) {
			return nullptr;}  // targets exist, but none are reachable

		const auto chosen = dsts.front().first;
		path.clear();
		path.resize(area(mapDim), UNREACHABLE);
		visited.clear();
		visited.resize(area(mapDim), false);
		queue.push_back({chosen, 0});
		while (!queue.empty()) { // && !visited[p.pos.y*mapDim.x+p.pos.x]) {
			const auto [hpos, hdist] = queue.front(); queue.pop_front();
			if (!visited[hpos.y*mapDim.x + hpos.x]) {
				visited[hpos.y*mapDim.x + hpos.x] = true;

				path[hpos.y*mapDim.x + hpos.x] = hdist;

				for (const auto dir : DIRS) {
					const auto candidate = hpos + dir;
					if (isOpen(candidate)) {
						queue.push_back({ candidate, hdist+1 }); }}}}
		
		dsts.clear();
		for (const auto dir : DIRS) {
			const auto candidate = p.pos + dir;
			const auto distance = path[candidate.y*mapDim.x + candidate.x];
			if (distance != UNREACHABLE) {
				dsts.push_back({ candidate, distance }); }}
		assert(!dsts.empty());
		sort(dsts.begin(), dsts.end(), [](const auto& a, const auto& b) {
			if (a.second < b.second) {
				return true;}
			else if (a.second > b.second) {
				return false;}
			else {
				return readingOrder(a.first, b.first); }});

		p.pos = dsts.front().first;
		return targetInRangeOf(p); };

	auto numTeamsAlive = [&]() {
		unordered_set<char> teams;
		for (const auto& player : players) {
			if (player.life > 0) {
				teams.insert(player.team); }}
		return teams.size(); };

	auto printState = [&]() {
		vector<Player> tmp;
		for (int y=0; y<mapDim.y; y++) {
			tmp.clear();
			string line = map[y];
			for (int x=0; x<mapDim.x; x++) {
				const auto pos = ivec2{x, y};
				for (const auto& player : players) {
					if (player.life>0 && player.pos == pos) {
						line[x] = player.team;
						tmp.push_back(player); }}}
			cout << line;
			bool first = true;
			for (const auto& p : tmp) {
				if (first) {
					first = false;
					cout << "   "; }
				else {
					cout << ", "; }
				cout << p.team << "(" << p.life << ")"; }
			cout << "\n"; }};

	const int gAttack = 3;
	int eAttack = 3;

	vector<Player> originalPlayers = players;

	int numElves = 0;
	int numAlive;
	for (const auto& player : players) {
		if (player.team == 'E') {
			numElves++; }}

	char survivingTeam;
	int outcome;
	do {
		players = originalPlayers;

	int t = 0;
	int pi = 0;
	sortPlayers();
	while (numTeamsAlive() > 1) {
		auto& player = players[pi];

		if (player.life > 0) {
			Player* otherPtr = targetInRangeOf(player);
			if (otherPtr == nullptr) {
				otherPtr = maybeMove(player); }
			if (otherPtr != nullptr) {
				assert(otherPtr->life > 0);
				const int attackPower = (player.team == 'G' ? gAttack : eAttack);
				otherPtr->life -= attackPower; }}

		if (++pi == players.size()) {
			t++;
//cout << "staring round " << (t+1) << "\n";
//printState();
			sortPlayers();
			pi = 0; }}

	int ax = 0;
	numAlive = 0;
	for (const auto& player : players) {
		if (player.life > 0) {
			survivingTeam = player.team;
			numAlive++;
			ax += player.life; }}

	outcome = t * ax;
	cout << "winner:" << survivingTeam << ", outcome:" << outcome << "\n";
	eAttack++;
	} while (survivingTeam == 'G' || (numAlive != numElves));

	return 0; }
