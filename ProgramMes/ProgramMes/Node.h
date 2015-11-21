#pragma once
class Node
{
public:
	Node(long ID);
	Node(long ID, double q, double alfa_d_t);
	~Node();

	void setT(double t);
	void setQ(double q);
	void setAlfaDT(double alfaDT);

	double getT();
	double getQ();
	double getAlfaDT();

private:
	long ID;
	double t;
	double q;
	double alfa_d_t;
};

