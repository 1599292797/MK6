//拟合类声明
//包括圆心拟合，断面拟合
#pragma once
#include"Common.h"
#include"MeasureData.h"
#include"Points.h"

//拟合抽象类
class Fitting{
public:
    virtual void Calculate() = 0;//
    virtual void COUT() = 0;
    virtual void Draw() = 0;
};

//圆心拟合，派生于拟合类
class CenterOfCircle:public Fitting, public MeasureData
{
private:
    Point centerofcircle;//圆心坐标
    double R;//半径
    //圆心拟合数据检查
    void CheckData()throw(domain_error);
public:
    //构造函数
    CenterOfCircle(initializer_list<string> FileData);
    //复制构造函数
    CenterOfCircle(const CenterOfCircle& p);
    //析构函数
    ~CenterOfCircle();
    //圆心拟合计算
    void Calculate();
    //圆心拟合结果输出
    void COUT();
    //图像绘制
    void Draw();
};

//断面拟合，派生于拟合类
class Section:public Fitting, public MeasureData
{
private:
    vector<double> Param;//拟合方程AX+BY+CZ=1的结果A,B,C
    //数据检查
    void CheckData()throw(domain_error);
public:
    //构造函数
    Section(initializer_list<string> FileData);
    //复制构造函数
    Section(const Section& p);
    //析构函数
    ~Section();
    //拟合计算
    void Calculate();
    //结果输出
    void COUT();
    //图像绘制
    void Draw();
};

//计算函数
void Calculate(Fitting* ptr) {
    ptr->Calculate();
}

//结果输出函数
void COUT(Fitting* ptr) {
    ptr->COUT();
}

//图像绘制函数
void DRAW(Fitting* ptr) {
    ptr->Draw();
}