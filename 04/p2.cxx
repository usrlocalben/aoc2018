#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


vector<string> split(const string& str, char ch) {
	vector<string> out;
	string src(str);
	auto match = src.find(ch);
	while (1) {
		auto item = src.substr(0, match);
		out.push_back(item);
		if (match == string::npos) {
			break; }
		src = src.substr(match + 1);
		match = src.find(ch); }
	return out; }


struct DateTime {
	int year;
	int month;
	int day;
	int hh;
	int mm;

	static DateTime parse(const string& text) {
		auto segments = split(text, ' ');
		string sdt = segments[0];
		string stm = segments[1];
		
		// date
		segments = split(sdt, '-');
		DateTime out;
		out.year = stoi(segments[0]);
		out.month = stoi(segments[1]);
		out.day = stoi(segments[2]);

		// time
		segments = split(stm, ':');
		out.hh = stoi(segments[0]);
		out.mm = stoi(segments[1]);
		return out; }};


bool consumePrefix(string& text, const string& prefix) {
	const int prefixLen = prefix.size();
	if (text.substr(0, prefixLen) == prefix) {
		text = text.substr(prefixLen);
		return true; }
	return false; }


struct Guard {
	int id = -1;
	vector<pair<int, int>> sleep;

	void clear() {
		id = -1;
		sleep.clear(); } };


int main() {
	string line;
	vector<string> entries;
	while (getline(cin, line)) {
		entries.push_back(line); }

	sort(entries.begin(), entries.end());

	vector<pair<int, Guard>> days;

	int dayId = 0;
	int state = 0;
	Guard g;
	g.id = -1;
	int sleepBegin = 0;
	int sleepEnd = 0;
	for (const auto& entry : entries) {
		auto segments = split(entry, ']');
		string s_date = segments[0].substr(1);
		string s_text = segments[1].substr(1);
		auto dt = DateTime::parse(s_date);

		if (consumePrefix(s_text, "Guard #")) {
			if (g.id != -1) {
				days.push_back({ dayId++, g });
				g.clear(); }
			g.id = stoi(s_text); }
		else if (consumePrefix(s_text, "falls asleep")) {
			sleepBegin = dt.mm; }
		else if (consumePrefix(s_text, "wakes up")) {
			g.sleep.push_back({sleepBegin, dt.mm}); }
		else {
			cout << "error1\n";
			return 1; }}

	vector<unordered_map<int, int>> mmtally(60);

	for (const auto& day : days) {
		const auto& dayId = day.first;
		const auto& guard = day.second;
		for (const auto& range : guard.sleep) {
			for (int minute=range.first; minute<range.second; minute++) {
				mmtally[minute][guard.id]++; }}}

	int maxfreq = 0;
	int maxfreqmin = -1;
	int maxfreqgid = 0;
	vector<vector<pair<int, int>>> mmtally2(60);
	for (int minute=0; minute<60; minute++) {
		const auto& src = mmtally[minute];
		auto& dst = mmtally2[minute];
		for (const auto& entry : src) {
			dst.push_back({ entry.second, entry.first }); }
		sort(dst.begin(), dst.end());
		if (!dst.empty()) {
			if (dst.back().first > maxfreq) {
				maxfreq = dst.back().first;
				maxfreqgid = dst.back().second;
				maxfreqmin = minute; }}}

	int answer = maxfreqmin * maxfreqgid;
	cout << answer << "\n";
	return 0; }
