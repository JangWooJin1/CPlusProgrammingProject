#ifndef CUSTOMER_H
#define CUSTOMER_H
#include"Installer.h"

class Customer : public Installer{
public:
	int Level;							//회원등급
	int Accumulated;					//누적주문금액

	Customer(string name, string phoneNum, string Area, string id, string password);

	void Membership();					//고객의 회원등급과 혜택을 출력
	int Benefits(int price);			//고객의 혜택에 맞는 적립금을 적립 및 반환 ( 기프티콘 구매나 주문시 사용 )
	bool LevelUp();						//고객의 회원등급을 상승 ( 기프티콘 구매나 주문시 사용 )
	void AddMenu(Menu m);				//고객의 장바구니(menus)에 메뉴를 추가
	void AddCoupon(Coupon* c);			//고객의 쿠폰함(copons)에 쿠폰을 추가
	bool Ordering(int price);			//결제 진행

	void dump() {} //순수 가상함수로 만들기위한 더미
};
#endif