#pragma once
class Node
{
public:
	Node(double t, long ID);
	Node(double t, long ID, double q, double alfa_d_t);
	~Node();

private:
	long ID;
	double t;
	double q;
	double alfa_d_t;
};

