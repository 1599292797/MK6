//�������߼���������
//level���map

#pragma once
#include"Head.h"
#include"Common.h"
#include"MeasureData.h"

//����������
class TransitionCurve {
protected:
	Point ZH, HY;//ֱ����ͻ�Բ������
	Degree Azimuth;//ֱ�������߷�λ��
	double Lzh, Lhy;//ֱ����,��Բ�����
	double R;//Բ���߰뾶
	bool Dir;//���߷�����תΪtrue
	MeasureData Result;
public:
	//���캯��
	TransitionCurve(
		Point ZH,
		Point HY, 
		double Lzh,
		double Lhy,
		Degree Azimuth, 
		double R, 
		bool Dir);
	//���ƹ��캯��
	TransitionCurve(TransitionCurve& p);
	//��������
	~TransitionCurve();
};

//���������,�����ڻ���������
class TransitionCurve_OnePoint:public TransitionCurve {
protected:
	double Ls;//��������
	void CheckData()throw(invalid_argument);
public:
	//���캯��
	TransitionCurve_OnePoint(
		Point ZH,
		Point HY, 
		double Lzh,
		double Lhy,
		double Ls, 
		Degree Azimuth,
		double R, 
		bool Dir);
	//���ƹ��캯��
	TransitionCurve_OnePoint(TransitionCurve_OnePoint& p);
	//��������
	~TransitionCurve_OnePoint();
	//����
	void Calculate();
};

//�������࣬�����ڵ��������
class TransitionCurve_MorePoints:public TransitionCurve_OnePoint {
protected:
	double LC, LE;//����㣬�������
	double Mile;//��λ���
	void CheckData()throw(invalid_argument);
public:
	//���캯��
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
	//���ƹ��캯��
	TransitionCurve_MorePoints(TransitionCurve_MorePoints& p);
	//��������
	~TransitionCurve_MorePoints();
	//����
	void Calculate();
};

//�����
class Level :public Martix {
private:
	unsigned int count = 0;//ת����
	Martix KB;//������߼�����k,b��һ��
	//��߲�������
	void HeightLaw();
	void SolveEquations_2_1(int loc);
public:
	//���캯��
	Level() {}
	Level(unsigned int count, ...);
	//���ƹ��캯��
	Level(Level& p);
	//��������
	~Level();
	//��ȡlocλ�õ���̣������ڷ�Χ���׳��쳣
	double Mile(unsigned int loc)throw(out_of_range);
	//��ȡlocλ�õı�ߣ������ڷ�Χ���׳��쳣
	double Height(unsigned int loc)throw(out_of_range);
};

//���ݼ���࣬�̳��ڶ�������
class TransitionCurve_SegmentCheck :
	public TransitionCurve_MorePoints,
	public MeasureData 
{
protected:
	MeasureData measure;//�������ݣ���ά����
	Level Height;//�������
	vector<double> Tolerance;//��ά�޲�
	//�������ݲ��죬���Ϊ10�����ݴ洢��Result��
	//ǰ����Ϊ���ֵ���м�����Ϊ����ֵ��������Ϊ��ֵ���ֱ�ΪX,Y,Hֵ,���Ϊ���ݲ�ֵ�Ƿ���Ϲ涨
	void Compare();
	//���ݼ��
	void CheckData()throw(invalid_argument);
public:
	//���캯��
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
	//���ƹ��캯��
	TransitionCurve_SegmentCheck(TransitionCurve_SegmentCheck& p);
	//��������
	~TransitionCurve_SegmentCheck();
	//����
	//�������ݷ��ڻ���MeasureData��
	//�����������ݷ��ڻ���TransitionCurve��Result��
	void Calculate();
	//������
	void COUT();
};