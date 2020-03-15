//此文件用于交会计算类实现
//涉及迭代器的使用
#include "Intersection.h"


Intersection::Intersection(const Intersection& p)
{
	this->A = p.A;
	this->B = p.B;
	this->Result = p.Result;
}

Intersection::~Intersection()
{
}

Intersection_Fore::Intersection_Fore(Point A, Point B, vector<Degree> PAB, vector<Degree> PBA):Intersection(A,B)
{
	this->PAB = PAB;
	this->PBA = PBA;
}

Intersection_Fore::Intersection_Fore(const Intersection_Fore& p):Intersection(p.A,p.B)
{
	this->PAB = p.PAB;
	this->PBA = p.PBA;
}

Intersection_Fore::~Intersection_Fore()
{
}

void Intersection_Fore::Calculate(vector<bool> sign)
{
	for (auto i = 0; i < sign.size(); i++)
		this->Calculate(i, sign[i]);
}

void Intersection_Fore::Calculate(int loc, bool sign)
{
	//SinA,SinB,CosA,CosB
	double sa = sin(this->PAB[loc].GetDegree());
	double ca = cos(this->PAB[loc].GetDegree());
	double sb = sin(this->PBA[loc].GetDegree());
	double cb = cos(this->PBA[loc].GetDegree());

	//x=(Xa*Sa*Cb+Xb*Ca*Sb+sign*(Ya-Yb)*Sa*Sb)/(Sa*Cb-Sb*Ca)
	//y=(Ya*Sa*Cb+Yb*Ca*Sb+sign*(Xb-Xa)*Sa*Sb)/(Sa*Cb-Sb*Ca)
	Point xy(2, (A.X() * (sa) * (cb)+B.X() * (sb) * (ca)+(sign ? 1 : 0) * (A.Y() - B.Y()) * (sa) * (sb)) / ((sa) * (cb)+(sb) * (ca)),
		(A.Y() * (sa) * (cb)+B.Y() * (sb) * (ca)+(sign ? 1 : 0) * (B.X() - A.X()) * (sa) * (sb)) / ((sa) * (cb)+(sb) * (ca)));
	
	this->Result.push_back(xy);
}

double Intersection_Fore::PrecisionAnalysis()
{
	return 0.0;
}

//测量坐标系下，A、B、P 顺时针排列时，sign = 1；
//A、B、P 逆时针排列时，sign = -1。
vector<Degree> Intersection_Side::DegreeCalculate(vector<Degree> degree1, vector<Degree> degree2)
{
	vector<Degree>::iterator it1, it2;
	vector<Degree> result;
	for (it1 = degree1.begin(), it2 = degree2.begin(); it1 < degree1.end(); it1++, it2++) {
		Degree degree(2 * PI - (*it1).GetDegree() - (*it2).GetDegree(), true);
		result.push_back(degree);
	}
	return result;
}

Intersection_Side::Intersection_Side(Point A, Point B, vector<Degree> PAB, vector<Degree> APB):Intersection_Fore(A,B,PAB,DegreeCalculate(PAB,APB))
{
	this->APB = APB;
	this->PAB = PAB;
}

Intersection_Side::Intersection_Side(const Intersection_Side& p):Intersection_Fore(p.A,p.B,p.PAB,p.APB)
{
	this->APB = p.APB;
	this->PAB = p.PAB;
}

Intersection_Side::~Intersection_Side()
{
}

void Intersection_Side::Calculate(vector<bool> sign)
{
	Intersection_Fore Side(this->A, this->B, this->PAB, DegreeCalculate(PAB, APB));
	return Side.Calculate(sign);
}

Intersection_Post::Intersection_Post(Point A, Point B, Point C, vector<Degree> APC, vector<Degree> APB):Intersection(A,B)
{
	this->C = C;
	this->APC = APC;
	this->APB = APB;
}

Intersection_Post::Intersection_Post(const Intersection_Post& p):Intersection(p.A,p.B)
{
	this->C = p.C;
	this->APC = p.APC;
	this->APB = p.APB;
}

Intersection_Post::~Intersection_Post()
{
}

void Intersection_Post::Calculate()
{
	
	double x1, x2, y1, y2;
	double K;
	vector<Degree>::iterator ip1, ip2;
	//x1=(Xa+Xb+(Ya-Yb)*Cot(APB))/2
	//y1=(Ya+Yb+(Xb-Xa)*Cot(APB))/2
	//x2=(Xa+Xc+(Ya-Yc)*Cot(APC))/2
	//y2=(Ya+Yc+(Xc-Xa)*Cot(APC))/2
	//K=(Ya*(x2-x1)-Xa*(y2-y1)+x1*y2-x2*y1)*2/((x2-x1)^2+(y2-y1)^2)
	//xp=Xa+K*(y2-y1);
	//yp=Ya+K*(x1-x2);
	for (ip1 = this->APB.begin(), ip2 = this->APC.begin(); ip1 < this->APB.end(); ip1++, ip2++) {
		x1 = (A.X() + B.X() + (A.Y() - B.Y()) / tan((*ip1).GetDegree())) / 2;
		y1 = (A.Y() + B.Y() + (B.X() - B.X()) / tan((*ip1).GetDegree())) / 2;
		x2 = (A.X() + C.X() + (A.Y() - C.Y()) / tan((*ip2).GetDegree())) / 2;
		y2 = (A.Y() + C.Y() + (C.X() - B.X()) / tan((*ip2).GetDegree())) / 2;
		K = 2 * (A.Y() * (x2 - x1) - A.X() * (y2 - y1) + x1 * y2 - x2 * y1) / (pow(x2 - x1, 2) + pow(y2 - y1, 2));
		Point res(2, A.X() + K * (y2 - y1), A.Y() + K * (x1 - x2));
		this->Result.push_back(res);
	}
}

