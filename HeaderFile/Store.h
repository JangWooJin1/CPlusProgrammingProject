#ifndef STORE_H
#define STORE_H
#include"Installer.h"

class Store : public Installer{
public:
	int TotalOrder;						//가게 총 주문건수
	vector<string> DeliveryArea;		//배달 가능 지역이름을 저장하는 배열
	vector<int> DeliveryTime;			//배달 시간을 저장하는 배열

	Store(string name, string phoneNum, string Area, string id, string passowrd);

	void AddMenu();						//가게 메뉴판(menus)에 메뉴추가
	void AddCoupon();					//가게 쿠폰함(coupons)에 쿠폰추가
	void AddDeliveryArea();				//가게 배달가능지역리스트(DeliveryArea, DeliveryTime)에 배달가능지역과 배달시간 추가
	void ShowDeliveryArea();			//가게 배달가능지역과 배달시간을 출력
	void ShowTotalOrder();				//가게 총 주문건수와 매출을 출력

	void dump() {} //순수 가상함수로 만들기위한 더미
};
#endif