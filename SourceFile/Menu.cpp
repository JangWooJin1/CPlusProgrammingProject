#include"Menu.h"
//메뉴 객체 생성 (생성자)-메뉴이름, 가격, 조리시간 전달
Menu::Menu(string name, int price, int cooktime) {
	this->name = name;
	this->price = price;
	this->cooktime = cooktime;
}

//details에 저장된 모든 세부내용출력
void Menu::DetailList() {
	//details의 크기 만큼 반복
	for (int i = 0; i < details.size(); i++) {
		//세부사항의 내용과 가격을 출력
		cout << i + 1 << ". " << details[i].content << " (" << details[i].price << "원) ";
	}
	cout << endl;
}

//details에 세부사항 추가
void Menu::AddDetail() {
	string content;
	int price;
	cout << "현재 세부사항 : ";	//현재까지의 세부 사항 출력
	DetailList();
	cout << "추가할 세부사항을 입력하세요 ( 내용, 가격 ) : ";	//입력 안내문
	cin >> content >> price;

	if (price < 0) {	//예외처리 ( 가격이 음수인 경우 )
		cout << "가격을 잘못 입력하였습니다." << endl;	//오류 안내문
		return;
	}

	//vector의 push_back함수를 이용하여 배열에 객체 추가
	details.push_back(Detail(content, price, false));
	cout << "메뉴의 세부내용이 추가되었습니다." << endl;
}

//details에 저장된 모든 세부사항 적용여부 검토
void Menu::SetDetail() {
	for (int i = 0; i < details.size(); i++) {//모든 세부 내용에 대한
		details[i].SelectYN();	//고객의 'y 또는 n'의 대답 여부를 곽인
	}
}