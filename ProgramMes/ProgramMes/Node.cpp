#include "Node.h"



Node::Node(long ID)
{
	this->ID = ID;
}

Node::Node(long ID, double q, double alfa_d_t)
{
	this->ID = ID;

}

Node::Node()
{
}

Node::~Node()
{
}

void Node::setT(double t)
{
	this->t = t;
}

void Node::setAlfaDT(double alfaDT)
{
	this->alfa_d_t = alfaDT;
}

void Node::setr(double sample_double)
{
	this->r = sample_double;
}

void Node::setQ(double q)
{
	this->q = q;
}


double Node::getT()
{
	return (this->t);
}

double Node::getAlfaDT()
{
	return (this->alfa_d_t);
}

double Node::getr()
{
	return (this->r);
}

double Node::getQ()
{
	return(this->q);
}

