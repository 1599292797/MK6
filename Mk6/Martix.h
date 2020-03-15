//此文件为矩阵类声明

#pragma once
#include"Head.h"

class Martix
{
private:
    unsigned int x, y;//矩阵行列数
    vector<vector<double>> martix;//矩阵数据区
public:
    //构造函数
    Martix();
    //构造x行y列空矩阵
    Martix(unsigned int x, unsigned int y); 
    //若矩阵m==n且flag==true则创建单位矩阵，
    //若m!=n且m/n==1且flag==true则创建1/n维元素数全为1的矩阵
    //否则抛出异常
    Martix(unsigned int x, unsigned int y, bool flag)throw(out_of_range);
    //析构函数
    ~Martix();
    //复制构造函数
    Martix(const Martix& m);
    //获取矩阵行列数
    unsigned int row()const;
    unsigned int col()const;
    //更新行列数
    void updatasize();
    //修改矩阵x行y列的数据为dt,若xy不在矩阵内，抛出异常
    void SetData(unsigned int x, unsigned int y, double dt)throw(out_of_range);
    //选择添加一行/列数据,true表示添加一行
    //若待添加数据数目不等于矩阵列/列数,则抛出异常
    void SetData(vector<double> dt, bool flag)throw(range_error);
    //获取矩阵元素值
    double GetData(unsigned int x, unsigned int y)throw(out_of_range);
    //在矩阵上，下，左，右方连接M
    void UpConnect(Martix M)throw(out_of_range);
    void DownConnect(Martix M)throw(out_of_range);
    void LeftConnect(Martix M)throw(out_of_range);
    void RightConnect(Martix M)throw(out_of_range);
    //矩阵求逆
    Martix Inverse();
    //矩阵转置
    Martix Transposition();
    //矩阵相乘,true表示当前矩阵左乘mar2
    Martix Multiplicte(Martix mar2,bool flag);
};
