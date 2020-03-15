//此文件为弧度类声明
#pragma once
#include"Head.h"

class Degree
{
protected:
	double degree;//弧度
public:
	//构造函数
	Degree();
	//degree为角度或弧度值，flag为true代表弧度
	Degree(double degree, bool flag);
	//度分秒构造函数
	Degree(double degree, double minute, double second);
	//复制构造函数
	Degree(const Degree& p);
	//析构函数
	~Degree();
	//获取弧度值
	double GetDegree() { return this->degree; }
};