//���ļ�Ϊ����������

#pragma once
#include"Head.h"

class Martix
{
private:
    unsigned int x, y;//����������
    vector<vector<double>> martix;//����������
public:
    //���캯��
    Martix();
    //����x��y�пվ���
    Martix(unsigned int x, unsigned int y); 
    //������m==n��flag==true�򴴽���λ����
    //��m!=n��m/n==1��flag==true�򴴽�1/nάԪ����ȫΪ1�ľ���
    //�����׳��쳣
    Martix(unsigned int x, unsigned int y, bool flag)throw(out_of_range);
    //��������
    ~Martix();
    //���ƹ��캯��
    Martix(const Martix& m);
    //��ȡ����������
    unsigned int row()const;
    unsigned int col()const;
    //����������
    void updatasize();
    //�޸ľ���x��y�е�����Ϊdt,��xy���ھ����ڣ��׳��쳣
    void SetData(unsigned int x, unsigned int y, double dt)throw(out_of_range);
    //ѡ�����һ��/������,true��ʾ���һ��
    //�������������Ŀ�����ھ�����/����,���׳��쳣
    void SetData(vector<double> dt, bool flag)throw(range_error);
    //��ȡ����Ԫ��ֵ
    double GetData(unsigned int x, unsigned int y)throw(out_of_range);
    //�ھ����ϣ��£����ҷ�����M
    void UpConnect(Martix M)throw(out_of_range);
    void DownConnect(Martix M)throw(out_of_range);
    void LeftConnect(Martix M)throw(out_of_range);
    void RightConnect(Martix M)throw(out_of_range);
    //��������
    Martix Inverse();
    //����ת��
    Martix Transposition();
    //�������,true��ʾ��ǰ�������mar2
    Martix Multiplicte(Martix mar2,bool flag);
};
