//���ļ�����ȫ�ֱ����������붨�壬ͷ�ļ�����
//��������ģʽ�������붨�壬������
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

//���ģʽ
enum Fitting_Mode { CenterOfCircle, Section };
//�������߼���ģ��
enum Transition_Mode { OnePoint, MorePoints, SegmentCheck };
//�������ģ��
enum Intersection_Mode { Fore, Side, Post };
//������ʽ
enum MessageBoxFlags { OK, OKCANCEL, ABORTRETRYIGNORE, YESNOCANCEL, YESNO, RETRYCANCEL };
