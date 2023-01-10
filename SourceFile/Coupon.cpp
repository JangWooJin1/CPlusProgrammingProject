#include"Coupon.h"

//쿠폰 객체 생성 ( 생성자 ) - 할인금액, 최소주문금액, 가게이름, 가게ID
Coupon::Coupon(int Discount, int Minprice, string storeName, string storeID) {
	this->Discount = Discount;
	this->MinPrice = Minprice;
	this->storeName = storeName;
	this-> storeID = storeID;
}

//customerIDs에 고객의 아이디가 존재하는지 파악
int Coupon::FindCustomerID(string customerid) {
	int i = 0;	//반복문 변수 설정
	for (; i < customerIDs.size(); i++) {
		//매개변수의 id를 가진 설치자가 있다면 반복문 종료
		if (customerIDs[i] == customerid) break;
	}
	//설치자가 있다면 i값은 installers크기보다 작고, 설치자가 없다면 i == installers.size()가 된다.

	//반복문 변수 반환
	return i;
}