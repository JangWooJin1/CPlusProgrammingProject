#include"Store.h"

//가게 객체 생성 ( 생성자 )
Store::Store(string name, string phoneNum, string Area, string id, string password) : Installer(name, phoneNum, Area, id, password,0) {
	this->TotalOrder = 0;	//가게 총 주문건수 0으로 초기화
}

//가게 메뉴판(menus)에 메뉴추가
void Store::AddMenu() {
	string name;	//메뉴이름
	int price,cooktime;	//메뉴 가격과 조리시간
	cout << "메뉴이름과 가격, 조리시간(분)을 입력하세요. : ";
	cin >> name >> price >> cooktime;
	
	if (price < 0) {//예외처리 ( 가격이 음수일때 )
		cout << "가격을 잘못 입력하셨습니다." << endl;
		return;
	}
	if (cooktime < 0) { //예외처리 ( 조리시간이 음수일때 )
		cout << "조리시간을 잘못 입력하셨습니다." << endl;
		return;
	}

	//메뉴 객체 생성후 menus에 추가
	menus.push_back(Menu(name, price, cooktime));
	cout << "메뉴가 추가되었습니다." << endl;
}

//가게 쿠폰함(conpos)에 쿠폰추가
void Store::AddCoupon() {
	ShowCoupon();
	int Discount, MinPrice;
	cout << "할인금액과 최소주문금액을 설정하세요. : ";
	cin >> Discount >> MinPrice;

	if (Discount <= 0) { //예외처리 ( 할인금액이 음수인경우 )
		cout << "잘못 입력하셨습니다." << endl;
		return;
	}
	if (MinPrice <= Discount) { //예외처리 ( 최소주문금액이 할인금액보다 작은경우 )
		cout << "최소주문금액이 할인금액보다 낮을 수 없습니다." << endl;
		return;
	}

	//쿠폰 객체 생성 후 coupons에 객체 추가
	coupons.push_back(Coupon(Discount, MinPrice, this->name, this->id));
	cout << "쿠폰이 추가되었습니다." << endl;
}

//가게 배달가능지역리스트(DeliveryArea, DeliveryTime)에 배달가능지역과 배달시간 추가
void Store::AddDeliveryArea() {
	cout << "현재 지역 : ";
	ShowDeliveryArea();
	string Area;	//배달 지역
	int cooktime;	//배달 시간
	cout << "추가하실 지역과 배달시간을 입력해주세요. : ";
	cin >> Area >> cooktime;

	if (cooktime > 0) {	//예외처리 ( 배달시간이 음수인 경우 )
		DeliveryArea.push_back(Area);	//DeliveryArea에 배달지역 추가
		DeliveryTime.push_back(cooktime);	//DeliveryTime에 배달시간 추가
		cout << "지역이 추가되었습니다." << endl;
	}
	else cout << "잘못 입력하셨습니다." << endl;
}

//가게 배달가능지역과 배달시간을 출력
void Store::ShowDeliveryArea() {
	for (int i = 0; i < DeliveryArea.size(); i++) {
		cout << i + 1 << ". " << DeliveryArea[i] << "(" << DeliveryTime[i] << "분) ";
	}
	cout << endl;
}

//가게 총 주문건수와 매출을 출력
void Store::ShowTotalOrder() {
	cout << "총 " << TotalOrder << "건의 주문이 들어왔고, 현재까지의 매출은 " << Balance << "원 입니다." << endl;
}




