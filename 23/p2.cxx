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


struct Box {
	ivec3 lbb;
	ivec3 rtf;
	inline ivec3 center() const {
		return { (lbb + rtf) / 2 }; }

	long long volume() const {
		return xsz() * ysz() * zsz(); }

	long long xsz() const { return abs(rtf.x - lbb.x); }
	long long ysz() const { return abs(rtf.y - lbb.y); }
	long long zsz() const { return abs(rtf.z - lbb.z); }

	inline ivec3 corner(int n) const {
		switch (n) {
		case 0: return lbb;						// left-bottom-back
		case 1: return {rtf.x-1, lbb.y, lbb.z};   // right-bottom-back
		case 2: return {lbb.x, lbb.y, rtf.z-1};	// left-bottom-front
		case 3: return {rtf.x-1, lbb.y, rtf.z-1};	// right-bottom-front

		case 4: return {lbb.x, rtf.y-1, lbb.z};  // left-top-back
		case 5: return {rtf.x-1, rtf.y-1, lbb.z};	// right-top-back
		case 6: return {lbb.x, rtf.y-1, rtf.z-1};	// left-top-front
		case 7: return {rtf.x-1, rtf.y-1, rtf.z-1};	// right-top-front
		default: assert(false); }}

	inline bool contains(ivec3 a) const {
		return ((lbb.x <= a.x && a.x < rtf.x) &&
		        (lbb.y <= a.y && a.y < rtf.y) &&
		        (lbb.z <= a.z && a.z < rtf.z));} };


struct Bot {
	ivec3 pos;
	int r;
	inline ivec3 front() const { return pos + ivec3{0,0,r}; }
	inline ivec3 back() const { return pos + ivec3{0,0,-r}; }
	inline ivec3 left() const { return pos + ivec3{-r,0,0}; }
	inline ivec3 right() const { return pos + ivec3{r,0,0}; }
	inline ivec3 top() const { return pos + ivec3{0,r,0}; }
	inline ivec3 bottom() const { return pos + ivec3{0,-r,0}; }

	inline ivec3 corner(int n) const {
		switch (n) {
		case 0: return {pos.x-r, pos.y-r, pos.z-r};	// left-bottom-back
		case 1: return {pos.x+r, pos.y-r, pos.z-r};	// right-bottom-back
		case 2: return {pos.x-r, pos.y-r, pos.z+r};	// left-bottom-front
		case 3: return {pos.x+r, pos.y-r, pos.z+r};	// right-bottom-front

		case 4: return {pos.x-r, pos.y+r, pos.z-r};	// left-top-back
		case 5: return {pos.x+r, pos.y+r, pos.z-r};	// right-top-back
		case 6: return {pos.x-r, pos.y+r, pos.z+r};	// left-top-front
		case 7: return {pos.x+r, pos.y+r, pos.z+r};	// right-top-front
		default: assert(false); }}

	inline ivec3 extent(int n) const {
		switch (n) {
		case 0: return front();
		case 1: return back();
		case 2: return left();
		case 3: return right();
		case 4: return bottom();
		case 5: return top();
		default: assert(false); }}


	//const botFrontBounds = a.pos + ivec3{0, 0, a.r};

	inline bool contains(ivec3 p) const { return mlength(pos - p) <= r;}
	inline int distanceFrom(ivec3 p) const { return mlength(pos-p) - r; } };


