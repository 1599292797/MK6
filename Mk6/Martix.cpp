//���ļ�Ϊ������ʵ��

//�쳣��ȡ
//��λ�����ʼ��
//SetData��ֵ
//GetDataԪ�ػ�ȡ
#include "Martix.h"

Martix::Martix():x(0),y(0){}

Martix::Martix(unsigned int x, unsigned int y)
{
    this->x = x;
    this->y = y;
    this->martix.resize(x);
    for (unsigned int i = 0; i < x; i++)
        this->martix[i].resize(y);
}

Martix::Martix(unsigned int x, unsigned int y, bool flag)throw(out_of_range)
{
    if (x != y) {
        throw out_of_range("�������������ȣ��޷�������λ���󣬾��󴴽�ʧ��");
    }
    this->x = x;
    this->y = y;
    if (x == 1 && flag) {
        this->martix.resize(1);
        for (unsigned int i = 0; i < x; i++)
            this->martix[0].push_back(1);
    }
    else
        this->martix.resize(x);
    for (unsigned int i = 0; i < x; i++) {
        if (y == 1 && flag)
            this->martix[i].push_back(1);
        else
            this->martix[i].resize(y);
        if (flag && x != 1 && y != 1)
            for (unsigned int j = 0; j < y; j++) {
                if (i == j) {
                    this->martix[i][j] = 1;
                    break;
                }
            }
    }
}

Martix::~Martix()
{
    for (unsigned int i = 0; i < x; i++)
        this->martix[i].resize(0);
    this->martix.resize(0);
    this->x = 0;
    this->y = 0;
}

Martix::Martix(const Martix& p)
{
    this->martix = p.martix;
    updatasize();
}

inline unsigned int Martix::row()const { return x; }

inline unsigned int Martix::col()const { return y; }

void Martix::updatasize()
{
    this->x = martix.size();
    this->y = martix[0].size();
}

void Martix::SetData(unsigned int x, unsigned int y, double dt)throw(out_of_range)
{
    if (x >= this->x || y >= this->y) {
        throw out_of_range("���޸�Ԫ��λ�ó�������Χ");
    }
    this->martix[x][y] = dt;
}

void Martix::SetData(vector<double> dt,bool flag)throw(range_error)
{
   if (flag) {
       if (dt.size() != this->col()&&this->row())
           throw range_error("�����������Ŀ�����ھ�������");
       this->martix.push_back(dt);
   }
   else {
       if (dt.size() != this->row() && this->col())
           throw range_error("�����������Ŀ�����ھ�������");
       vector<double>::iterator it;
       vector<vector<double>>::iterator it2;
       for (it = dt.begin(), it2 = this->martix.begin(); it < dt.end(); it++, it2++)
           (*it2).push_back(*it);
   }
   updatasize();
}

double Martix::GetData(unsigned int x, unsigned int y)throw(out_of_range)
{
    if (x >= this->x || y >= this->y) 
        throw out_of_range("Ҫ��ȡ��Ԫ��λ�ó�������Χ");
    return this->martix[x][y];
}

void Martix::UpConnect(Martix M)throw(out_of_range) {
    if (this->col() != M.col())
        throw out_of_range("�����Ӿ�����������������");
    for (unsigned int i = 1; i <= M.row(); i++)
        this->martix.insert(this->martix.begin(), *(M.martix.end() - i));
}

void Martix::DownConnect(Martix M)throw(out_of_range) {
    if (this->col() != M.col())
        throw out_of_range("�����Ӿ�����������������");
    for (unsigned int i = 0; i < M.row(); i++)
        this->martix.insert(this->martix.end(), *(M.martix.begin() + i));
}

void Martix::LeftConnect(Martix M)throw(out_of_range) {
    if (this->row() != M.row())
        throw out_of_range("�����Ӿ�����������������");
    for (unsigned int i = 0; i < M.row(); i++)
        for (unsigned int j = 0; i < M.col(); j++)
            this->martix[i].insert(this->martix[i].begin(), M.martix[i][j]);
}

void Martix::RightConnect(Martix M)throw(out_of_range) {
    if (this->row() != M.row())
        throw out_of_range("�����Ӿ�����������������");
    for (unsigned int i = 0; i < M.row(); i++)
        for (unsigned int j = 0; i < M.col(); j++)
            this->martix[i].insert(this->martix[i].end(), M.martix[i][j]);
}

Martix Martix::Inverse()
{
    int m = this->row();//��ȡ��������
    int n = this->col();//��ȡ��������
    int i, j, k;
    double bs;
    //��ʼ��һ��m*2n�ľ���
    Martix array(m, 2 * n);
    //��ԭʼ��������¾����ǰ�벿��
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            array.martix[i][j] = this->martix[i][j];
    //���¾���ĺ�벿�ֻ�Ϊ��λ����
    for (i = 0; i < m; i++)
        for (j = n; j < 2 * n; j++)
            if ((j - i) == m)
                array.martix[i][j] = 1;
    //��ʼ���о��������
    for (i = 0; i < m; i++)
    {
        if (array.martix[i][i] != 1)
        {
            bs = array.martix[i][i];
            array.martix[i][i] = 1;
            for (j = i + 1; j < 2 * n; j++)
                array.martix[i][j] /= bs;
        }
        for (k = 0; k < m; k++)
        {
            if (k != i)
            {
                bs = array.martix[k][i];
                for (j = 0; j < 2 * n; j++)
                {
                    array.martix[k][j] -= bs * array.martix[i][j];
                }
            }
        }
    }
    Martix NI(m, n); 
    for (i = 0; i < m; i++)
        for (j = n; j < 2 * n; j++)
            NI.martix[i][j - n] = array.martix[i][j];
    return NI;//�����������
}

Martix Martix::Transposition()
{
    Martix result(this->col(), this->row());
    for (unsigned int i = 0; i < this->row(); i++)
        for (unsigned int j = 0; j < this->col(); j++)
            result.martix[j][i] = this->martix[i][j];
    return result;
}

Martix Martix::Multiplicte(Martix mar2, bool flag)
{
    unsigned int i, j, k;
    if (!flag) {
        Martix result(this->row(), mar2.col());
        for (i = 0; i < this->row(); i++)
            for (j = 0; j < mar2.col(); j++)
                for (k = 0; k < mar2.row(); k++)
                    result.martix[i][j] += this->martix[i][k] * mar2.martix[k][j];
        return result;
    }
    else {
        Martix result(mar2.row(), this->col());
        for (i = 0; i < mar2.row(); i++)
            for (j = 0; j < this->col(); j++)
                for (k = 0; k < this->row(); k++)
                    result.martix[i][j] += this->martix[i][k] * mar2.martix[k][j];
        return result;
    }
}
