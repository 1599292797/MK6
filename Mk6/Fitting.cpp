//拟合类实现
//异常获取
//Calculate
#include "Fitting.h"

//返回值为圆心坐标X,Y,Z和半径R
CenterOfCircle::CenterOfCircle(initializer_list<string> FileData):
    MeasureData(FileData),centerofcircle()
{
    try
    {
        this->CheckData();
    }
    catch (exception& e)
    {
        Error_Report(e, MessageBoxFlags::OK);
    }
}

CenterOfCircle::CenterOfCircle(const CenterOfCircle& p):
    centerofcircle(p.centerofcircle),R(p.R)
{
}

CenterOfCircle::~CenterOfCircle()
{
}

void CenterOfCircle::Calculate()
{
    int m = this->row();
    int n = this->col(); 
    Martix X0(3, 1);
    Martix l(m, 1, true);
    Martix P(m, m,true);
    Martix A(m, n);
    Martix L(m, 1);
    Martix X(3, 1);
    Martix R(m, 1);

    //(MT*M)^-1*(MT*l)
    Martix MT = this->Transposition();
    Martix MTM = this->Multiplicte(MT, true);
    Martix MTMT = MTM.Transposition();
    Martix MTL = MT.Multiplicte(l, false);
    X0 = MTMT.Multiplicte(MTL, false);

    L.SetData(0, 0, 1);
    for (int i = 0; i < n; i++)
        A.SetData(0, i, X0.GetData(i, 0));
    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A.SetData(i, j, this->GetData(i, j) - this->GetData(i - 1, j));
            L.SetData(i, 0, L.GetData(i, 0) + pow(this->GetData(i, j), 2) - pow(this->GetData(i - 1, j), 2));
        }
        L.SetData(i, 0, L.GetData(i, 0) / 2);
    }
    //AT为A的转置
    //((AT*P*A)^-1*AT)^-1*P*L
    Martix AT = A.Transposition();
    Martix ATPA = AT.Multiplicte(P, false).Multiplicte(A, false);
    Martix ATPAT = ATPA.Transposition();
    Martix ATPATAT = ATPAT.Multiplicte(AT, false);
    X = ATPATAT.Transposition().Multiplicte(P, false).Multiplicte(L, false);

    double r = 0;
    for (int i = 0; i < m; i++)
    {
        R.SetData(i, 0, sqrt(pow((this->GetData(i, 0) - X.GetData(0, 0)), 2) + pow((this->GetData(i, 1) - X.GetData(1, 0)), 2) + pow(this->GetData(i, 2) - X.GetData(2, 0), 2)));
        r += R.GetData(i, 0);
    }
    r /= m;
    this->centerofcircle.SetData(3, X.GetData(0, 0), X.GetData(1, 0), X.GetData(2, 0));
    this->R = r;
}

void CenterOfCircle::COUT()
{
}

void CenterOfCircle::CheckData()throw(domain_error)
{
    if (this->row() < 7)
        throw domain_error("所测坐标数目小于7");
}

void CenterOfCircle::Draw()
{
}

//返回值为方程AX+BY+CZ=1的X,Y,Z
Section::Section(initializer_list<string> FileData):MeasureData(FileData)
{
    try
    {
        this->CheckData();
    }
    catch (exception& e)
    {
        Error_Report(e, MessageBoxFlags::OK);
    }
}

Section::Section(const Section& p):Param(p.Param)
{
}

Section::~Section()
{
}

void Section::Calculate() {
    int m = this->row();
    Martix X(3, 1, true);
    Martix l(m, 1);
    Martix P(m, m, true);
    //解算X=(AT*P*A)^-1*AT*P*l；
    Martix ATP = this->Transposition().Multiplicte(P, false);
    Martix ATPAT = this->Multiplicte(ATP, true).Transposition();
    Martix ATPL = this->Transposition().Multiplicte(P, false).Multiplicte(l, false);
    X = ATPAT.Multiplicte(ATPL, false);
    for (int i = 0; i < 3; i++)
        this->Param.push_back(X.GetData(i, 0));
}

void Section::COUT()
{
}

void Section::CheckData()throw(domain_error)
{
    if (this->row() < 7)
        throw domain_error("所测坐标数目小于7");
}

void Section::Draw()
{
}
