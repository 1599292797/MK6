//���ļ����ڽ������������
//����ǰ�����෽���󷽽���

#pragma once
#include"Head.h"
#include"Points.h"
#include"Degree.h"

//������
class Intersection {
protected:
	Point A, B;//��A,B
	vector<Point>  Result;//������
public:
	//���캯��
	Intersection(Point A, Point B):A(A),B(B),Result(){}
	//���ƹ��캯��
	Intersection(const Intersection& p);
	//��������
	~Intersection();
};

//ǰ�����������ڽ�����
class Intersection_Fore :public Intersection {
protected:
	vector<Degree> PAB, PBA;//��PAB, PBA����
	vector<double> Accuracy;//���ȷ������
public:
	//���캯��
	Intersection_Fore(Point A, Point B, vector<Degree> PAB, vector<Degree> PBA);
	//���ƹ��캯��
	Intersection_Fore(const Intersection_Fore& p);
	//��������
	~Intersection_Fore();
	//ǰ���������
	//��������ϵ�£�A��B��P ˳ʱ������ʱ��sign = 1��
	//A��B��P ��ʱ������ʱ��sign = -1��
	void Calculate(vector<bool> sign);
	//�������
	void Calculate(int loc, bool sign);
	//���ȷ���
	double PrecisionAnalysis();
};

//�෽���ᣬ������ǰ������
class Intersection_Side:public Intersection_Fore{
private:
	vector<Degree> APB;//��APB����
	//����������ǻ���
	vector<Degree> DegreeCalculate(vector<Degree> degree1, vector<Degree> degree2);
public:
	//���캯��
	Intersection_Side(Point A, Point B, vector<Degree> PAB, vector<Degree> PBA);
	//���ƹ��캯��
	Intersection_Side(const Intersection_Side& p);
	//��������
	~Intersection_Side();
	//�෽�������,sign������ǰ������һ��
	void Calculate(vector<bool> sign);
};

//�󷽽��ᣬ�����ڽ�����
class Intersection_Post:public Intersection {
private:
	Point C;//C����
	vector<Degree> APC, APB;//��APC, APB����
public:
	//���캯��
	Intersection_Post(Point A, Point B, Point C, vector<Degree> APC, vector<Degree> APB);
	//���ƹ��캯��
	Intersection_Post(const Intersection_Post& p);
	//��������
	~Intersection_Post();
	//�󷽽������
	void Calculate();
};

