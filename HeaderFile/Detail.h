#ifndef DETAIL_H
#define DETAIL_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Detail {
public:
	string content;			//세부사항의 내용
	int price;				//세부사항의 가격
	bool YN;				//세부사항에 대한 고객의 적용 여부
	Detail(string content, int price, bool YN);
	void SelectYN();		//세부사항 적용여부(YN)의 값을 조정
};

#endif