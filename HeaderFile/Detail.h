#ifndef DETAIL_H
#define DETAIL_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Detail {
public:
	string content;			//���λ����� ����
	int price;				//���λ����� ����
	bool YN;				//���λ��׿� ���� ���� ���� ����
	Detail(string content, int price, bool YN);
	void SelectYN();		//���λ��� ���뿩��(YN)�� ���� ����
};

#endif