//���������
//����Բ����ϣ��������
#pragma once
#include"Common.h"
#include"MeasureData.h"
#include"Points.h"

//��ϳ�����
class Fitting{
public:
    virtual void Calculate() = 0;//
    virtual void COUT() = 0;
    virtual void Draw() = 0;
};

//Բ����ϣ������������
class CenterOfCircle:public Fitting, public MeasureData
{
private:
    Point centerofcircle;//Բ������
    double R;//�뾶
    //Բ��������ݼ��
    void CheckData()throw(domain_error);
public:
    //���캯��
    CenterOfCircle(initializer_list<string> FileData);
    //���ƹ��캯��
    CenterOfCircle(const CenterOfCircle& p);
    //��������
    ~CenterOfCircle();
    //Բ����ϼ���
    void Calculate();
    //Բ����Ͻ�����
    void COUT();
    //ͼ�����
    void Draw();
};

//������ϣ������������
class Section:public Fitting, public MeasureData
{
private:
    vector<double> Param;//��Ϸ���AX+BY+CZ=1�Ľ��A,B,C
    //���ݼ��
    void CheckData()throw(domain_error);
public:
    //���캯��
    Section(initializer_list<string> FileData);
    //���ƹ��캯��
    Section(const Section& p);
    //��������
    ~Section();
    //��ϼ���
    void Calculate();
    //������
    void COUT();
    //ͼ�����
    void Draw();
};

//���㺯��
void Calculate(Fitting* ptr) {
    ptr->Calculate();
}

//����������
void COUT(Fitting* ptr) {
    ptr->COUT();
}

//ͼ����ƺ���
void DRAW(Fitting* ptr) {
    ptr->Draw();
}