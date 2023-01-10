#include"Customer.h"

//고객 객체 생성 ( 생성자 )
Customer::Customer(string name, string phoneNum, string Area, string id, string password) : Installer(name,phoneNum,Area,id,password,0) {
	Level = 0;	//회원등급 0으로 초기화
	Accumulated = 0;	//누적주문금액 0으로 초기화
}

//고객의 회원등급과 혜택을 출력
void Customer::Membership() {
	cout << endl << "***회원등급확인***" << endl;
	cout << "회원님의 등급은 현재 " << Level << "입니다." << endl;
	if (Level == 0) {
		cout << "현재 등급에서 혜택은 없습니다." << endl;
		cout << "다음 등급까지 " << 10000 - Accumulated << "원 남았습니다." << endl;
	}
	else if (Level == 1) {
		cout << "현재 등급에서 혜택은 1% 적립" << endl;
		cout << "다음 등급까지 " << 50000 - Accumulated << "원 남았습니다." << endl;
	}
	else if (Level == 2) {
		cout << "현재 등급에서 혜택은 3% 적립" << endl;
		cout << "다음 등급까지 " << 100000 - Accumulated << "원 남았습니다." << endl;
	}
	else if (Level == 3) {
		cout << "현재 등급에서 혜택은 5% 적립" << endl;
	}
}

//고객의 혜택에 맞는 적립금을 적립 및 반환 ( 기프티콘 구매나 주문시 사용 )
int Customer::Benefits(int price) {
	int Benefit = 0;
	if (Level == 0) Benefit+=0;
	else if (Level == 1) Benefit += int(price * 0.01);
	else if (Level == 2) Benefit += int(price * 0.03);
	else if (Level == 3) Benefit += int(price * 0.05);
	return Benefit;
}

//고객의 회원등급을 상승 ( 기프티콘 구매나 주문시 사용 )
bool Customer::LevelUp() {
	if (Level == 0) {
		if (Accumulated < 10000) return false;
		else if (Accumulated >= 160000) Level = 3;
		else if (Accumulated >= 60000) Level = 2;
		else if (Accumulated >= 10000)Level = 1;
		return true;
	}
	else if (Level == 1) {
		if (Accumulated < 60000) return false;
		else if (Accumulated >= 160000) Level = 3;
		else if (Accumulated >= 60000) Level = 2;
		return true;
	}
	else if (Level == 2) {
		if (Accumulated < 160000) return false;
		else if (Accumulated >= 160000) Level = 3;
		return true;
	}
	//회원등급이 상승하였다면 true, 아니라면 false반환
	return false;
}

//고객의 장바구니(menus)에 메뉴를 추가
void Customer::AddMenu(Menu m) {
	//장바구니에 추가하기 전에 세부사항을 체크
	cout << m.name << "의 세부사항을 체크해주세요." << endl;
	m.SetDetail();

	//세부사항 체크가 완료되었다면 장바구니에 메뉴 추가
	menus.push_back(m);
	cout << "장바구니에 " << m.name << "이(가) 추가되었습니다." << endl;
	
}

//고객의 쿠폰함(copons)에 쿠폰을 추가
void Customer::AddCoupon(Coupon* c) {
	if (c != NULL) { 
		//쿠폰 중복 발급 방지를 위해 고객의 아이디를 가지고 확인
		int i = c->FindCustomerID(this->id);

		if (i == c->customerIDs.size()) {	
			coupons.push_back(*c);	//모든 조건을 충족한다면 고객의 쿠폰함에 추가
			c->customerIDs.push_back(this->id);	//중복 발급 방지를 위해 쿠폰에 고객 아이디 저장
			cout << "쿠폰이 추가되었습니다." << endl;
		}
		// 예외처리 ( 이미 발급받은 쿠폰인 경우 )
		else cout << "이미 발급받은 쿠폰입니다." << endl;
	}
	// 예외처리 ( 잘못된 쿠폰 번호를 입력했을 경우 )
	else cout << "해당하는 쿠폰이 없습니다." << endl;
}

//결제 진행
bool Customer::Ordering(int price) {
	//결제가 완료되면 true, 실패하면 false를 반환
	if (Balance >= price) {
		Accumulated += price;	//누적주문금액 조정
		Balance -= price;		//고객의 잔액 조정
		cout << "등급혜택으로 " << Benefits(price) << "원 적립되었습니다." << endl;	//결제후 회원등급에 따른 적립금 처리
		if (LevelUp()) cout << "멤버십 레벨이 " << Level << "로 올랐습니다!" << endl;	//누적주문금액에 따른 회원등급 상승이 발생했는지 파악
		return true;
	}
	//예외처리 ( 잔액가 부족할 경우 )
	else return false;
}