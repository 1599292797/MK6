//���ļ�Ϊ����������
#pragma once
#include"Head.h"

class Degree
{
protected:
	double degree;//����
public:
	//���캯��
	Degree();
	//degreeΪ�ǶȻ򻡶�ֵ��flagΪtrue������
	Degree(double degree, bool flag);
	//�ȷ��빹�캯��
	Degree(double degree, double minute, double second);
	//���ƹ��캯��
	Degree(const Degree& p);
	//��������
	~Degree();
	//��ȡ����ֵ
	double GetDegree() { return this->degree; }
};