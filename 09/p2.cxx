#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


struct Node {
	int64_t num = -1;
	Node* next = nullptr;
	Node* prev = nullptr; };

vector<Node> nodepile;
int ni = 0;

Node *make_node(int num) {
	Node* n = &nodepile[ni++];
	n->num = num;
	return n; }


int main() {
	nodepile.reserve(80000*100);
	ni = 0;

	const int numPlayers = 435;
	const int lastMarble = 71184 * 100;

	Node *cm = make_node(0);
	cm->next = cm;
	cm->prev = cm;
	Node *head = cm;
	Node *tail = cm;


	auto printCircle = [&]() {
		Node *pos = head;
		while (1) {
			cout << pos->num << " ";
			if (pos->next == head) {
				break; }
			pos = pos->next; }
		cout << "\n"; };


	auto placeMarble1 = [&](int64_t num) {
		cm = cm->next;
		Node *tmp = make_node(num);
		cm->next->prev = tmp;
		tmp->next = cm->next;
		tmp->prev = cm;
		cm->next = tmp;
		cm = tmp;};

	vector<int64_t> scores(numPlayers, 0);

	int player = 1;
	for (int64_t m=1; m<=lastMarble; m++) {
		if (m%10000==0) {
			cout << "." << flush; }
		if (m%23 == 0) {
			scores[player] += m;

			cm = cm->prev->prev->prev->prev->prev->prev->prev;
			scores[player] += cm->num;
			cm->prev->next = cm->next;
			cm->next->prev = cm->prev;
			cm = cm->next; }
		else {
			placeMarble1(m); }

		//printCircle();

		if (++player > numPlayers) {
			player = 1; }}

	sort(scores.begin(), scores.end());
	cout << scores.back() << endl;
	//printCircle();
	return 0; }
