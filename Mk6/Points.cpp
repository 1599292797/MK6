#include "Points.h"

Point::Point() { this->dim = 0; }

Point::Point(unsigned int dim, ...)
{
    this->dim = dim;
    va_list vl;
    va_start(vl, dim);
    for (unsigned int i = 0; i < dim; i++)
        this->point.push_back(va_arg(vl, double));
    va_end(vl);
}

Point::Point(const Point& p)
{
    this->dim = p.dim;
    this->point = p.point;
}

Point::~Point()
{
}

unsigned int Point::Dim() { return this->dim; }

void Point::SetData(unsigned int dim, ...)
{
    this->dim = dim;
    va_list vl;
    va_start(vl, dim);
    for (unsigned int i = 0; i < dim; i++)
        this->point.push_back(va_arg(vl, double));
    va_end(vl);
}

double Point::X() { return point[0]; }

double Point::Y() { return point[1]; }

double Point::Z() throw(out_of_range)
{
    if (dim == 3)
        return point[2];
    else
        throw out_of_range("二维点不存在Z坐标");
}
