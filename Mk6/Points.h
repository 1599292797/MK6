//���ļ�Ϊ���������

//�쳣��ȡ
//��ȡZ����

#pragma once
#include "Head.h"

//������
class Point
{
protected:
	unsigned int dim;//���ά��
	vector<double> point;//������
public:
	//���캯��
	Point();
	//����һ��dimά������Ϊpoint�ĵ�
	Point(unsigned int dim, vector<double> point) :point(point), dim(dim) {}
	//����һ��dimά������Ϊ��εĵ�
	Point(unsigned int dim, ...);
	//���ƹ��캯��
	Point(const Point& p);
	//��������
	~Point();
	//��ȡ��ά��
	unsigned int Dim(); 
	//����/���ĵ�����
	void SetData(unsigned int dim, ...);
	//��ȡX��Y���꣬��dim==3,��ȡZ����
	double X(); 
	double Y(); 
	double Z() throw(out_of_range);
};
