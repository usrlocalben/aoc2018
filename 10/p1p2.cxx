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


int main() {
	vector<int> positionX;
	vector<int> positionY;
	vector<int> velocityX;
	vector<int> velocityY;

	string line;

	int bbTop = -99999;
	int bbBottom = 99999;
	int bbLeft = 99999;
	
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
	}

	const int sz = positionX.size();

	//cout << "top: " << bbTop << "\n";
	//cout << "bot: " << bbBottom << "\n";

	/*
	int yheight = bbTop - bbBottom;
	int t = 0;
	while (t < 10900) {
		t++;
		bbTop = -99999;
		bbBottom = 99999;
		bbLeft = 99999;
		for (int i=0; i<sz; i++) {
			int nX = positionX[i] + velocityX[i];
			int nY = positionY[i] + velocityY[i];
			positionX[i] = nX;
			positionY[i] = nY;
			bbTop = max(bbTop, nY);
			bbBottom = min(bbBottom, nY);
			bbLeft = min(bbLeft, nX); }
		int nheight = bbTop - bbBottom;
		int delta = nheight - yheight;
		cout << "t:" << t << ", h:" << nheight << ", d:" << delta << ", top:" << bbTop << ", bot:" << bbBottom << ", left:" << bbLeft << "\n";
		yheight = nheight; }
	*/

	const int bufWidth = 80;
	const int bufHeight = 25;
	vector<char> pixels(bufWidth*bufHeight, ' ');

	const int t = 10886;
	for (int i=0; i<sz; i++) {
		int nX = positionX[i] + velocityX[i]*t;
		int nY = positionY[i] + velocityY[i]*t;
		positionX[i] = nX;
		positionY[i] = nY; }

	for (int by=0; by<bufHeight; by++) {
		int sy = by + 111;
		for (int bx=0; bx<bufWidth; bx++) {
			int sx = bx + 161;

			for (int i=0; i<sz; i++) {
				if (positionX[i] == sx && positionY[i] == sy) {
					pixels[by*bufWidth+bx] = '=';
					break; }}}}

	string tmp;
	for (int by=0; by<bufHeight; by++) {
		tmp = "";
		for (int bx=0; bx<bufWidth; bx++) {
			tmp.push_back(pixels[by*bufWidth+bx]); }
		cout << tmp << "\n"; }

	return 0; }
