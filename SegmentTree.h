#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>

class SegmentTree {
public:
	SegmentTree(const std::vector<int>& data);
	long long get(int index_v, int v_l, int v_r, int l, int r);
	void push(int index_v, int vr, int vl);
	void set_value(int v, int vl, int vr, int l, int r, int x);
private:
	void build(int index, int l, int r);
	size_t n;
	std::vector<int> data;
	std::vector <long long> segment_tree_array;
	std::vector<long long> postponed_change;
};


SegmentTree::SegmentTree(const std::vector<int>& data)
	: n(data.size()), data(data), segment_tree_array(n * 4), postponed_change(n * 4) {

	build(1, 0, data.size() - 1);
}


void SegmentTree::build(int index, int l, int r) {
	if (r == l) {
		segment_tree_array[index] = data[l];
	}
	else {
		int m = (r + l) / 2;
		build(2 * index, l, m);
		build(2 * index + 1, m + 1, r);
		segment_tree_array[index] = segment_tree_array[index * 2] + segment_tree_array[index * 2 + 1];
	}
}

long long SegmentTree::get(int index_v, int v_l, int v_r, int l, int r) {
	push(index_v, v_r, v_l);
	if (v_r < l || r < v_l) return 0;
	if (l <= v_l and v_r <= r) return segment_tree_array[index_v];

	int v_m = (v_l + v_r) / 2;
	long long res1 = get(index_v * 2, v_l, v_m, l, r);
	long long res2 = get(index_v * 2 + 1, v_m + 1, v_r, l, r);
	return res1 + res2;
}


void SegmentTree::push(int index_v, int vr, int vl) {
	if (postponed_change[index_v] == 0) return;
	segment_tree_array[index_v] += postponed_change[index_v] * (vr - vl + 1);
	if (vr != vl) {
		postponed_change[2 * index_v] += postponed_change[index_v];
		postponed_change[2 * index_v + 1] += postponed_change[index_v];
	}
	postponed_change[index_v] = 0;
}

void SegmentTree::set_value(int v, int vl, int vr, int l, int r, int x) {
	if (vr < l || r < vl) return;
	if (l <= vl and vr <= r) {
		postponed_change[v] += x; return;
	}
	int vm = (vl + vr) / 2;
	set_value(2 * v, vl, vm, l, r, x);
	set_value(2 * v + 1, vm + 1, vr, l, r, x);

	segment_tree_array[v] = segment_tree_array[2 * v + 1] + postponed_change[2 * v + 1]
		+ segment_tree_array[2 * v] + postponed_change[2 * v];
}

//int main() {
//	std::vector<int> data = { 1, 2, 3, INT_MAX , INT_MAX };
//	SegmentTree tree(data);
//	std::cout << tree.get(1, 0, data.size() - 1, 3, 4) << '\n';
//	tree.set_value(1, 0, data.size() - 1, 3, 3, 10);
//	std::cout << tree.get(1, 0, data.size() - 1, 3, 4);
//}