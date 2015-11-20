#pragma once
class Node
{
public:
	Node(long ID);
	Node(long ID, double q, double alfa_d_t);
	~Node();

	void set_t(double t);

private:
	long ID;
	double t;
	double q;
	double alfa_d_t;
};

