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

	CPU before;
	int opcode, a, b, c;
	int hits = 0;
	while (getline(cin, line)) {
		if (line.substr(0,6) == "Before") {
			auto segments = split(line, '[');
			segments = split(segments[1], ' ');
			before.r[0] = stoi(segments[0]);
			before.r[1] = stoi(segments[1]);
			before.r[2] = stoi(segments[2]);
			before.r[3] = stoi(segments[3]); }
		else if (line.substr(0,5) == "After") {
			CPU after;
			auto segments = split(line, '[');
			segments = split(segments[1], ' ');
			after.r[0] = stoi(segments[0]);
			after.r[1] = stoi(segments[1]);
			after.r[2] = stoi(segments[2]);
			after.r[3] = stoi(segments[3]);

			int many = 0;
			for (int i=0; i<16; i++) {
				auto testOpcode = static_cast<Opcode>(i);
				auto result = execute(before, testOpcode, a, b, c);
				if (result.r == after.r) {
					many++; }}
			if (many >= 3) {
				//cout << "x" << flush;
				hits++; }
			else {
				//cout << "." << flush;
				}
			// process...
		}
		else if (line.length()) {
			auto segments = split(line, ' ');
			opcode = stoi(segments[0]);
			a = stoi(segments[1]);
			b = stoi(segments[2]);
			c = stoi(segments[3]); }}

	cout << hits << "\n";
	return 0; }
