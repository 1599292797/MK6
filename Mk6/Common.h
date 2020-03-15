#pragma once
#include "Head.h"
#include "Points.h"
#include "Degree.h"

//�ж��Ƿ�δ��������,δ����Ϊ��
bool ISNULL(double data);
bool ISNULL(double* data);
bool ISNULL(string data);
bool ISNULL(Point data);
bool ISNULL(Degree data);
bool ISNULL(vector<Point> data);
bool ISNULL(vector<Degree> data);

//������������
int Error_Report(exception& e, MessageBoxFlags MBF);