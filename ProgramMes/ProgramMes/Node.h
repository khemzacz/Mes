#pragma once
class Node
{
public:
	Node(long ID);
	Node(long ID, double q, double alfa_d_t);
	Node();
	~Node();

	void setT(double t);
	void setQ(double q);
	void setAlfaDT(double alfaDT);
	void setr(double);

	double getT();
	double getQ();
	double getAlfaDT();
	double getr();

private:
	long ID;
	double t;
	double q;
	double alfa_d_t;
	double r;
};

