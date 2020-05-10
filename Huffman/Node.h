#pragma once
class Node
{
	int frequency;
	char letter;
	Node *childLeft, *childRight;
public:
	Node(){}

	Node(Node *left, Node *right)
	{
		this->childLeft = left;
		this->childRight = right;
		this->frequency = left->getFrequency() + right->getFrequency();
	}

	void setValue(int frequency, char letter)
	{
		this->frequency = frequency;
		this->letter = letter;
	}

	int getFrequency()
	{
		return frequency;
	}

	char getLetter()
	{
		return letter;
	}

	Node* getLeftChild()
	{
		return childLeft;
	}

	Node* getRightChild()
	{
		return childRight;
	}
};

