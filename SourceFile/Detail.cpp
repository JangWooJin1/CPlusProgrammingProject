#include"Detail.h"
//세부사항 객체 생성 (생성자)-내용, 가격, 적용여부 전달
Detail::Detail(string content, int price, bool YN) {
	this->content = content;
	this->price = price;
	this->YN = YN;
}

//세부사항적용여부(YN)의 값 조정
void Detail::SelectYN() {
	string select;	//YN의 값을 임시 저장하는 변수
	//고객이 정상적으로 대답할때까지 반복
	while (true) {
		cout << content << "(" << price << "원) (Y or N) : "; //세부사항 안내 및 적용 여부 질문
		cin >> select;	
		if (select == "Y" || select == "y") {	//고객이 'Y' / 'y'중에서 대답한 경우
			YN = true;	//세부사항 적용
			break;
		}
		else if (select == "N" || select == "n") { //고객이 'N' / 'n' 중에서 대답한 경우
			YN = false; //세부사항 적용하지 않음
			break;
		}
		else cout << "잘못 입력하셨습니다." << endl;	//그 외의 대답
	}
}
