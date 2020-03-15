//此文件为测量数据类实现
#pragma once

#include "MeasureData.h"

MeasureData::MeasureData(initializer_list<string> list) throw(out_of_range) :Martix(0, 0)
{
	string filenameLast = FilenameLast(*list.begin());
	if (!strcmp(filenameLast.c_str(), "txt")) {
		TxTToMartix(*list.begin());
	}
	else if (!strcmp(filenameLast.c_str(), "xls") || !strcmp(filenameLast.c_str(), "xlsx")) {
		ExcelToMartix(*list.begin());
	}
	else {
		throw out_of_range("暂不支持读取该格式的数据");
	}
	if (list.size() >1)
		this->MeasureId = *(list.begin() + 1);
	if (list.size() > 2)
		this->info = *(list.begin() + 2);
}

MeasureData::MeasureData(const MeasureData& p):Martix(p), rowhead(p.rowhead),colhead(p.colhead),MeasureId(p.MeasureId),info(p.info)
{
}

MeasureData::~MeasureData()
{
}

void MeasureData::SetHead(vector<string> rowhead, vector<string> colhead)
{
	this->rowhead = rowhead;
	this->colhead = colhead;
}

string MeasureData::FilenameLast(string filename)
{
	return filename.substr(filename.find_last_of('.') + 1);
}

bool MeasureData::MartixToExcel(string filename, unsigned int precision)
{
	//setprecision(precision);
	return false;
}

bool MeasureData::MartixToTxt(string filename, unsigned int precision)
{
	ofstream outfile;
	outfile.open(filename);
	
	vector<vector<double>>::iterator it1;
	vector<double>::iterator it2;
	vector<string>::iterator it;
	//setprecision(precision);
	if (this->colhead.size())
		outfile << "\t";
	for (unsigned int i = 0; i < this->rowhead.size(); i++)
		outfile << this->rowhead[i] << "\t";
	if (this->colhead.size())
		outfile << endl;
	for (unsigned int i = 0; i < this->colhead.size(); i++) {
		if (this->colhead.size())
			outfile << this->colhead[i] << "\t";
		for (unsigned int j = 0; j < this->row(); j++)
			outfile << this->GetData(i, j) << "\t";
		outfile << endl;
	}
	outfile.close();
	return true;
}

void MeasureData::ExcelToMartix(string filename)
{
}

void MeasureData::TxTToMartix(string filename)
{
	ifstream infile(filename);
	string str;
	vector<double> res;
	double x;
	int flag = 0;
	while (infile) {
		getline(infile, str);
		if (!isdigit(*str.begin())) {
			if (!flag) {
				str = str.substr(1, str.size());
				do {
					this->rowhead.push_back(str.substr(0, str.find_first_of("\t")));
					if (str.find_first_of('\t') == string::npos) {
						str.clear();
					}
					else
						str = str.substr(str.find_first_of('\t') + 1, str.size());
				} while (str.size());
				flag = 1;
			}
			else {
				this->colhead.push_back(str.substr(0, str.find_first_of("\t")));
				str = str.substr(str.find_first_of('\t') + 1, str.size());
			}
		}
		if (str.size()) {
			do {
				istringstream iss(str.substr(0, str.find_first_of('\t')));
				iss >> x;
				res.push_back(x);
				if (str.find_first_of('\t') == string::npos) {
					str.clear();
				}
				else
					str = str.substr(str.find_first_of('\t') + 1, str.size());
			} while (str.size());
			this->SetData(res, true);
		}
		res.clear();
	}
	updatasize();
}