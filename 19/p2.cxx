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
	array<int, 6> r = {0,0,0,0,0,0}; };


enum Opcode {
	addr, addi,
	mulr, muli,
	banr, bani,
	borr, bori,
	setr, seti,
	gtir, gtri, gtrr,
	eqir, eqri, eqrr };


vector<string> opcodeText = {
	"addr", "addi",
	"mulr", "muli",
	"banr", "bani",
	"borr", "bori",
	"setr", "seti",
	"gtir", "gtri", "gtrr",
	"eqir", "eqri", "eqrr" };


Opcode decodeOpcodeText(const string& text) {
	for (int i=0; i<opcodeText.size(); i++) {
		if (opcodeText[i] == text) {
			return static_cast<Opcode>(i); }}
	return Opcode::addr; }


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


struct Inst {
	Opcode opcode;
	int a, b, c; };


int main() {
	string line;

	vector<Inst> mem;

	int ipreg = 0;
	while (getline(cin, line)) {
		auto segments = split(line, ' ');
		if (line[0] == '#') {
			ipreg = stoi(segments[1]); }
		else {
			auto opcode = decodeOpcodeText(segments[0]);
			int aa = stoi(segments[1]);
			int bb = stoi(segments[2]);
			int cc = stoi(segments[3]);
			mem.push_back({ opcode, aa, bb, cc });}}

	int ip = 0;
	CPU cpu;
	cpu.r[0] = 1;
	while (ip < mem.size() && ip >= 0) {
		cpu.r[ipreg] = ip;
		const auto& inst = mem[ip];
		cpu = execute(cpu, inst.opcode, inst.a, inst.b, inst.c);
		ip = cpu.r[ipreg];

		if (ip == 1) {
			//cout << "break at ip=1!\n";
			/*{bool x=true;
				for (const auto& n: cpu.r) {
					if (x) { x = false; cout << "[" << n;} else { cout << ", " << n; }} cout << "]\n";}*/
			break; }
		ip++; }

	//cout << "begin native factoring of r5..." << flush;
	int r5 = cpu.r[5];
	int ax = 0;
	for (int i=1; i<=sqrt(r5); i++) {
		if (r5%i == 0) {
			if (r5/i == i) {
				ax += i; }
			else {
				ax += i;
				ax += r5/i; }}}
	cout << ax << "\n";
	return 0; }
