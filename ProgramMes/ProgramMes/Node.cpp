#include "Node.h"



Node::Node(long ID)
{
	this->ID = ID;
}

Node::Node(long ID, double q, double alfa_d_t)
{
	this->ID = ID;

}

Node::~Node()
{
}

void Node::set_t(double t)
{
	this->t = t;
}