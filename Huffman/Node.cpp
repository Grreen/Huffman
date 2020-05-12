#include "Node.h"

Node::Node()
{
}

Node::Node(Node* left, Node* right)
{
	this->childLeft = left;
	this->childRight = right;
	this->frequency = left->getFrequency() + right->getFrequency();
}

void Node::setValue(int frequency, char letter)
{
	this->frequency = frequency;
	this->letter = letter;
}

int Node::getFrequency()
{
	return frequency;
}

char Node::getLetter()
{
	return letter;
}

Node* Node::getLeftChild()
{
	return childLeft;
}

Node* Node::getRightChild()
{
	return childRight;
}
