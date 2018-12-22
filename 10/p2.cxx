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


const int INF = 99999;

int main() {
	vector<int> positionX;
	vector<int> positionY;
	vector<int> velocityX;
	vector<int> velocityY;

	string line;

	int bbTop = -INF;
	int bbBottom = INF;
	int bbLeft = INF;
	int bbRight = -INF;
	
	while (getline(cin, line)) {
		// "position=< 21992, -10766> velocity=<-2,  1>"
		//  012345678901234567890123456789012345678901234
		//            11111111112222222222333333333344444
		int posx = stoi(line.substr(10, 16-10));
		int posy = stoi(line.substr(17, 24-17));
		int velx = stoi(line.substr(36, 38-36));
		int vely = stoi(line.substr(39, 42-39));

		//cout << "[" << posx << "," << posy << "]";
		//cout << "[" << velx << "," << vely << "]\n";
		positionX.push_back(posx);
		positionY.push_back(posy);
		velocityX.push_back(velx);
		velocityY.push_back(vely);

		bbTop = max(bbTop, posy);
		bbBottom = min(bbBottom, posy);
		bbLeft = min(bbLeft, posx);
		bbRight = max(bbRight, posx);
	}

	const int sz = positionX.size();

	int t = 0;
	int prevHeight = bbTop - bbBottom;
	int minHeight = prevHeight;
	int minHeightT = 0;
	while (1) {
		t++;

		bbTop = -INF;
		bbBottom = INF;
		bbLeft = INF;
		bbRight = -INF;
		for (int i=0; i<sz; i++) {
			int nX = positionX[i] + (velocityX[i] * t);
			int nY = positionY[i] + (velocityY[i] * t);
			bbTop = max(bbTop, nY);
			bbBottom = min(bbBottom, nY);
			bbLeft = min(bbLeft, nX);
			bbRight = max(bbRight, nX); }

		int curHeight = bbTop - bbBottom;
		if (curHeight < minHeight) {
			minHeight = curHeight;
			minHeightT = t;}
		else if (curHeight > minHeight) {
			// now past the minimum
			break; }

		prevHeight = curHeight; }

	cout << minHeightT << "\n";
	return 0; }
