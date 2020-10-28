class TreapNode {
public:
	TreapNode* left;
	TreapNode* right;
	int size = 1;
	int data;
	ll y;
};

class Treap {
public:
	pair<TreapNode*, TreapNode*> split(TreapNode* node, int x);
	TreapNode* Merge(TreapNode* a, TreapNode* b);
	int get_index(TreapNode* node, int index);
private:
	int get_size(TreapNode* node);
	void update_size(TreapNode* node);
};

void Treap::update_size(TreapNode* node) {
	if (!node) {
		return;
	}
	node->size = get_size(node->left) + get_size(node->right) + 1;
}

int Treap::get_size(TreapNode* node) {
	if (node) {
		return node->size;
	}
	return 0;
}

pair<TreapNode*, TreapNode*> Treap::split(TreapNode* node, int x) {
	if (node == nullptr) {
		return { nullptr, nullptr };
	}
	pair<TreapNode*, TreapNode*> ans;
	int index = get_size(node->left);

	if (index + 1 < x) {
		ans = split(node->right, x - index - 1);
		node->right = ans.first;
		update_size(node);
		return { node, ans.second };
	}
	else {
		ans = split(node->left, x);
		node->left = ans.second;
		update_size(node);
		return { ans.first, node };
	}
}

int Treap::get_index(TreapNode* node, int index) {
	int left_index = get_size(node->left);

	if (left_index + 1 == index) {
		return node->data;
	}
	if (index <= left_index) {
		return get_index(node->left, index);
	}
	else {
		return get_index(node->right, index - left_index - 1);
	}
}

TreapNode* Treap::Merge(TreapNode* a, TreapNode* b) {
	if (a == nullptr) {
		return b;
	}
	if (b == nullptr) {
		return a;
	}

	if (a->y < b->y) {
		a->right = Merge(a->right, b);
		update_size(a);
		return a;
	}
	else {
		b->left = Merge(a, b->left);
		update_size(b);
		return b;
	}
}