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

ivec2 vmin(ivec2 a, ivec2 b) {
	return ivec2{ min(a.x, b.x), min(a.y, b.y) }; }
ivec2 vmax(ivec2 a, ivec2 b) {
	return ivec2{ max(a.x, b.x), max(a.y, b.y) }; }

int area(ivec2 a) {
	return a.x * a.y; }

ostream& operator<<(ostream& stream, ivec2 item) {
	stream << "(" << item.x << ", " << item.y << ")";
	return stream; }

ivec2 operator-(ivec2 lhs, ivec2 rhs) {
	return ivec2{ lhs.x - rhs.x, lhs.y - rhs.y }; }
ivec2 operator+(ivec2 lhs, ivec2 rhs) {
	return ivec2{ lhs.x + rhs.x, lhs.y + rhs.y }; }
bool operator==(ivec2 lhs, ivec2 rhs) {
	return (lhs.x==rhs.x && lhs.y==rhs.y); }


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

struct Rect {
	ivec2 leftTop;
	ivec2 rightBottom; };


const auto DOWN = ivec2{0,1};
const auto LEFT = ivec2{-1,0};
const auto RIGHT = ivec2{1,0};

const auto SPRING_COORD = ivec2{500,0};

const int INF = 99999;


int main() {
	string line;
	vector<Rect> claySegments;

	Rect bounds = { ivec2{INF, INF}, ivec2{-INF, -INF} };
	while (getline(cin, line)) {
		auto segments = split(line, ' ');
		bool isRow = line[0] == 'y';

		auto tmp = split(segments[0], '=');
		int a = stoi(tmp[1]);

		tmp = split(segments[1], '=');
		tmp = split(tmp[1], '.');
		int b = stoi(tmp[0]);
		int c = stoi(tmp[2]);

		Rect r;
		if (isRow) {
			int y = a;
			int x1 = b;
			int x2 = c;
			r = Rect{ ivec2{b,a}, ivec2{c+1, a+1} }; }
		else {
			int x = a;
			int y1 = b;
			int y2 = c;
			r = Rect{ ivec2{x,y1}, ivec2{x+1,y2+1} }; }
		claySegments.push_back(r);
		bounds.leftTop = vmin(bounds.leftTop, r.leftTop);
		bounds.rightBottom = vmax(bounds.rightBottom, r.rightBottom); }

	//cout << "leftTop: " << bounds.leftTop << "\n";
	//cout << "rightBottom: " << bounds.rightBottom << "\n";

	const auto mapDim = ivec2{ bounds.rightBottom + ivec2{1,1} };
	vector<char> map(area(mapDim), '.');

	auto putPixel = [&](ivec2 coord, char color) {
		map[coord.y*mapDim.x+coord.x] = color; };
	auto getPixel = [&](ivec2 coord) {
		return map[coord.y*mapDim.x+coord.x]; };

	for (const auto& segment : claySegments) {
		for (int y=segment.leftTop.y; y<segment.rightBottom.y; y++) {
			for (int x=segment.leftTop.x; x<segment.rightBottom.x; x++) {
				putPixel(ivec2{x,y}, '#');}}}

	deque<ivec2> queue;
	while (1) {

		// clear flowing water
		for (int y=0; y<mapDim.y; y++) {
			for (int x=0; x<mapDim.x; x++) {
				if (getPixel({x,y}) == '|') {
					putPixel({x,y}, '.'); }}}

		// flow
		queue.clear();
		queue.push_back(SPRING_COORD);
		while (!queue.empty()) {
			auto hpos = queue.front(); queue.pop_front();

			putPixel(hpos, '|');

			if ((hpos+DOWN).y < mapDim.y) {
				if (getPixel(hpos+DOWN) == '.') {
					// flow down
					queue.push_back(hpos+DOWN);}
				else if (getPixel(hpos+DOWN) == '#' || getPixel(hpos+DOWN) == '~') {
					if (getPixel(hpos+LEFT) == '.') {
						queue.push_back(hpos+LEFT); }
					if (getPixel(hpos+RIGHT) == '.') {
						queue.push_back(hpos+RIGHT); }}}}

/*		string blah;
		for (int y=0; y<mapDim.y; y++) {
			blah = "";
			for (int x=494; x<508; x++) {
				blah.push_back(getPixel({x,y})); }
			cout << blah << "\n"; }*/

		// convert pooling flows into solid water
		int spansConverted = 0;
		const int IN_SAND = 0;
		const int IN_CLAY = 1;
		const int IN_FLOWING_WATER = 2;
		for (int y=0; y<mapDim.y-1; y++) {
			int state = IN_SAND;
			int wb = -1;
			int we = -1;
			for (int x=0; x<mapDim.x; x++) {
				auto color = getPixel({x, y});
				if (state == IN_SAND) {
					// coming from SAND
					if (color == '#') {
						state = IN_CLAY; }}
				else if (state ==IN_CLAY) {
					// coming from CLAY
					if (color == '#') {}
					else if (color == '|') {
						wb = x;
						state = IN_FLOWING_WATER; }
					else {
						state = IN_SAND; }}
				else if (state == IN_FLOWING_WATER) {
					// coming from FLOWING WATER
					if (color == '#') {
						we = x;

						// FOUND SPAN from [wb..we)
						for (int xx=wb; xx<we; xx++) {
							putPixel(ivec2{xx,y}, '~');}
						spansConverted++;
						
						state = IN_CLAY; }
					else if (color == '|') {}
					else {
						state = IN_SAND; }}}}

		if (spansConverted == 0) {
			break; }
		//cout << "." << flush;
		}

	//cout << "\n";
	int ax = 0;
	for (int y=bounds.leftTop.y; y<mapDim.y-1; y++) {
		for (int x=0; x<mapDim.x; x++) {
			if (getPixel({x,y}) == '|' || getPixel({x,y}) == '~') {
				ax++; }}}
	cout << ax << "\n";
	return 0; }
