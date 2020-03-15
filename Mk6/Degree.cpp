//此文件为弧度类实现
#include "Degree.h"

Degree::Degree() { this->degree = 0; }

Degree::Degree(double degree, bool flag)
{
	if (flag)
		this->degree = degree;
	else
		this->degree = PI * degree / 180;
}

Degree::Degree(double degree, double minute, double second)
{
	this->degree = PI / 180 * (degree + minute / 60 + second / 3600);
}

Degree::Degree(const Degree& p):degree(p.degree)
{
}

Degree::~Degree()
{
}
