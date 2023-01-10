#include"Delivery.h"

//생성자(list.csv 파일 내용 읽어오기)
Delivery::Delivery() {
	ifstream IF("list.csv");
	if (IF.fail()) {
		return;
	}

	string str;
	getline(IF, str);	//가게 헤더라인 건너뛰기
	while (!IF.eof()) {
		//가게 이름, 전화번호, 지역, 아이디, 비밀번호, 매출 정보 가져오기
		string name, phoneNum, Area, id, password, Balance;
		getline(IF, name, ',');
		if (name.find("손님") != name.find("NOT_FOUND") || name.size()<1) {
			break;
		}
		getline(IF, phoneNum, ',');
		getline(IF, Area, ',');
		getline(IF, id, ',');
		getline(IF, password, ',');
		getline(IF, Balance, ',');

		//cout << "디버깅1 : " << name << "/" << phoneNum << "/" << Area << "/" << id << "/" << password << "/" << Balance << "/" << endl;
		Store *S = new Store(name, phoneNum, Area, id, password);
		S->Balance = stoi(Balance);
		//가게 이름, 전화번호, 지역, 아이디, 비밀번호, 매출 정보 가져오기


		// 메뉴들[이름_가격_조리시간_메뉴세부사항] 정보 가져오기
		string menu, m_name, m_price, m_cooktime;
		getline(IF, menu, ',');
		while (menu.size() > 2) {
			int split = menu.find("_");
			m_name = menu.substr(1, split-1);
			menu = menu.substr(split+1);

			split = menu.find("_");
			m_price = menu.substr(0, split);
			menu = menu.substr(split + 1);

			split = menu.find("_");
			m_cooktime = menu.substr(0, split);
			menu = menu.substr(split + 1);

			//cout << "디버깅2 : " << m_name << "/" <<  m_price << "/" <<  m_cooktime << "/" <<endl;
			Menu M(m_name, stoi(m_price), stoi(m_cooktime));

			// 메뉴세부사항[세부 내용, 가격, 적용여부] 정보 가져오기
			string d_content, d_price, d_YN;
			while (menu[1] != ')') {
				split = menu.find("_");
				d_content = menu.substr(1, split-1);
				menu = menu.substr(split + 1);

				split = menu.find("_");
				d_price = menu.substr(0, split);
				menu = menu.substr(split + 1);

				split = menu.find("_");
				d_YN = menu.substr(0, split);
				menu = menu.substr(split + 1);

				//cout << "디버깅3 : " << d_content << "/" << d_price << "/" << d_YN << "/" << endl;
				Detail D(d_content, stoi(d_price), stoi(d_YN));
				M.details.push_back(D);

			}
			menu = menu.substr(2);
			S->menus.push_back(M);
			// 메뉴세부사항[세부 내용, 가격, 적용여부] 정보 가져오기

		}
		// 메뉴들[이름_가격_조리시간_메뉴세부사항] 정보 가져오기

		
		// 쿠폰들[할인가격_최소주문가격_가게이름_가게아이디_사용한고객정보] 정보 가져오기
		string coupon, c_discount, c_minprice, c_storename, c_storeid, c_customerid;
		getline(IF, coupon, ',');
		while (coupon.size() > 2) {
			int split = coupon.find("_");
			c_discount = coupon.substr(1, split - 1);
			coupon = coupon.substr(split + 1);

			split = coupon.find("_");
			c_minprice = coupon.substr(0, split);
			coupon = coupon.substr(split + 1);

			split = coupon.find("_");
			c_storename = coupon.substr(0, split);
			coupon = coupon.substr(split + 1);

			split = coupon.find("_");
			c_storeid = coupon.substr(0, split);
			coupon = coupon.substr(split + 1);

			//cout << "디버깅4 : " << c_discount << "/" << c_minprice << "/" << c_storename << "/" << c_storeid << "/" <<endl;
			Coupon C(stoi(c_discount), stoi(c_minprice), c_storename, c_storeid);

			// 사용한고객정보 가져오기
			while (coupon[1] != ')') {
				split = coupon.find("_");
				c_storeid = coupon.substr(1, split - 1);
				coupon = coupon.substr(split + 1);

				//cout << "디버깅5 : " << c_storeid << "/" << endl;
				C.customerIDs.push_back(c_storeid);

			}
			coupon = coupon.substr(2);
			S->coupons.push_back(C);
			// 사용한고객정보 가져오기

		}
		// 쿠폰들[할인가격_최소주문가격_가게이름_가게아이디_사용한고객정보] 정보 가져오기

		

		//배달가능지역 정보 가져오기
		string deliverArea, area;
		getline(IF, deliverArea, ',');
		while (deliverArea.size() > 2) {
			int split = deliverArea.find("_");
			area = deliverArea.substr(1, split - 1);
			deliverArea = deliverArea.substr(split + 1);

			//cout << "디버깅6 : " << area << "/" << endl;
			S->DeliveryArea.push_back(area);
		}
		//배달가능지역 정보 가져오기

		//배달시간 정보 가져오기
		string deliveryTime, time;
		getline(IF, deliveryTime, '\n');
		while (deliveryTime.size() > 2) {
			int split = deliveryTime.find("_");
			time = deliveryTime.substr(1, split - 1);
			deliveryTime = deliveryTime.substr(split + 1);

			//cout << "디버깅7 : " << time << "/" << endl;
			S->DeliveryTime.push_back(stoi(time));
		}
		//배달시간 정보 가져오기

		installers.insert(installers.begin(), S);

	}

	getline(IF, str);	//고객 헤더라인 건너뛰기
	while (!IF.eof()) {
		//고객 이름, 전화번호, 지역, 아이디, 비밀번호, 잔액, 등급, 누적주문금액 정보 가져오기
		string name, phoneNum, Area, id, password, Balance, Level, Accumulated;
		getline(IF, name, ',');
		if (name.size() < 1) {
			break;
		}
		getline(IF, phoneNum, ',');
		getline(IF, Area, ',');
		getline(IF, id, ',');
		getline(IF, password, ',');
		getline(IF, Balance, ',');
		getline(IF, Level, ',');
		getline(IF, Accumulated, ',');

		//cout << "디버깅8 : " << name << "/" << phoneNum << "/" << Area << "/" << id << "/" << password << "/" << Balance << "/" << Level << "/" << Accumulated << "/" << endl;
		Customer* C = new Customer(name, phoneNum, Area, id, password);
		C->Balance = stoi(Balance);
		C->Level = stoi(Level);
		C->Accumulated = stoi(Accumulated);
		//고객 이름, 전화번호, 지역, 아이디, 비밀번호, 잔액, 등급, 누적주문금액 정보 가져오기


		// 쿠폰들[할인가격_최소주문가격_가게이름_가게아이디_사용한고객정보] 정보 가져오기
		string coupon, c_discount, c_minprice, c_storename, c_storeid, c_customerid;
		getline(IF, coupon, '\n');
		while (coupon.size() > 2) {
			int split = coupon.find("_");
			c_discount = coupon.substr(1, split - 1);
			coupon = coupon.substr(split + 1);

			split = coupon.find("_");
			c_minprice = coupon.substr(0, split);
			coupon = coupon.substr(split + 1);

			split = coupon.find("_");
			c_storename = coupon.substr(0, split);
			coupon = coupon.substr(split + 1);

			split = coupon.find("_");
			c_storeid = coupon.substr(0, split);
			coupon = coupon.substr(split + 1);

			//cout << "디버깅9 : " << c_discount << "/" << c_minprice << "/" << c_storename << "/" << c_storeid << "/" << endl;
			Coupon Cp(stoi(c_discount), stoi(c_minprice), c_storename, c_storeid);

			// 사용한고객정보 가져오기
			while (coupon[1] != ')') {
				split = coupon.find("_");
				c_storeid = coupon.substr(1, split - 1);
				coupon = coupon.substr(split + 1);

				//cout << "디버깅10 : " << c_storeid << "/" << endl;
				Cp.customerIDs.push_back(c_storeid);

			}
			coupon = coupon.substr(2);
			C->coupons.push_back(Cp);
			// 사용한고객정보 가져오기

		}
		// 쿠폰들[할인가격_최소주문가격_가게이름_가게아이디_사용한고객정보] 정보 가져오기

		installers.push_back(C);

	}

}

