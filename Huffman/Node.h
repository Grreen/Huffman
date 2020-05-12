#pragma once
class Node
{
	int frequency;
	char letter;
	Node *childLeft, *childRight;
public:
	Node();
	Node(Node* left, Node* right);

	void setValue(int frequency, char letter);
	int getFrequency();
	char getLetter();

	Node* getLeftChild();
	Node* getRightChild();
};