auto octdiv(Box b) {
	array<Box, 8> out;
	const auto c = b.center();
	out[0] = Box{ { b.lbb.x, b.lbb.y, b.lbb.z }, {     c.x,     c.y,     c.z } }; // left-bottom-back
	out[1] = Box{ {     c.x, b.lbb.y, b.lbb.z }, { b.rtf.x,     c.y,     c.z } }; // right-bottom-back
	out[2] = Box{ { b.lbb.x, b.lbb.y,     c.z }, {     c.x,     c.y, b.rtf.z } }; // left-bottom-front
	out[3] = Box{ {     c.x, b.lbb.y,     c.z }, { b.rtf.x,     c.y, b.rtf.z } }; // right-bottom-front

	out[4] = Box{ { b.lbb.x,     c.y, b.lbb.z }, {     c.x, b.rtf.y,     c.z } }; // left-top-back
	out[5] = Box{ {     c.x,     c.y, b.lbb.z }, { b.rtf.x, b.rtf.y,     c.z } }; // right-top-back
	out[6] = Box{ { b.lbb.x,     c.y,     c.z }, {     c.x, b.rtf.y, b.rtf.z } }; // left-top-front
	out[7] = Box{ {     c.x,     c.y,     c.z }, { b.rtf.x, b.rtf.y, b.rtf.z } }; // right-top-front
	return out; }


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<Bot> bots;

	string line;

	Box bb;
	bb.lbb = { oo, oo, oo };
	bb.rtf = {-oo,-oo,-oo };

	while (getline(cin, line)) {
		auto segments = split(line, ' ');
		auto pos = segments[0].substr(5);
		auto tmp = split(pos, ',');

		ivec3 p{ stoi(tmp[0]), stoi(tmp[1]), stoi(tmp[2]) };

		tmp = split(segments[1], '=');
		int r = stoi(tmp[1]);

		bb.lbb = vmin(bb.lbb, p);
		bb.rtf = vmax(bb.rtf, p);

		bots.push_back({ p, r });}
	bb.rtf += ivec3{1,1,1};  // rtf is exclusive

	// positive
	for (auto& bot : bots) {
		bot.pos -= bb.lbb; }
	auto origin = ivec3{0,0,0} - bb.lbb;
	bb.rtf -= bb.lbb;
	bb.lbb -= bb.lbb;

	//cout << dbg(bb.lbb) << dbg(bb.rtf) << dbg(origin) << nl;

	// power-of-2 cube
	int largest = hmax(bb.rtf);
	{int xa=1;
	while (xa < largest) xa<<=1;
	largest = xa; }
	bb.rtf = {largest+1, largest+1, largest+1};
	//cout << dbg(bb.rtf) << nl;

	struct SearchBox {
		int n;
		int d;
		Box b;
		int dim() const { return b.rtf.x - b.lbb.x; } };

	struct sbcmp {
		bool operator()(const SearchBox& a, const SearchBox& b) {
			if (a.n > b.n) return false;
			if (a.n < b.n) return true;
			if (a.d < b.d) return false;
			if (a.d > b.d) return true;
			return a.dim() > b.dim(); }};

	priority_queue <SearchBox, vector<SearchBox>, sbcmp> q;
	q.push(SearchBox{ sz(bots), mlength(bb.center() - origin), bb });
	auto found = bb.rtf;
	uset<int> covered;
	while (!q.empty()) {
		auto cb = q.top(); q.pop();
		//cout << ">>> " << cb.b.lbb << "--" << cb.b.rtf << ", n=" << cb.n << ", d=" << cb.d << ", dim=" << cb.dim() << nl;
		if (cb.dim() == 1) {
			found = cb.b.lbb;
			break; }

		for (const auto& subbox : octdiv(cb.b)) {
			SearchBox sb;
			covered.clear();
			forn(bi,sz(bots)) {
				const auto& bot = bots[bi];
				forn(c,8) {
					if (bot.distanceFrom(subbox.corner(c)) <= 0) {
						covered.insert(bi);
						break;}}
				forn(c,8) {
					if (subbox.contains(bot.extent(c))) {
						covered.insert(bi);
						break;}}}
			sb.n = sz(covered);
			sb.d = mlength(subbox.center() - origin);
			sb.b = subbox;
			//cout << "    adding: " << subbox.lbb << "--" << subbox.rtf << ", n=" << sb.n << ", d=" << sb.d << nl;
			if (sb.n) {
				q.push(sb);}}}

	if (found == bb.rtf) {
		cout << "not found\n";
		return 1; }
	else {
		//cout << (found-origin) << "\n";
		cout << mlength(found-origin) << "\n";
		return 0; }}
