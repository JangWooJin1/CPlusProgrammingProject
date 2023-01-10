#ifndef COUPON_H
#define COUPON_H
#include"Detail.h"

class Coupon {
public:
	int Discount;							//쿠폰 할인금액
	int MinPrice;							//쿠폰 사용을 위한 최소 주문금액
	string storeName;						//쿠폰 사용이 가능한 가게이름
	string storeID;							//쿠폰 사용이 가능한 가게아이디
	vector<string> customerIDs;				//쿠폰을 발급받은 고객의 아이디를 저장하는 배열	( 쿠폰 중복 발급 방지를 위해 사용 )

	Coupon(int Discount, int Minprice, string storeName, string storeID);
	int FindCustomerID(string customerid);		//customerIDs에 고객의 아이디가 존재하지 파악 ( 쿠폰 중복 발급 방지를 위해 사용 )
};
#endif