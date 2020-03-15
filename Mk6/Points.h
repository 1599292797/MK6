//此文件为点类的声明

//异常获取
//获取Z坐标

#pragma once
#include "Head.h"

//单点类
class Point
{
protected:
	unsigned int dim;//点的维度
	vector<double> point;//点坐标
public:
	//构造函数
	Point();
	//构造一个dim维点坐标为point的点
	Point(unsigned int dim, vector<double> point) :point(point), dim(dim) {}
	//构造一个dim维，坐标为变参的点
	Point(unsigned int dim, ...);
	//复制构造函数
	Point(const Point& p);
	//析构函数
	~Point();
	//获取点维度
	unsigned int Dim(); 
	//设置/更改点坐标
	void SetData(unsigned int dim, ...);
	//获取X，Y坐标，若dim==3,获取Z坐标
	double X(); 
	double Y(); 
	double Z() throw(out_of_range);
};
