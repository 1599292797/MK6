#pragma once
#include "Head.h"
#include "Points.h"
#include "Degree.h"

//判断是否未输入数据,未输入为是
bool ISNULL(double data);
bool ISNULL(double* data);
bool ISNULL(string data);
bool ISNULL(Point data);
bool ISNULL(Degree data);
bool ISNULL(vector<Point> data);
bool ISNULL(vector<Degree> data);

//报错及错误类型
int Error_Report(exception& e, MessageBoxFlags MBF);