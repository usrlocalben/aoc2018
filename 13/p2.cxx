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
bool operator==(ivec2 lhs, ivec2 rhs) {
	return (lhs.x==rhs.x && lhs.y==rhs.y); }


struct Cart {
	ivec2 pos;
	ivec2 vel;
	int nav; };


ivec2 turnRight(ivec2 a) {
	if (a.y == 0) {
		return ivec2{0, a.x}; }
	return ivec2{-a.y, 0};}


ivec2 turnLeft(ivec2 a) {
	if (a.y == 0) {
		return ivec2{0, -a.x}; }
	return ivec2{a.y, 0};}


const ivec2 EAST{1,0};
const ivec2 WEST{-1,0};
const ivec2 NORTH{0,-1};
const ivec2 SOUTH{0,1};


int main() {
	vector<string> map;
	vector<Cart> carts;

	string line;
	int y=0;
	while (getline(cin, line)) {
		for (int x=0; x<line.length(); x++) {
			switch (line[x]) {
			case '>':
				carts.push_back(Cart{ {x,y}, EAST, 0 });
				line[x] = '-';
				break;
			case '<':
				carts.push_back(Cart{ {x,y}, WEST, 0 });
				line[x] = '-';
				break;
			case '^':
				carts.push_back(Cart{ {x,y}, NORTH, 0 });
				line[x] = '|';
				break;
			case 'v':
				carts.push_back(Cart{ {x,y}, SOUTH, 0 });
				line[x] = '|';
				break;
			default:
				break; }}
		map.push_back(line);
		y++; }

	auto sortCarts = [&]() {
		sort(carts.begin(), carts.end(), [](const auto& a, const auto& b) {
			if (a.pos.y < b.pos.y) {
				 return true;}
			else if (a.pos.y == b.pos.y) {
			 	return a.pos.x < b.pos.x; }
			else {
				return false; }});};

	int t=0;

	ivec2 crashPosition{ -1, -1 };

	unordered_set<int> badCarts;

	while (carts.size() > 1) {
		badCarts.clear();
		sortCarts();

		/*
		for (int y=0; y<map.size(); y++) {
			string l = map[y];
			for (int x=0; x<l.size(); x++) {
				for (int ci=0; ci<carts.size(); ci++) {
					if (carts[ci].pos == ivec2{x,y}) {
						l[x] = '0' + ci; }}}
			cout << l << "\n"; }
		cout << "------------------\n";
		*/


		//cout << "." << flush;
		for (int ci=0; ci<carts.size(); ci++) {
			auto& ac = carts[ci];
			ac.pos = ac.pos + ac.vel;

			for (int oi=0; oi<carts.size(); oi++) {
				if (ci == oi) continue;
				const auto& other = carts[oi];
				if (ac.pos == other.pos) {
					// collision!
					badCarts.insert(ci);
					badCarts.insert(oi);}}
					//cout << "ci:" << ci << ", other:" << oi << "\n"; }}

			switch (map[ac.pos.y][ac.pos.x]) {
			case '/':
				if (ac.vel == WEST) {
					ac.vel = SOUTH; }
				else if (ac.vel == EAST) {
					ac.vel = NORTH; }
				else if (ac.vel == NORTH) {
					ac.vel = EAST; }
				else if (ac.vel == SOUTH) {
					ac.vel = WEST; }
				break;
			case '\\':
				if (ac.vel == WEST) {
					ac.vel = NORTH; }
				else if (ac.vel == EAST) {
					ac.vel = SOUTH; }
				else if (ac.vel == NORTH) {
					ac.vel = WEST; }
				else if (ac.vel == SOUTH) {
					ac.vel = EAST; }
				break;
			case '-':
				break;
			case '|':
				break;
			case '+':
				if (ac.nav == 0) {
					ac.vel = turnLeft(ac.vel); }
				else if (ac.nav == 1) {}
				else if (ac.nav == 2) {
					ac.vel = turnRight(ac.vel); }
				if (++ac.nav == 3) ac.nav = 0;
				break; }}

		{
			vector<Cart> tmp;
			for (int idx=0; idx<carts.size(); idx++) {
				if (auto search = badCarts.find(idx); search == badCarts.end()) {
					tmp.push_back(carts[idx]); }}
			swap(carts, tmp); }

		t++; }

	cout << carts[0].pos.x << "," << carts[0].pos.y << "\n";
	return 0; }
