//此文件用于交会计算类声明
//包括前方，侧方，后方交会

#pragma once
#include"Head.h"
#include"Points.h"
#include"Degree.h"

//交会类
class Intersection {
protected:
	Point A, B;//点A,B
	vector<Point>  Result;//计算结果
public:
	//构造函数
	Intersection(Point A, Point B):A(A),B(B),Result(){}
	//复制构造函数
	Intersection(const Intersection& p);
	//析构函数
	~Intersection();
};

//前方交会派生于交会类
class Intersection_Fore :public Intersection {
protected:
	vector<Degree> PAB, PBA;//角PAB, PBA弧度
	vector<double> Accuracy;//精度分析结果
public:
	//构造函数
	Intersection_Fore(Point A, Point B, vector<Degree> PAB, vector<Degree> PBA);
	//复制构造函数
	Intersection_Fore(const Intersection_Fore& p);
	//析构函数
	~Intersection_Fore();
	//前方交会计算
	//测量坐标系下，A、B、P 顺时针排列时，sign = 1；
	//A、B、P 逆时针排列时，sign = -1。
	void Calculate(vector<bool> sign);
	//单点计算
	void Calculate(int loc, bool sign);
	//精度分析
	double PrecisionAnalysis();
};

//侧方交会，派生于前方交会
class Intersection_Side:public Intersection_Fore{
private:
	vector<Degree> APB;//角APB弧度
	//计算第三个角弧度
	vector<Degree> DegreeCalculate(vector<Degree> degree1, vector<Degree> degree2);
public:
	//构造函数
	Intersection_Side(Point A, Point B, vector<Degree> PAB, vector<Degree> PBA);
	//复制构造函数
	Intersection_Side(const Intersection_Side& p);
	//析构函数
	~Intersection_Side();
	//侧方交会计算,sign含义与前方交会一样
	void Calculate(vector<bool> sign);
};

//后方交会，派生于交会类
class Intersection_Post:public Intersection {
private:
	Point C;//C坐标
	vector<Degree> APC, APB;//角APC, APB弧度
public:
	//构造函数
	Intersection_Post(Point A, Point B, Point C, vector<Degree> APC, vector<Degree> APB);
	//复制构造函数
	Intersection_Post(const Intersection_Post& p);
	//析构函数
	~Intersection_Post();
	//后方交会计算
	void Calculate();
};

