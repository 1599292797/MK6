//此文件为测量文件类声明
//涉及类模板声明实现,string字符串操作等知识点
//Excel操作待实现

#include"Head.h"
#include"Martix.h"

class MeasureData:public Martix
{
protected:
	string MeasureId;//测量数据名
	string info;//备注
	vector<string> rowhead, colhead;//行标题，列标题
public:
	//构造函数
	MeasureData(){}
	//列表中元素为数据源路径，数据名，备注,数据源路径必须有
	MeasureData(initializer_list<string> list)throw(out_of_range);
	//复制构造函数
	MeasureData(const MeasureData& p);
	//析构函数
	~MeasureData();
	//设置行标题，列标题
	void SetHead(vector<string> rowhead, vector<string> colhead);
	//提取文件后缀
	string FilenameLast(string filename);
	//矩阵转EXCEL,precision为要保留的小数位数
	bool MartixToExcel(string filename, unsigned int precision);
	//矩阵转TXT
	bool MartixToTxt(string filename, unsigned int precision);
	//读取Excel并转矩阵
	void ExcelToMartix(string filename);
	//读取Txt并转矩阵
	void TxTToMartix(string filename);
};