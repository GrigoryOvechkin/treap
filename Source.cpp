#include <iostream>

using namespace std;

#define mp make_pair

struct Node
{
	Node *left, *right;
	long long value, cnt, y;
	Node() {}
	Node(long long value)
	{
		this->value = value;
		left = right = NULL;
		y = (rand() << 16) ^ rand();
		cnt = 1;
	}
};

Node* nulltree = NULL;

int cnt(Node* tree) //counting vertexes in a tree
{
	if (tree == NULL)
		return 0;
	return tree->cnt;
}

int index(Node* tree)
{
	if (tree == NULL)
		return -1;
	return cnt(tree->left);
}

void update (Node* tree) //updating information about vertex via its child 
{
	tree->cnt = cnt(tree->left) + cnt(tree->right) + 1;
}

Node* merge (Node* left_tree, Node* right_tree) //merging two trees
{
	if (left_tree == NULL)
		return right_tree;
	if (right_tree == NULL)
		return left_tree;
	if (left_tree->y > right_tree->y)
	{
		left_tree->right = merge(left_tree->right, right_tree);
		update(left_tree);
		return left_tree;
	}
	right_tree->left = merge(left_tree, right_tree->left);
	update(right_tree);
	return right_tree;
}

pair<Node*, Node*> split (Node* tree, int num) //spliting tree by number
{                                              //giving number will be the last in left part
	if (tree == NULL)                          //numeration starts from 0
		return mp(nulltree, nulltree);
	if (index(tree) <= num)
	{
		auto tt = split(tree->right, num - index(tree) - 1);
		tree->right = tt.first;
		return mp(tree, tt.second);
	}
	auto tt = split(tree->left, num);
	tree->left = tt.second;
	return mp(tt.first, tree);
}

Node* insert (Node* tree, int value, int num) //inserting an element by its value and number
{                                             //if there is no such number in trees, element will be added in the nearest place
	auto tt = split(tree, num - 1);
	Node* new_elem = new Node(value);
	tt.first = merge(tt.first, new_elem);
	tree = merge(tt.first, tt.second);
	return tree;
}

Node* erase (Node* tree, int num) //erasing an element by number
{                                 //if there is no such number, nothing will be erased
	auto tt = split(tree, num);
	auto tt2 = split(tt.first, num - 1);
	tree = merge(tt2.first, tt.second);
	return tree;
}

void print_tree (Node* tree) //in-order printing tree in line 
{
	if (tree == NULL)
		return;
	print_tree(tree->left);
	cout << tree->value << ' ';
	print_tree(tree->right);
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	Node* my_tree = NULL;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int val, num;
		cin >> val >> num;
		my_tree = insert(my_tree, val, num);
		print_tree(my_tree);
		cout << "\n";
	}
	for (int i = 0; i < n - 5; ++i)
	{
		my_tree = erase(my_tree, 0);
		print_tree(my_tree);
		cout << "\n";
	}
	
	my_tree = erase(my_tree, -1);
	print_tree(my_tree);
	cout << "\n";
	my_tree = erase(my_tree, 3);
	print_tree(my_tree);
	cout << "\n";
	
	return 0;
}