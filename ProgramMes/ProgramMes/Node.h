#pragma once
class Node
{
public:
	Node(long ID);
	Node(long ID, double q, double alfa_d_t);
	Node();
	~Node();

	void setTemp(double t);
	void setQ(double q);
	void setAlfaDT(double alfaDT);
	void setr(double);

	double getTemp();
	double getQ();
	double getAlfaDT();
	double getr();

	void free();
private:
	long ID;
	double t;
	double q;
	double alfa_d_t;
	double r;
};

