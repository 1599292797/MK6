//�������߼�����ʵ��

//�쳣��ȡ
//���ݼ���CheckData
//������ȡ��̣����
#include "TransitionCurve.h"

TransitionCurve::TransitionCurve(
    Point ZH, 
    Point HY, 
    double Lzh, 
    double Lhy, 
    Degree Azimuth,
    double R,
    bool Dir) :
    ZH(ZH),
    HY(HY), 
    Lzh(Lzh),
    Lhy(Lhy),
    Azimuth(Azimuth),
    R(R),
    Dir(Dir),
    Result()
{
}


TransitionCurve::TransitionCurve(TransitionCurve& p) : 
    ZH(p.ZH), 
    HY(p.HY), 
    Lzh(p.Lzh),
    Lhy(p.Lhy), 
    Azimuth(p.Azimuth),
    Dir(p.Dir), 
    R(p.R), 
    Result(p.Result)
{
}

TransitionCurve::~TransitionCurve()
{
}

TransitionCurve_OnePoint::TransitionCurve_OnePoint(
    Point ZH,
    Point HY,
    double Lzh,
    double Lhy,
    double Ls,
    Degree Azimuth,
    double R,
    bool Dir) :
    TransitionCurve(ZH, HY, Lzh, Lhy, Azimuth, R, Dir),
    Ls(Ls)
{
}

TransitionCurve_OnePoint::TransitionCurve_OnePoint(TransitionCurve_OnePoint& p):
    TransitionCurve(p.ZH,p.HY,p.Lzh,p.Lhy,p.Azimuth,p.R,p.Dir),
    Ls(p.Ls)
{
}

TransitionCurve_OnePoint::~TransitionCurve_OnePoint()
{
}

void TransitionCurve_OnePoint::Calculate()
{
    vector<double> result;
    double L = Lhy - Lzh;
    double a = 180 * pow(Ls, 2) / (6 * PI * R * L);
    double S = Ls - pow(Ls, 5) / (90 * pow(R * L, 2));
    result[0] = ZH.X() + S * cos(2 * PI * (Azimuth.GetDegree() + a) / 360);
    result[1] = ZH.Y() + S * sin(2 * PI * (Azimuth.GetDegree() + a) / 360);
    this->Result.SetData(result, true);
}

void TransitionCurve_OnePoint::CheckData()throw(invalid_argument)
{
    if (ISNULL(Lzh)) {
       throw invalid_argument("ֱ�������Ϊ��");
    }
    if (ISNULL(Lhy)) {
        throw invalid_argument("��Բ������Ϊ��");
    }
    if (ISNULL(ZH)) {
        throw invalid_argument("ֱ��������Ϊ��");
    }
    if (ISNULL(HY)) {
        throw invalid_argument("��Բ������Ϊ��");
    }
    if (ISNULL(Ls)) {
        throw invalid_argument("��������Ϊ��");
    }
    if (ISNULL(Azimuth)) {
        throw invalid_argument("ֱ�������߷�λ��Ϊ��");
    }
    if (ISNULL(R)) {
        throw invalid_argument("Բ���߰뾶Ϊ��");
    }
    if (ISNULL(Dir)) {
        throw invalid_argument("δѡ������ת��");
    }
}

TransitionCurve_MorePoints::TransitionCurve_MorePoints(
    Point ZH, 
    Point HY,
    double Lzh, 
    double Lhy, 
    Degree Azimuth, 
    double R, 
    bool Dir,
    double LC, 
    double LE, 
    double Mile) :
    TransitionCurve_OnePoint(ZH, HY, Lzh, Lhy, LC, Azimuth, R, Dir),
    LC(LC),
    LE(LE),
    Mile(Mile)
{
}

TransitionCurve_MorePoints::TransitionCurve_MorePoints(TransitionCurve_MorePoints& p):
    TransitionCurve_OnePoint(p.ZH,p.HY,p.Lzh,p.Lhy,p.Ls,p.Azimuth,p.R,p.Dir),
    LC(p.LC),
    LE(p.LE),
    Mile(p.Mile)
{
}

TransitionCurve_MorePoints::~TransitionCurve_MorePoints()
{
}

void TransitionCurve_MorePoints::Calculate()
{
    vector<double> res;
    int n = (int)((LC - LE) / Mile);//����ѭ������
    for (int i = 0; i < n; i++)//��ʼѭ��
    {
        this->Ls = (LC + i * Mile) - Lzh;
        TransitionCurve_MorePoints::Calculate();
    }
}

