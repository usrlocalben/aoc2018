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


struct CPU {
	array<int, 4> r = {0,0,0,0}; };


enum Opcode {
	addr, addi,
	mulr, muli,
	banr, bani,
	borr, bori,
	setr, seti,
	gtir, gtri, gtrr,
	eqir, eqri, eqrr };


CPU execute(CPU cpu_, Opcode opcode, int arg1, int arg2, int output) {
	CPU cpu = cpu_;
	int result;
	switch (opcode) {
	case Opcode::addr: result = cpu.r[arg1] + cpu.r[arg2]; break;
	case Opcode::addi: result = cpu.r[arg1] + arg2;        break;
	case Opcode::mulr: result = cpu.r[arg1] * cpu.r[arg2]; break;
	case Opcode::muli: result = cpu.r[arg1] * arg2;        break;
	case Opcode::banr: result = cpu.r[arg1] & cpu.r[arg2]; break;
	case Opcode::bani: result = cpu.r[arg1] & arg2;        break;
	case Opcode::borr: result = cpu.r[arg1] | cpu.r[arg2]; break;
	case Opcode::bori: result = cpu.r[arg1] | arg2;        break;
	case Opcode::setr: result = cpu.r[arg1];               break;
	case Opcode::seti: result = arg1;                      break;
	case Opcode::gtir: result = (arg1 > cpu.r[arg2] ? 1 : 0); break;
	case Opcode::gtri: result = (cpu.r[arg1] > arg2 ? 1 : 0); break;
	case Opcode::gtrr: result = (cpu.r[arg1] > cpu.r[arg2] ? 1 : 0); break;
	case Opcode::eqir: result = (arg1 == cpu.r[arg2] ? 1 : 0); break;
	case Opcode::eqri: result = (cpu.r[arg1] == arg2 ? 1 : 0); break;
	case Opcode::eqrr: result = (cpu.r[arg1] == cpu.r[arg2] ? 1 : 0); break;
	default: assert(false); }
	cpu.r[output] = result;
	return cpu; }


int main() {
	string line;

	struct Sample {
		int opcode;
		int a;
		int b;
		int c;
		CPU before;
		CPU after; };

	Sample sample;
	vector<vector<Sample>> opcodeSamples(16);

	int blanks = 0;
	while (getline(cin, line)) {
		if (line.substr(0,6) == "Before") {
			blanks = 0;
			auto segments = split(line, '[');
			segments = split(segments[1], ' ');
			sample.before.r[0] = stoi(segments[0]);
			sample.before.r[1] = stoi(segments[1]);
			sample.before.r[2] = stoi(segments[2]);
			sample.before.r[3] = stoi(segments[3]); }
		else if (line.substr(0,5) == "After") {
			blanks = 0;
			auto segments = split(line, '[');
			segments = split(segments[1], ' ');
			sample.after.r[0] = stoi(segments[0]);
			sample.after.r[1] = stoi(segments[1]);
			sample.after.r[2] = stoi(segments[2]);
			sample.after.r[3] = stoi(segments[3]);
			opcodeSamples[sample.opcode].push_back(sample); }
		else if (line.length()) {
			blanks = 0;
			auto segments = split(line, ' ');
			sample.opcode = stoi(segments[0]);
			sample.a = stoi(segments[1]);
			sample.b = stoi(segments[2]);
			sample.c = stoi(segments[3]); }
		else {
			if (++blanks == 3) {
				break; }}}

	unordered_map<int, Opcode> xlate;
	unordered_set<Opcode> unassigned;
	for (int i=0; i<16; i++) {
		const auto code = static_cast<Opcode>(i);
		unassigned.insert(code); }

	while (!unassigned.empty()) {

		vector<unordered_set<Opcode>> candidates(16);
		for (int i=0; i<16; i++) {
			auto& pack = candidates[i];
			pack.clear();
			for (const auto code : unassigned) {
				pack.insert(code); }}

		for (int i=0; i<16; i++) {
			if (xlate.find(i) == xlate.end()) {
				for (const auto& sample : opcodeSamples[i]) {
					for (const auto& code : unassigned) {
						auto result = execute(sample.before, code, sample.a, sample.b, sample.c);
						if (result.r != sample.after.r) {
							candidates[i].erase(code); }}}}}

		for (int i=0; i<16; i++) {
			if (xlate.find(i) == xlate.end()) {
				if (candidates[i].size() == 1) {
					for (const auto& code : candidates[i]) {
						xlate[i] = code;
						unassigned.erase(code); }}}}}

	assert(xlate.size() == 16);

	CPU cpu;
	while (getline(cin, line)) {
		auto segments = split(line, ' ');
		const auto opcode = xlate[stoi(segments[0])];
		const int a = stoi(segments[1]);
		const int b = stoi(segments[2]);
		const int c = stoi(segments[3]);
		cpu = execute(cpu, opcode, a, b, c); }

	cout << cpu.r[0] << "\n";
	return 0; }
