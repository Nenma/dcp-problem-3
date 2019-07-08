// SerializeAndDeserialize.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Node {
public:
	string val;
	Node* left;
	Node* right;

	Node() {
		val = "";
		left = nullptr;
		right = nullptr;
	}

	Node(string val, Node* left, Node* right) {
		this->val = val;
		this->left = left;
		this->right = right;
	}
};

string text = "";

//preorder pass
string serialize(Node* root) {
	if (root != nullptr) {
		text.append(root->val);
		text.append("(");
		serialize(root->left);
		serialize(root->right);
		text.append(")");
	}
	return text;
}

Node* deserialize(string text) {
	Node* node = new Node();
	stack<Node*> statesStack;
	for (int i = 0; i < text.length(); i++) {
		if (node == nullptr) {
			node = new Node();
		}
		if (isalpha(text[i])) {
			node->val += text[i];
		}
		if (text[i] == '(') {
			statesStack.push(node);
			node = node->left;
		}
		if (text[i] == ')') {
			if (text[i] == '(') {
				node->left = nullptr;
				node->right = nullptr;
				statesStack.pop();
				node = statesStack.top();
			}
			if (text[i] == ')') {
				node->right = nullptr;
				statesStack.pop();
				node = statesStack.top();
			}
		}

	}
	return node;
}


int main()
{
	Node* node = new Node("root", new Node("left", new Node("left.left", nullptr, nullptr), nullptr), new Node("right", nullptr, nullptr));
	cout << serialize(node) << endl;

	string test = "root(left(left.left()left.right())right(right.left()right.right()))";
	cout << serialize(deserialize(test)) << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