//동적할당 배열 installers 공간 해제해주는 소멸자
Delivery::~Delivery() {

	ofstream OF("list.csv");
	int i = 0;
	OF << "가게 > 이름, 전화번호, 지역, 아이디, 비밀번호, 매출, 메뉴들[이름_가격_조리시간_메뉴세부사항], 쿠폰들[할인가격_최소주문가격_가게이름_가게아이디_사용한고객정보], [배달가능지역], [배달시간] " << endl;
	for (; i < installers.size(); i++) {
		if (typeid(*installers[i]) == typeid(Store)) {
			Store* S = (Store*)installers[i];
			OF << S->name << ',' << S->phoneNum << ',' << S->Area << ',' << S->id << ',' << S->password << ',' << S->Balance << ',';

			OF << '[';
			for (int j = 0; j < S->menus.size(); j++) {
				Menu M = S->menus[j];
				OF << M.name << '_' << M.price << '_' << M.cooktime << "_(";
				for (int k = 0; k < M.details.size(); k++) {
					Detail D = M.details[k];
					OF << D.content << '_' << D.price << '_' << D.YN << "_/";
				}
				OF << ")/";
			}
			
			OF << "],";

			OF << '[';
			for (int j = 0; j < S->coupons.size(); j++) {
				Coupon C = S->coupons[j];
				OF << C.Discount << '_' << C.MinPrice << '_' << C.storeName << '_' << C.storeID << "_(";
				for (int k = 0; k < C.customerIDs.size(); k++) {
					OF << C.customerIDs[k] << "_/";
				}
				OF << ")/";

			}
			OF << "],";

			OF << '[';
			for (int j = 0; j < S->DeliveryArea.size(); j++) {
				OF << S->DeliveryArea[j] << "_/";
			}
			OF << "],";

			OF << '[';
			for (int j = 0; j < S->DeliveryTime.size(); j++) {
				OF << S->DeliveryTime[j] << "_/";
			}
			OF << "]\n";
		}
		else {
			break;
		}

	}


	OF << "\n손님 > 이름,전화번호,지역,아이디,비밀번호,잔고,회원등급,누적주문금액,[보유 쿠폰]" << endl;
	for (; i < installers.size(); i++) {
		if (typeid(*installers[i]) == typeid(Customer)) {
			Customer* C = (Customer*)installers[i];

			OF << C->name << ',' << C->phoneNum << ',' << C->Area << ',' << C->id << ',' << C->password << ',' << C->Balance << ',' << C->Level << ',' << C->Accumulated << ',';

			OF << '[';
			for (int j = 0; j < C->coupons.size(); j++) {
				Coupon Cp = C->coupons[j];
				OF << Cp.Discount << '_' << Cp.MinPrice << '_' << Cp.storeName << '_' << Cp.storeID << "_(";
				for (int k = 0; k < Cp.customerIDs.size(); k++) {
					OF << Cp.customerIDs[k] << "_/";
				}
				OF << ")/";

			}
			OF << "]\n";

		}

	}

	OF.close();


	for (int i = 0; i < installers.size(); i++) {
		delete installers[i];
	}
}

