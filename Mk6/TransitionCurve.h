//缓和曲线计算类声明
//level类改map

#pragma once
#include"Head.h"
#include"Common.h"
#include"MeasureData.h"

//缓和曲线类
class TransitionCurve {
protected:
	Point ZH, HY;//直缓点和缓圆点坐标
	Degree Azimuth;//直缓点切线方位角
	double Lzh, Lhy;//直缓点,缓圆点里程
	double R;//圆曲线半径
	bool Dir;//曲线方向，左转为true
	MeasureData Result;
public:
	//构造函数
	TransitionCurve(
		Point ZH,
		Point HY, 
		double Lzh,
		double Lhy,
		Degree Azimuth, 
		double R, 
		bool Dir);
	//复制构造函数
	TransitionCurve(TransitionCurve& p);
	//析构函数
	~TransitionCurve();
};

//单点计算类,派生于缓和曲线类
class TransitionCurve_OnePoint:public TransitionCurve {
protected:
	double Ls;//待求点里程
	void CheckData()throw(invalid_argument);
public:
	//构造函数
	TransitionCurve_OnePoint(
		Point ZH,
		Point HY, 
		double Lzh,
		double Lhy,
		double Ls, 
		Degree Azimuth,
		double R, 
		bool Dir);
	//复制构造函数
	TransitionCurve_OnePoint(TransitionCurve_OnePoint& p);
	//析构函数
	~TransitionCurve_OnePoint();
	//计算
	void Calculate();
};

//多点计算类，派生于单点计算类
class TransitionCurve_MorePoints:public TransitionCurve_OnePoint {
protected:
	double LC, LE;//起算点，最终里程
	double Mile;//单位里程
	void CheckData()throw(invalid_argument);
public:
	//构造函数
	TransitionCurve_MorePoints(
		Point ZH,
		Point HY,
		double Lzh, 
		double Lhy, 
		Degree Azimuth, 
		double R,
		bool Dir,
		double LC,
		double LE,
		double Mile);
	//复制构造函数
	TransitionCurve_MorePoints(TransitionCurve_MorePoints& p);
	//析构函数
	~TransitionCurve_MorePoints();
	//计算
	void Calculate();
};

//标高类
class Level :public Martix {
private:
	unsigned int count = 0;//转点数
	Martix KB;//标高折线计算结果k,b各一行
	//标高参数计算
	void HeightLaw();
	void SolveEquations_2_1(int loc);
public:
	//构造函数
	Level() {}
	Level(unsigned int count, ...);
	//复制构造函数
	Level(Level& p);
	//析构函数
	~Level();
	//获取loc位置的里程，若不在范围内抛出异常
	double Mile(unsigned int loc)throw(out_of_range);
	//获取loc位置的标高，若不在范围内抛出异常
	double Height(unsigned int loc)throw(out_of_range);
};

//数据检核类，继承于多点计算类
class TransitionCurve_SegmentCheck :
	public TransitionCurve_MorePoints,
	public MeasureData 
{
protected:
	MeasureData measure;//测量数据，三维坐标
	Level Height;//标高数据
	vector<double> Tolerance;//三维限差
	//计算数据差异，结果为10列数据存储在Result中
	//前三列为设计值，中间三列为测量值，后三列为差值，分别为X,Y,H值,最后为数据差值是否符合规定
	void Compare();
	//数据检查
	void CheckData()throw(invalid_argument);
public:
	//构造函数
	TransitionCurve_SegmentCheck(
		Point ZH, 
		Point HY,
		double Lzh,
		double Lhy,
		double Ls, 
		Degree Azimuth, 
		double R, 
		bool Dir,
		double LC, 
		double LE, 
		double Mile, 
		Level Height,
		vector<double> Tolerance,
		initializer_list<string> FileData);
	//复制构造函数
	TransitionCurve_SegmentCheck(TransitionCurve_SegmentCheck& p);
	//析构函数
	~TransitionCurve_SegmentCheck();
	//计算
	//测量数据放在基类MeasureData中
	//计算所得数据放在基类TransitionCurve的Result中
	void Calculate();
	//结果输出
	void COUT();
};