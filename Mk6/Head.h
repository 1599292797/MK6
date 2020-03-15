//此文件用于全局变量的声明与定义，头文件引用
//包括计算模式的声明与定义，报错函数
#pragma once
#pragma warning( disable : 4290 )

#include<iostream>
#include<vector>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<cmath>
#include<cstdarg>
#include<Windows.h>

using namespace std;

#ifndef PI
#define PI 3.1415926535898
#endif // !PI

//拟合模式
enum Fitting_Mode { CenterOfCircle, Section };
//缓和曲线计算模块
enum Transition_Mode { OnePoint, MorePoints, SegmentCheck };
//交会计算模块
enum Intersection_Mode { Fore, Side, Post };
//弹窗格式
enum MessageBoxFlags { OK, OKCANCEL, ABORTRETRYIGNORE, YESNOCANCEL, YESNO, RETRYCANCEL };
