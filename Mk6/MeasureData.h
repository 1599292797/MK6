//���ļ�Ϊ�����ļ�������
//�漰��ģ������ʵ��,string�ַ���������֪ʶ��
//Excel������ʵ��

#include"Head.h"
#include"Martix.h"

class MeasureData:public Martix
{
protected:
	string MeasureId;//����������
	string info;//��ע
	vector<string> rowhead, colhead;//�б��⣬�б���
public:
	//���캯��
	MeasureData(){}
	//�б���Ԫ��Ϊ����Դ·��������������ע,����Դ·��������
	MeasureData(initializer_list<string> list)throw(out_of_range);
	//���ƹ��캯��
	MeasureData(const MeasureData& p);
	//��������
	~MeasureData();
	//�����б��⣬�б���
	void SetHead(vector<string> rowhead, vector<string> colhead);
	//��ȡ�ļ���׺
	string FilenameLast(string filename);
	//����תEXCEL,precisionΪҪ������С��λ��
	bool MartixToExcel(string filename, unsigned int precision);
	//����תTXT
	bool MartixToTxt(string filename, unsigned int precision);
	//��ȡExcel��ת����
	void ExcelToMartix(string filename);
	//��ȡTxt��ת����
	void TxTToMartix(string filename);
};