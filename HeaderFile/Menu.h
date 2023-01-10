#ifndef MENU_H
#define MENU_H
#include"Detail.h"

class Menu {
public:
	string name;				//메뉴 이름
	int price;					//메뉴 가격
	int cooktime;				//조리 시간
	vector<Detail> details;		//메뉴의 세부내용

	Menu(string name, int price, int cooktime);  //메뉴 객체생성 ( 가게가 메뉴를 추가할 때 )
	void DetailList();							 //메뉴 세부내용 출력
	void AddDetail();							 //메뉴 세부내용 추가 ( 가게가 세부내용을 추가할 때 )
	void SetDetail();							 //메뉴 세부내용 설정 ( 고객이 주문할 때 사용 )
};

#endif