void TransitionCurve_MorePoints::CheckData()throw (invalid_argument)
{
    try
    {
        TransitionCurve_OnePoint::CheckData();
    }
    catch (exception& e)
    {
        Error_Report(e, MessageBoxFlags::OK);
    }
    if (ISNULL(LC)) {
        throw invalid_argument("��������Ϊ��");
    }
    if (ISNULL(LE)) {
        throw invalid_argument("�յ����Ϊ��");
    }
    if (ISNULL(Mile)) {
        throw invalid_argument("��λ���Ϊ��");
    }
}

//��̷������
void Level::HeightLaw() {
    vector<double> res(4);
    vector<double> res2(2);
    vector<vector<double>> param;
    for (unsigned int i = 0; i < this->row() - 1; i++) {
        SolveEquations_2_1(i);
    }
}
//���Ԫһ�η�����
void Level::SolveEquations_2_1(int loc) {
    double x1 = this->GetData(loc, 0);
    double y1 = this->GetData(loc, 1);
    double x2 = this->GetData(loc + 1, 0);
    double y2 = this->GetData(loc + 1, 1);
    vector<double> result;
    if (x1 - x2<0.0000001 && x1 - x2>-0.0000001)
        this->KB.SetData(loc, 0, 0);
    else
        this->KB.SetData(loc, 0, (y1 - y2) / (x1 - x2));
    this->KB.SetData(loc, 1, y1 - this->KB.GetData(loc, 0) * x1);
}

Level::Level(unsigned int count, ...) :
    Martix(count, 2),
    KB()
{
    this->count = count;
    va_list vl;
    va_start(vl, count);
    for (unsigned int i = 0; i < this->count; i++) {
        this->SetData(i, 0, va_arg(vl, double));
        this->SetData(i, 1, va_arg(vl, double));
    }
    va_end(vl);
    HeightLaw();
}

Level::Level(Level& p) :
    Martix(p.count, 2),
    count(p.count),
    KB(p.KB)
{
}

Level::~Level()
{
}

double Level::Mile(unsigned int loc)throw(out_of_range) {
    if (loc > count) {
        throw out_of_range("��ȡλ�ò�����");
    }
    return this->GetData(loc - 1, 0);
}

double Level::Height(unsigned int loc)throw(out_of_range) {
    if (loc > count) {
        throw out_of_range("��ȡλ�ò�����");
    }
    return this->GetData(loc - 1, 1);
}

TransitionCurve_SegmentCheck::TransitionCurve_SegmentCheck(
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
    initializer_list<string> FileData
):TransitionCurve_MorePoints(ZH, HY, Lzh, Lhy, Azimuth, R, Dir, LC, LE, Mile), 
MeasureData(FileData){}

TransitionCurve_SegmentCheck::TransitionCurve_SegmentCheck(TransitionCurve_SegmentCheck& p):
    TransitionCurve_MorePoints(p.ZH,p.HY,p.Lzh,p.Lhy,p.Azimuth,p.R,p.Dir,p.LC,p.LE,p.Mile),
    MeasureData(p.measure),
    Height(p.Height)
{
}

TransitionCurve_SegmentCheck::~TransitionCurve_SegmentCheck()
{
}


void TransitionCurve_SegmentCheck::Calculate()
{
    double L = Lhy - Lzh;
    int n = (int)((LC - LE) / Mile);//����ѭ������
    for (int i = 0, j = 0; i < n; i++)//��ʼѭ��
    {
        this->Ls = (LC + i * Mile) - Lzh;
        while (!(LC + i * Mile >= this->Height.GetData(i, 0) && LC + i * Mile < this->Height.GetData(i, 1)))
            j++;
        TransitionCurve_OnePoint::Calculate();
        this->Result.SetData(i, 2, this->Height.GetData(j, 2) * (LC + i * Mile) + this->Height.GetData(j, 3));
    }
}

void TransitionCurve_SegmentCheck::Compare()
{
    for (unsigned int i = 0; i < this->Result.row(); i++)
        for (int j = 0, k = 6; j < 3; j++, k++)
            this->Result.SetData(i, k, this->Result.GetData(i, j) - this->Result.GetData(i, j + 3));
   
}

void TransitionCurve_SegmentCheck::CheckData()throw (invalid_argument)
{
    try
    {
        TransitionCurve_MorePoints::CheckData();
    }
    catch (exception& e)
    {
        Error_Report(e, MessageBoxFlags::OK);
    }
}

void TransitionCurve_SegmentCheck::COUT()
{
    this->Result.RightConnect(measure);
    Compare();
}


