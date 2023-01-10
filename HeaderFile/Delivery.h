#ifndef DELIVERY_H
#define DELIVERY_H
#include"Store.h"
#include"Customer.h"
#include<typeinfo>
#include<fstream>
#include<windows.h>

class Delivery {
private:
	vector<Installer*> installers;								//설치자(고객, 가게)을 저장하는 배열 ( 동적할당 사용 )
	int in;												//어떤 동작을 할지 결정하는 변수
public:
	Delivery();									//동적할당 배열 installers 공간 해제해주는 소멸자
	~Delivery();									//동적할당 배열 installers 공간 해제해주는 소멸자

	int Input();										//입력예외처리함수 ( 정수 자료형에 문자값을 넣었을 때)

	//배열에서 i-1번째 인덱스에 있는 객체를 반환해주는 템플릿 함수 ( Installer::menus, Installer::coupons, Installer::gifticons,Store::DeliveryArea, Store::DeliveryTime, Menu::details 에 사용)
	template<class T>
	T* selectObj(vector<T>* list, int i);		

	//배열에서 i-1번째 인덱스에 있는 객체를 제거해주는 템플릿 함수 ( Installer::menus, Installer::coupons, Installer::gifticons,Store::DeliveryArea, Store::DeliveryTime, Menu::details에 사용) 
	template<class K>
	bool Delete(vector<K>* list, K* tmp, int index);	

	int FindInstallerID(string id);							//설치자 아이디를 통해 installers에서 위치(인덱스)를 찾아 반환
	void InstallerJoin();									//installers에 설치자 추가(회원가입)
	bool InstallerLeave(Installer* IT);							//installers에서 설치자 제거(회원탈퇴)
	Installer* InstallerLogin();									//설치자 아이디와 비밀번호를 통해 installers에서 해당하는 고객 반환( 로그인 )
	Store* SelectStore();							//고객이 원하는 가게를 선택하면 그 가게를 반환 ( 주문, 기프티콘 선물할때 사용 )
	int DeliveryTime(Store* S, Customer* C, int i);			//고객과 가게의 정보를 가지고 최종 배달시간을 반환	( 주문할때 사용 )

	void StartInterface();								//회원가입, 로그인 인터페이스

	void CustomerInterface(Customer* C);						//고객으로 로그인했을때 사용되는 인터페이스 ( 주문 / 선물하기 / 잔액관리 / 회원등급 / 회원탈퇴 )
	void MoneyInterface(Customer* C);						//고객 잔액관리 인터페이스 ( 잔액확인/ 잔액충전/ 잔액인출 )
	void StoreInterface(Customer* C);						//고객 주문 인터페이스	( 가게 선택 후 => 장바구니 관리 / 주문하기 / 쿠폰추가 )
	void BasketInterface(Customer* C, Store* S);		//고객 장바구니 인터페이스	( 장바구니목록 / 장바구니추가 / 장바구니제거 )
	void OrderInterface(Customer* C, Store* S);		//고객 주문하기 인터페이스	( 쿠폰사용 / 기프티콘사용 / 주문진행 )

	void ManagerInterface(Store* S);					//가게로 로그인했을때 사용되는 인터페이스 ( 메뉴관리 / 메뉴세부내용관리 / 배달지역 / 쿠폰관리 / 기프티콘관리 / 주문확인 /회원탈퇴 )
	void MenuInterface(Store* S);					//가게 메뉴관리 인터페이스 ( 메뉴목록 / 메뉴추가 / 메뉴삭제 )
	void DetailInterface(Menu* M);					//가게 메뉴세부내용관리 인터페이스 ( 메뉴세부내용목록 / 메뉴세부내용추가 / 메뉴세부내용삭제 )
	void DeliveryAreaInterface(Store* S);			//가게 배달지역관리 인터페이스 ( 배달지역목록 / 배달지역추가 / 배달지역삭제 )
	void CouponInterface(Store* S);				//가게 쿠폰관리 인터페이스 ( 쿠폰목록 / 쿠폰추가 / 쿠폰삭제 )
};

#endif