//입력예외처리함수 ( 정수 자료형에 문자값을 넣었을 때)
int Delivery::Input() {
	int tmp;
	cin >> tmp;
	//int자료형에 다른 값이 들어갔을때 예외처리
	if (!cin) {
		//입력버퍼에 있는값을 초기화해줌으로써 무한루프 오류 해결
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return tmp;
}

//배열에서 i-1번째 인덱스에 있는 객체를 반환해주는 템플릿 함수 ( Installer::menus, Installer::coupons, Installer::gifticons,Store::DeliveryArea, Store::DeliveryTime, Menu::details 에 사용)
template<class T>
T* Delivery::selectObj(vector<T>* list, int i) {
	//입력된 i가 배열list 인덱스 범위라면, 해당 인덱스 객체 주소 반환
	if (i <= list->size() && i >= 1) return &list->at(i - 1);
	//인덱스 범위가 아니라면 NULL값 반환
	else return NULL;
}

//배열에서 i-1번째 인덱스에 있는 객체를 제거해주는 템플릿 함수 ( Installer::menus, Installer::coupons, Installer::gifticons,Store::DeliveryArea, Store::DeliveryTime, Menu::details에 사용) 
template<class K>
bool Delivery::Delete(vector<K>* list, K* tmp, int index) {
	//배열(list)의 인덱스(index)에 해당하는 객체(tmp)가 존재한다면 제거
	if (tmp != NULL) {
		list->erase(list->begin() + index - 1);	//vector의 erase함수를 이용해 index-1에 해당하는 객체 제거
		return true;
	}
	else return false;	//예외처리
}

//설치자 아이디를 통해 installers에서 위치(인덱스)를 찾아 반환
int Delivery::FindInstallerID(string id) {
	int i = 0;	//반복문 변수 설정
	for (; i < installers.size(); i++) {
		//매개변수의 id를 가진 설치자가 있다면 반복문 종료
		if (installers[i]->id == id) break;
	}
	//설치자가 있다면 i값은 installers크기보다 작고, 설치자가 없다면 i == installers.size()가 된다.

	//반복문 변수 반환
	return i;
}

//installers에 설치자 추가(회원가입)
void Delivery::InstallerJoin() {
	system("cls");
	cout << endl << "***회원가입***" << endl;
	//설치자 정보를 입력받을 변수들 선언
	string name, phoneNum, Area, id, password;
	cout << "1.고객  2.가게 : ";
	in = Input();	//고객과 가게중 어느 것을 생성할지 결정

	if (in != 1 && in != 2) {	//예외처리
		cout << "잘못 입력하셨습니다." << endl;
		return;
	}

	cout << "'이름' '전화번호(-없이, 이어서)' '지역'을입력하세요. : ";
	cin >> name >> phoneNum >> Area;

	cout << "아이디 비밀번호를 입력하세요. : ";
	cin >> id >> password;


	if (FindInstallerID(id) != installers.size()) {	//예외처리 ( 중복되는 아이디가 존재할 때 )
		cout << "이미 사용중인 아이디입니다." << endl;
	}
	else {
		//vector의 멤버함수 push_back함수를 통해 새로운 고객 객체를 배열 맨뒤에 추가
		if (in == 1) {
			Customer* C = new Customer(name, phoneNum, Area, id, password);
			installers.push_back(C);
		}
		//vector의 멤버함수 insert함수를 통해 새로운 가게 객체를 배열 맨앞에 추가
		else if (in == 2) {
			Store* S = new Store(name, phoneNum, Area, id, password);
			installers.insert(installers.begin(), S);
		}
		cout << "\n^0^ 회원가입 완료 ^0^" << endl;
	}
}

//installers에서 설치자 제거(회원탈퇴)
bool Delivery::InstallerLeave(Installer* IT) {
	cout << endl << "***회원탈퇴***" << endl;
	string check; //비밀번호 확인을 하기 위한 변수 선언
	int i = FindInstallerID(IT->id);	//설치자 IT의 위치를 i에 저장

	cout << "탈퇴하시려면 비밀번호 인증이 필요합니다. : ";
	cin >> check;

	if (check == IT->password) { // 비밀번호가 일치하다면 탈퇴진행
		//vector의 멤버함수 erase를 통해 i번째 위치한 객체 제거
		delete installers[i];
		installers.erase(installers.begin() + i);
		cout << "탈퇴되었습니다." << endl;
		return true;
	}
	else {	// 비밀번호가 다르다면 탈퇴종료
		cout << "비밀번호가 틀렸습니다." << endl;
		return false;
	}
}

//설치자 아이디와 비밀번호를 통해 installers에서 해당하는 고객 반환( 로그인 )
Installer* Delivery::InstallerLogin() {
	cout << endl << "***로그인***" << endl;

	string IDcheck, PWcheck;	//아이디와 비밀번호 확인을 위한 변수 선언

	cout << "아이디와 비밀번호를 입력하세요. : ";
	cin >> IDcheck >> PWcheck;

	int i = FindInstallerID(IDcheck);	//해당하는 아이디를 가진 설치자 위치 i에 저장

	//해당하는 아이디를 가진 설치자가 없다면 NULL반환
	if (i == installers.size()) {
		cout << "아이디가 존재하지 않습니다." << endl;
		return NULL;
	}
	//설치자의 비밀번호와 일치하면 로그인 완료
	if (installers[i]->password == PWcheck) {
		cout << "로그인 성공" << endl;
		return installers[i];	//해당 고객 반환
	}
	//비밀번호가 일치하지 않으면 로그인 실패 NULL반환
	else {
		cout << "비밀번호가 틀립니다." << endl;
		return NULL;
	}

}

//고객이 원하는 가게를 선택하면 그 가게를 반환 ( 주문, 기프티콘 선물할때 사용 )
Store* Delivery::SelectStore() {
	cout << "현재 가게 목록 : ";
	int i = 0; //반복문 변수 선언
	//반복문을 통해 installers에 있는 가게 이름 출력
	for (; i < installers.size(); i++) {
		//typeid함수를 이용해 가게 객체만 출력
		//회원가입할때 가게 객체는 맨앞에 저장했으므로 가게 객체들은 항상 고객보다 앞에 존재
		if (typeid(*installers[i]) != typeid(Store)) break;
		cout << i + 1 << ". " << installers[i]->name << " ";
	}
	cout << endl;

	//주문하고싶은 가게 위치(인덱스)입력 ( 0~i )
	cout << "어떤 가게를 선택하시겠습니까? : ";
	in = Input();

	//in가 가게 인덱스 범위에 있다면 가게 객체 반환
	if (in <= i + 1 && in >= 1) return (Store*)installers[in - 1];
	//in가 가게 인덱스 범위밖이라면  NULL반환
	else return NULL;
}

//고객과 가게의 정보를 통해 총 배달 소요시간을 반환	( 주문할때 사용 )
int Delivery::DeliveryTime(Store* S, Customer* C, int i) {
	int totaltime = 0;	//총 배달소요시간을 저장하는 변수 선언 및 초기화
	//첫 번째 반복문을 이용하여 고객 장바구니에 있는 메뉴의 조리시간을 추가
	for (int i = 0; i < C->menus.size(); i++) {
		totaltime += C->menus[i].cooktime;
	}
	C->menus.clear();	//주문 완료 후 장바구니 초기화

	if (i == 2) {
		//고객의 주소까지 배달되는 시간 추가
		for (int i = 0; i < S->DeliveryArea.size(); i++) {
			if (C->Area == S->DeliveryArea[i]) {  //고객의 지역과 가게에 저장된 배달 가능 지역 중 일치하는 부분이 있다면
				totaltime += S->DeliveryTime[i];  //해당 지역 소요시간을 추가
				break;
			}
		}
	}
	return totaltime;	//총 배달 소요시간 반환
}

//초기화면 인터페이스 ( 회원가입, 로그인 )
void Delivery::StartInterface() {
	system("cls");
	while (true) {	//반복문을 통해 인터페이스 반복
		cout << endl << "***초기화면***" << endl;
		cout << "1.회원가입  2.로그인  3.프로그램 종료 : ";
		in = Input();
		if (in == 1) InstallerJoin();	//회원가입
		else if (in == 2) {				//로그인
			Installer* IT = InstallerLogin();
			if (IT == NULL) continue;	//IT가 NULL이라면 로그인 실패
			else if (typeid(*IT) == typeid(Customer)) CustomerInterface((Customer*)IT);	//typeid함수를 이용해 IT가 고객 타입이라면 고객 인터페이스로 이동
			else if (typeid(*IT) == typeid(Store)) ManagerInterface((Store*)IT);		//typeid함수를 이용해 IT가 가게 타입이라면 가게 인터페이스로 이동
		}
		else if (in == 3) {	//프로그램 종료
			cout << endl << "프로그램 종료." << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;
	}

}

//고객으로 로그인했을때 사용되는 인터페이스 ( 주문 / 선물하기 / 잔액관리 / 회원등급 / 회원탈퇴 )
void Delivery::CustomerInterface(Customer* C) {
	system("cls");
	while (true) {		//반복문을 통해 인터페이스 반복
		cout << endl << C->name << "님, 환영합니다." << endl;
		cout << "1.주문 2.잔액관리 3.회원등급확인 4.회원탈퇴 5.로그아웃 : ";
		in = Input();	//어떤 작업을 할지 입력받기

		if (in == 1) StoreInterface(C);		//주문 인터페이스로 이동
		else if (in == 2) MoneyInterface(C); //고객 잔액 인터페이스로 이동
		else if (in == 3) C->Membership();	//회원 등급 확인
		else if (in == 4) {
			if (InstallerLeave(C)) break; //회원탈퇴 성공시 인터페이스 반복 종료
		}
		else if (in == 5) {	//고객 인터페이스 종료
			cout << endl << "초기화면으로." << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}

}

//고객 잔액관리 인터페이스 ( 잔액확인 / 잔액충전/ 잔액인출 )
void Delivery::MoneyInterface(Customer* C) {
	system("cls");
	//반복문을 통해 인터페이스 반복
	while (true) {
		cout << endl << "***잔액관리***" << endl;
		cout << "1.잔액확인  2.충전  3.인출  4.뒤로가기 : ";
		in = Input();	//어떤 작업을 할지 입력받기

		if (in == 1) {
			cout << endl << "***잔액 확인***" << endl;
			C->ShowBalance();	//잔액 출력
		}
		else if (in == 2) {
			cout << endl << "***잔액 충전***" << endl;
			C->ShowBalance();	//현재 잔액 출력
			cout << "얼마를 충전하시겠습니까? : ";
			in = Input();		//충전 금액 입력
			if (C->PlusBalance(in)) cout << "충전이 완료되었습니다." << endl;	//입력받은 값을 통해 잔액 충전
			else cout << "잘못 입력하셨습니다." << endl;
		}
		else if (in == 3) {
			cout << endl << "***잔액 인출***" << endl;
			C->ShowBalance();		//현재 잔액 출력
			cout << "인출 금액을 입력해주세요 : ";
			in = Input();			//인출 금액 입력
			C->MinusBalance(in);	//입력받은 값을 통해 잔액 인출
		}
		else if (in == 4) {			//잔액 인터페이스 종료
			cout << endl << "이전화면으로" << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}
}

//고객 주문 인터페이스	( 가게 선택 후 -> 장바구니 관리 / 주문하기 / 쿠폰추가 )
void Delivery::StoreInterface(Customer* C) {
	system("cls");
	cout << endl << "***주문***" << endl;
	Store* S = SelectStore();	//주문할 가게 선택
	if (S != NULL) {			//주문할 가게 선택 후
		while (true) {			//반복문을 통해 인터페이스 반복
			cout << endl << "어서오세요 " << S->name << "입니다!" << endl;
			cout << "1.장바구니  2.주문하기  3.쿠폰추가  4.뒤로가기 : ";
			in = Input();		//어떤 작업을 할지 입력받기

			if (in == 1) BasketInterface(C, S);	//장바구니 인터페이스로 이동
			else if (in == 2) {					//주문하기 인터페이스로 이동
				if (C->menus.size() == 0) cout << endl << "장바구니에 메뉴가 없습니다. 추가해주세요." << endl;	//예외처리 ( 장바구니에 메뉴가 없는 경우 )
				else OrderInterface(C, S);
			}
			else if (in == 3) {		//쿠폰 추가
				cout << endl << "***쿠폰 추가***" << endl;
				cout << "현재 쿠폰 : ";
				S->ShowCoupon();	//가게의 쿠폰목록 출력
				cout << "추가하실 쿠폰 번호를 입력해주세요. : ";
				in = Input();		//목록에서 쿠폰 선택
				Coupon* m = selectObj<Coupon>(&S->coupons, in);
				C->AddCoupon(m);	//고객의 쿠폰함에 쿠폰 추가
			}
			else if (in == 4) {		//주문 인터페이스 종료
				C->menus.clear();	//장바구니 목록 초기화 ( 주문을 완료했으므로 )
				cout << endl << "장바구니 목록이 초기화되었습니다." << endl;
				break;
			}
			else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
		}
	}
}

//고객 장바구니 인터페이스	( 장바구니 목록 / 장바구니 추가 / 장바구니 삭제 )
void Delivery::BasketInterface(Customer* C, Store* S) {
	system("cls");
	while (true) {	//반복문을 통해 인터페이스 반복
		cout << endl << "***장바구니***" << endl;
		cout << "1.장바구니목록  2.장바구니추가  3.장바구니삭제  4.뒤로가기 : ";
		in = Input();	//어떤 작업을 할지 입력받기

		if (in == 1) {	//장바구니 목록과 총 금액 출력
			cout << endl << "***장바구니 목록***" << endl;
			cout << "총 : " << C->ShowMenu() << "원 입니다." << endl;
		}
		else if (in == 2) {	//장바구니에 메뉴 추가
			cout << endl << "***장바구니 추가***" << endl;
			// 가게의 메뉴목록에서 메뉴 선택
			cout << "어떤 메뉴를 추가하시겠습니까? : ";
			S->ShowMenu();
			in = Input();
			Menu* m = selectObj<Menu>(&S->menus, in);
			if (m != NULL)C->AddMenu(*m);	//고객의 장바구니에 선택한 메뉴 추가
			else cout << "잘못 입력하셨습니다." << endl;
		}
		else if (in == 3) {	//장바구니에서 메뉴 삭제
			cout << endl << "***장바구니 삭제***" << endl;
			cout << "현재 장바구니 목록 : ";
			// 고객의 장바구니목록에서 메뉴 선택
			C->ShowMenu();
			cout << "삭제하실 메뉴의 번호를 입력하세요. : ";
			in = Input();
			Menu* m = selectObj<Menu>(&C->menus, in);
			Delete<Menu>(&C->menus, m, in);	//고객의 장바구니에 선택한 메뉴 삭제
		}
		else if (in == 4) {	//주문인터페이스 종료
			cout << endl << "이전화면으로" << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}
}


//고객 주문하기 인터페이스	( 쿠폰사용 / 기프티콘사용 / 주문진행 )
void Delivery::OrderInterface(Customer* C, Store* S) {
	system("cls");
	cout << endl << "***주문진행***" << endl;
	int Deliveryprice = C->ShowMenu();		//주문금액 ( 고객의 장바구니에 담겨있는 메뉴의 총 액 )
	int CouponPrice = 0, totalPrice = 0;	//쿠폰 할인 금액, 주문금액에서 할인금액을 뺀 실제 주문 금액
	int CouponIndex;	//고객의 쿠폰함에서 사용할 쿠폰과 기프티콘의 위치(인덱스)를 저장할 변수
	Coupon* c = NULL;	//고객의 쿠폰함에서 사용할 쿠폰

	while (true) {
		//실제 주문 금액 = 주문금액 - 쿠폰금액
		totalPrice = Deliveryprice - CouponPrice;
		cout << endl << "(주문금액 : " << Deliveryprice << "원) - (할인금액 : " << CouponPrice << "원) ===> (총금액 : " << totalPrice << "원)" << endl;
		cout << "1.쿠폰사용 2.주문하기 3.뒤로가기 : ";
		in = Input();	//어떤 작업을 할지 입력받기

		if (in == 1) {	//쿠폰 적용
			if (c == NULL) {
				cout << endl << "***쿠폰 사용***" << endl;
				//고객의 쿠폰함에서 쿠폰 선택
				C->ShowCoupon();
				cout << "어떤 쿠폰을 사용하시겠습니까? : ";
				CouponIndex = Input();
				c = selectObj<Coupon>(&C->coupons, CouponIndex);

				if (c == NULL) cout << "잘못 입력하셨습니다." << endl;	//예외처리 ( 잘못된 쿠폰 번호를 입력했을경우 )
				else if (c->storeID != S->id) {	//예외처리 ( 다른 가게의 쿠폰 번호를 입력했을 경우 )
					c = NULL;
					cout << "해당 가게의 쿠폰만 사용가능합니다." << endl;
				}
				else if (Deliveryprice < c->MinPrice) {	//예외처리 ( 주문금액이 해당 쿠폰의 최소주문금액보다 낮은 경우 )
					c = NULL;
					cout << "주문금액이 부족합니다." << endl;
				}
				else {	//모든 조건을 충족하면 쿠폰적용
					CouponPrice += c->Discount;
					cout << "쿠폰이 적용되었습니다." << endl;
				}
			}
			else cout << "이미 쿠폰을 적용하였습니다." << endl;	//예외처리 ( 하나의 주문에는 하나의 쿠폰만 사용 가능 )
		}
		else if (in == 2) {	//주문진행
			cout << endl << "***주문***" << endl;
			cout << "픽업 방법을 결정해주세요 1. 포장  2. 배달 : ";
			in = Input();
			if (in == 1) {
				if (C->Ordering(totalPrice)) {	//실제 주문금액으로 결제 진행
					//결제가 성공하면
					cout << "주문이 완료되었습니다." << endl;
					S->TotalOrder++;	//가게의 주문건수 추가
					S->PlusBalance(Deliveryprice);	//가게의 매출액에 주문금액 추가
					cout << "포장 완료까지 총 " << DeliveryTime(S, C, in) << "분 걸립니다." << endl;	//배달시간 출력

					//사용한 쿠폰 고객의 쿠폰함에 제거
					if (c != NULL) Delete<Coupon>(&C->coupons, c, CouponIndex);

					break;
				}
				else cout << endl << "잔액이 부족하여 결제를 실패하였습니다. " << endl;	//예외처리 ( 잔액가 부족한 경우 )
			}
			else if (in == 2) {
				if (C->Ordering(totalPrice)) {	//실제 주문금액으로 결제 진행
					//결제가 성공하면
					cout << "주문이 완료되었습니다." << endl;
					S->TotalOrder++;	//가게의 주문건수 추가
					S->PlusBalance(Deliveryprice);	//가게의 매출액에 주문금액 추가
					cout << "배달 완료까지 총 " << DeliveryTime(S, C, in) << "분 걸립니다." << endl;	//배달시간 출력

					//사용한 쿠폰 고객의 쿠폰함에 제거
					if (c != NULL) Delete<Coupon>(&C->coupons, c, CouponIndex);

					break;
				}
				else cout << endl << "잔액이 부족하여 결제를 실패하였습니다. " << endl;	//예외처리 ( 잔액가 부족한 경우 )
			}
			else cout << endl << "주문취소" << endl;
		}
		else if (in == 3) {	//뒤로가기
			cout << endl << "이전화면으로" << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}
}

//가게로 로그인했을때 사용되는 인터페이스 ( 메뉴관리 / 메뉴세부내용관리 / 배달지역 / 쿠폰관리 / 주문확인 /회원탈퇴 )
void Delivery::ManagerInterface(Store* S) {
	system("cls");
	while (true) { //반복문을 통해 인터페이스 반복
		cout << endl << S->name << "님 환영합니다." << endl;
		cout << "1.메뉴관리  2.메뉴세부내용관리  3.배달지역관리  4.쿠폰관리 5.주문확인 6.회원탈퇴 7.로그아웃 : ";
		in = Input();

		if (in == 1) MenuInterface(S);	//메뉴관리 인터페이스로 이동
		else if (in == 2) {
			cout << endl << "현재 메뉴 : ";
			S->ShowMenu();	//메뉴목록 출력
			cout << "어떤 메뉴의 세부내용을 관리하시겠습니까? : ";
			in = Input();	//메뉴 선택
			Menu* m = selectObj<Menu>(&S->menus, in);
			DetailInterface(m);	//메뉴세부내용확인
		}
		else if (in == 3) DeliveryAreaInterface(S);	//배달지역관리 인터페이스로 이동
		else if (in == 4) CouponInterface(S);	//쿠폰관리 인터페이스로 이동
		else if (in == 5) {	//가게의 주문건수와 매출 확인
			cout << endl << "***주문확인***" << endl;
			S->ShowTotalOrder();
		}
		else if (in == 6) {	//회원탈퇴
			if (InstallerLeave(S)) break; //회원탈퇴가 성공했으면 인터페이스 종료
		}
		else if (in == 7) {	//가게 인터페이스 종료
			cout << endl << "로그아웃 처리되었습니다." << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}

}

//가게 메뉴관리 인터페이스 ( 메뉴목록 / 메뉴추가 / 메뉴삭제 )
void Delivery::MenuInterface(Store* S) {
	system("cls");
	while (true) { //반복문을 통해 인터페이스 반복
		cout << endl << "***메뉴관리***" << endl;
		cout << "1.메뉴목록  2.메뉴추가  3.메뉴삭제  4.뒤로가기 : ";
		in = Input(); //어떤 작업을 할지 입력받기

		if (in == 1) {	//메뉴목록 출력
			cout << endl << "***현재메뉴목록***" << endl;
			S->ShowMenu();
		}
		else if (in == 2) {	//메뉴추가
			cout << endl << "***메뉴추가***" << endl;
			S->AddMenu();
		}
		else if (in == 3) {	//메뉴삭제
			cout << endl << "***메뉴삭제***" << endl;
			//가게의 메뉴목록에서 삭제할 메뉴 선택
			cout << "현재 메뉴 목록 : ";
			S->ShowMenu();
			cout << "삭제하실 메뉴 번호를 입력하세요. : ";
			in = Input();

			Menu* m = selectObj<Menu>(&S->menus, in);
			Delete<Menu>(&S->menus, m, in);	//가게의 메뉴목록에서 선택한 메뉴 삭제
		}
		else if (in == 4) {	//메뉴내용 인터페이스 종료
			cout << endl << "이전화면으로" << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}
}

//가게 메뉴세부내용관리 인터페이스 ( 메뉴세부내용목록 / 메뉴세부내용추가 / 메뉴세부내용삭제 )
void Delivery::DetailInterface(Menu* M) {
	system("cls");
	while (M != NULL) {	//반복문을 통해 인터페이스 반복
		cout << endl << "***" << M->name << "의 세부내용관리***" << endl;
		cout << "1.세부내용목록  2.세부내용추가  3.세부내용삭제  4.뒤로가기 : ";
		in = Input();	//어떤 작업을 할지 입력받기

		if (in == 1) {	//메뉴세부내용목록 출력
			cout << endl << "***세부내용 목록***" << endl;
			M->DetailList();
		}
		else if (in == 2) {	//메뉴세부내용 추가
			cout << endl << "***세부내용 추가***" << endl;
			M->AddDetail();
		}
		else if (in == 3) {	//메뉴세부내용 삭제
			cout << endl << "***세부내용 삭제***" << endl;
			//메뉴의 메뉴세부내용목록에서 삭제할 메뉴세부내용 선택
			cout << "현재 세부내용 : ";
			M->DetailList();
			cout << "삭제하실 세부사항을 입력하세요. : ";
			in = Input();

			Detail* d = selectObj<Detail>(&M->details, in);
			Delete<Detail>(&M->details, d, in);	//메뉴의 메뉴세부내용목록에서 선택한 메뉴세부내용 삭제
		}
		else if (in == 4) {	//메뉴세부내용 인터페이스 종료
			cout << endl << "이전화면으로" << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}
}

//가게 배달지역관리 인터페이스 ( 배달지역목록 / 배달지역추가 / 배달지역삭제 )
void Delivery::DeliveryAreaInterface(Store* S) {
	system("cls");
	while (true) {	//반복문을 통해 인터페이스 반복
		cout << endl << "***배달지역관리***" << endl;
		cout << "1.배달지역목록  2.배달지역추가  3.배달지역삭제  4.뒤로가기 : ";
		in = Input();	//어떤 작업을 할지 입력받기

		if (in == 1) {	//배달지역목록과 배달시간목록 출력
			cout << endl << "***배달지역 목록***" << endl;
			S->ShowDeliveryArea();
		}
		else if (in == 2) { //배달지역과 배달시간 추가
			cout << endl << "***배달지역 추가***" << endl;
			S->AddDeliveryArea();
		}
		else if (in == 3) {
			cout << endl << "***배달지역 삭제***" << endl;
			//가게의 배달지역목록과 배달시간목록에서 삭제할 배달지역과 배달시간 선택
			cout << "현재 배달 가능 지역 : ";
			S->ShowDeliveryArea();
			cout << "삭제하실 지역을 입력해주세요. : ";
			in = Input();

			string* Area = selectObj<string>(&S->DeliveryArea, in);
			int* time = selectObj<int>(&S->DeliveryTime, in);
			//선택한 배달지역과 배달시간 삭제
			Delete<string>(&S->DeliveryArea, Area, in);
			Delete<int>(&S->DeliveryTime, time, in);
		}
		else if (in == 4) {	//배달지역관리 인터페이스 종료
			cout << endl << "이전화면으로" << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}
}

//가게 쿠폰관리 인터페이스 ( 쿠폰목록 / 쿠폰추가 / 쿠폰삭제 )
void Delivery::CouponInterface(Store* S) {
	system("cls");
	while (true) {	//반복문을 통해 인터페이스 반복
		cout << endl << "***쿠폰관리***" << endl;
		cout << "1.쿠폰목록  2.쿠폰추가  3.쿠폰삭제  4.뒤로가기 : ";
		in = Input();	//어떤 작업을 할지 입력받기

		if (in == 1) {	//쿠폰목록 출력
			cout << endl << "***쿠폰 목록***" << endl;
			S->ShowCoupon();
		}
		else if (in == 2) {	//쿠폰 추가
			cout << endl << "***쿠폰 추가***" << endl;
			S->AddCoupon();
		}
		else if (in == 3) {	//쿠폰 삭제
			cout << endl << "***쿠폰 삭제***" << endl;
			//가게의 쿠폰목록에서 삭제할 쿠폰 선택
			cout << "현재 쿠폰 : ";
			S->ShowCoupon();
			cout << "삭제하실 쿠폰 번호를 입력해주세요. : ";
			in = Input();

			Coupon* c = selectObj<Coupon>(&S->coupons, in);
			Delete<Coupon>(&S->coupons, c, in);	//선택한 쿠폰 제거
		}
		else if (in == 4) {	//쿠폰관리 인터페이스 종료
			cout << endl << "이전화면으로" << endl;
			break;
		}
		else cout << endl << "잘못 입력하셨습니다." << endl;	//예외처리
	}
}