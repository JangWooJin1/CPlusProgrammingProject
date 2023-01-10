#include"Installer.h"

//설치자 객체를 생성 ( 생성자 )
Installer::Installer(string name, string phoneNum, string Area, string id, string password, int Balance) {
	this->name = name;
	this->phoneNum = phoneNum;
	this->Area = Area;
	this->id = id;
	this->password = password;
	this->Balance = Balance;
}

//설치자의 잔액를 출력
void Installer::ShowBalance() {
	cout << "현재 잔액 : " << Balance << "원" << endl;
}

//설치자의 잔액에 입금
bool Installer::PlusBalance(int price) {
	if (price > 0) {	//예외처리 ( 입금하려는 금액이 음수일 때 ) 
		Balance += price;
		return true;
	}
	else return false;
}

//설치자의 잔액에서 인출
void Installer::MinusBalance(int price) {
	if (price > 0) {	//예외처리 ( 인출하려는 금액이 음수일 때 )
		if (Balance >= price) {	//예외처리 ( 잔액가 부족할경우 )
			Balance -= price;
			cout << "인출 완료." << endl;
		}
		else cout << "잔액이 부족합니다." << endl;
	}
	else cout << "잘못 입력하셨습니다." << endl;
}

//menus에 저장되어있는 메뉴들 출력 후 총 금액을 반환
int Installer::ShowMenu() {
	int totalprice = 0;	//모든 메뉴의 가격을 저장하는 변수
	int price;	//하나의 메뉴의 가격을 저장하는 변수
	//첫번째 반복문을 통해 메뉴 가격 price에 넣기
	for (int i = 0; i < menus.size(); i++) {
		price = menus[i].price;
		//두번째 반복문을 통해 세부사항 적용 금액 price에 추가
		for (int j = 0; j < menus[i].details.size(); j++) {
			if (menus[i].details[j].YN == true) 	price += menus[i].details[j].price;
		}
		totalprice += price;	//각 메뉴의 금액을 총액에 추가
		cout << i + 1 << ". " << menus[i].name << " (" << price << "원) ";
	}
	cout << endl;
	//총 금액 반환
	return totalprice;
}

//coupons에 저장되어있는 쿠폰 정보 출력
void Installer::ShowCoupon() {
	cout << "현재 쿠폰 목록 : ";

	for (int i = 0; i < coupons.size(); i++) {
		cout << i+1 <<". " << coupons[i].storeName << "의 " << coupons[i].Discount << "원 할인쿠폰 ( 최소주문금액 : " << coupons[i].MinPrice << " ) ";
	}
	cout << endl;
}


