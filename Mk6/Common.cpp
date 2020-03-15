#include "Common.h"


//判断是否未输入数据,未输入为是
bool ISNULL(double data)
{
	if (data<0.0000001 && data>-0.0000001)
		return true;
	return false;
}

bool ISNULL(double* data)
{
	if (data[0]<0.0000001 && data[0]>-0.0000001 || data[1]<0.0000001 && data[1]>-0.0000001)
		return true;
	return false;
}

bool ISNULL(string data) {
	if (data == "")
		return true;
	return false;
}

bool ISNULL(Point data)
{
	if (data.X() < 0.0000001 && data.X() > -0.0000001 || data.Y() < 0.0000001 && data.Y() > -0.0000001)
		return true;
	else
		if (data.Dim() > 2)
			if (data.Z() < 0.0000001 && data.Z() > -0.0000001)
				return true;
	return false;
}

bool ISNULL(Degree data)
{
	if (data.GetDegree() < 0.0000001 && data.GetDegree() > -0.0000001)
		return false;
	return true;
}

bool ISNULL(vector<Point> data)
{
	vector<Point>::iterator it;
	for (it = data.begin(); it < data.end(); it++)
		if (ISNULL(*it))
			return true;
	return false;
}

bool ISNULL(vector<Degree> data)
{
	vector<Degree>::iterator it;
	for (it = data.begin(); it < data.end(); it++)
		if (ISNULL(*it))
			return true;
	return false;
}

//报错及错误类型
int Error_Report(exception& e, MessageBoxFlags MBF)
{
	int flag;
	switch (MBF)
	{
	case OK:
		flag = MessageBox(GetForegroundWindow(), e.what(), "ERROR", MB_OK);
		break;
	case OKCANCEL:
		flag = MessageBox(GetForegroundWindow(), e.what(), "ERROR", MB_OKCANCEL);
		break;
	case ABORTRETRYIGNORE:
		flag = MessageBox(GetForegroundWindow(), e.what(), "ERROR", MB_ABORTRETRYIGNORE);
		break;
	case YESNOCANCEL:
		flag = MessageBox(GetForegroundWindow(), e.what(), "ERROR", MB_YESNOCANCEL);
		break;
	case YESNO:
		flag = MessageBox(GetForegroundWindow(), e.what(), "ERROR", MB_YESNO);
		break;
	case RETRYCANCEL:
		flag = MessageBox(GetForegroundWindow(), e.what(), "ERROR", MB_RETRYCANCEL);
		break;
	default:
		break;
	}
	return flag;
}