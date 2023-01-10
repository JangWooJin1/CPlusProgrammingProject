#ifndef INSTALLER_H
#define INSTALLER_H
#include"Menu.h"
#include"Coupon.h"
//#include"Gifticon.h"

class Installer {
public:
	string name, phoneNum, Area, id, password;													//설치자 정보 ( 이름, 전화번호, 지역, 아이디, 비밀번호 )
	int Balance;																				//설치자의 잔액 ( 가게는 매출, 고객은 잔액로 이용 )
	vector<Menu> menus;																			//설치자의 메뉴를 저장하는 배열 ( 가게는 메뉴, 고객은 장바구니로 이용 )
	vector<Coupon> coupons;																		//설치자의 쿠폰을 저장하는 배열

	Installer(string name, string phoneNum, string Area, string id, string password, int Balance);	//설치자 객체생성
	void ShowBalance();																			//설치자의 잔액를 출력
	bool PlusBalance(int price);																	//설치자의 잔액에 price만큼 입금
	void MinusBalance(int price);																//설치자의 잔액에서 price만큼 인출

	int ShowMenu();																				//menus에 저장된 메뉴들 출력
	void ShowCoupon();																			//coupons에 저장된 쿠폰들 출력	
	virtual void dump() = 0;
};


#endif

