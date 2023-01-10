#include"Delivery.h"

//������(list.csv ���� ���� �о����)
Delivery::Delivery() {
	ifstream IF("list.csv");
	if (IF.fail()) {
		return;
	}

	string str;
	getline(IF, str);	//���� ������� �ǳʶٱ�
	while (!IF.eof()) {
		//���� �̸�, ��ȭ��ȣ, ����, ���̵�, ��й�ȣ, ���� ���� ��������
		string name, phoneNum, Area, id, password, Balance;
		getline(IF, name, ',');
		if (name.find("�մ�") != name.find("NOT_FOUND") || name.size()<1) {
			break;
		}
		getline(IF, phoneNum, ',');
		getline(IF, Area, ',');
		getline(IF, id, ',');
		getline(IF, password, ',');
		getline(IF, Balance, ',');

		//cout << "�����1 : " << name << "/" << phoneNum << "/" << Area << "/" << id << "/" << password << "/" << Balance << "/" << endl;
		Store *S = new Store(name, phoneNum, Area, id, password);
		S->Balance = stoi(Balance);
		//���� �̸�, ��ȭ��ȣ, ����, ���̵�, ��й�ȣ, ���� ���� ��������


		// �޴���[�̸�_����_�����ð�_�޴����λ���] ���� ��������
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

			//cout << "�����2 : " << m_name << "/" <<  m_price << "/" <<  m_cooktime << "/" <<endl;
			Menu M(m_name, stoi(m_price), stoi(m_cooktime));

			// �޴����λ���[���� ����, ����, ���뿩��] ���� ��������
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

				//cout << "�����3 : " << d_content << "/" << d_price << "/" << d_YN << "/" << endl;
				Detail D(d_content, stoi(d_price), stoi(d_YN));
				M.details.push_back(D);

			}
			menu = menu.substr(2);
			S->menus.push_back(M);
			// �޴����λ���[���� ����, ����, ���뿩��] ���� ��������

		}
		// �޴���[�̸�_����_�����ð�_�޴����λ���] ���� ��������

		
		// ������[���ΰ���_�ּ��ֹ�����_�����̸�_���Ծ��̵�_����Ѱ�����] ���� ��������
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

			//cout << "�����4 : " << c_discount << "/" << c_minprice << "/" << c_storename << "/" << c_storeid << "/" <<endl;
			Coupon C(stoi(c_discount), stoi(c_minprice), c_storename, c_storeid);

			// ����Ѱ����� ��������
			while (coupon[1] != ')') {
				split = coupon.find("_");
				c_storeid = coupon.substr(1, split - 1);
				coupon = coupon.substr(split + 1);

				//cout << "�����5 : " << c_storeid << "/" << endl;
				C.customerIDs.push_back(c_storeid);

			}
			coupon = coupon.substr(2);
			S->coupons.push_back(C);
			// ����Ѱ����� ��������

		}
		// ������[���ΰ���_�ּ��ֹ�����_�����̸�_���Ծ��̵�_����Ѱ�����] ���� ��������

		

		//��ް������� ���� ��������
		string deliverArea, area;
		getline(IF, deliverArea, ',');
		while (deliverArea.size() > 2) {
			int split = deliverArea.find("_");
			area = deliverArea.substr(1, split - 1);
			deliverArea = deliverArea.substr(split + 1);

			//cout << "�����6 : " << area << "/" << endl;
			S->DeliveryArea.push_back(area);
		}
		//��ް������� ���� ��������

		//��޽ð� ���� ��������
		string deliveryTime, time;
		getline(IF, deliveryTime, '\n');
		while (deliveryTime.size() > 2) {
			int split = deliveryTime.find("_");
			time = deliveryTime.substr(1, split - 1);
			deliveryTime = deliveryTime.substr(split + 1);

			//cout << "�����7 : " << time << "/" << endl;
			S->DeliveryTime.push_back(stoi(time));
		}
		//��޽ð� ���� ��������

		installers.insert(installers.begin(), S);

	}

	getline(IF, str);	//�� ������� �ǳʶٱ�
	while (!IF.eof()) {
		//�� �̸�, ��ȭ��ȣ, ����, ���̵�, ��й�ȣ, �ܾ�, ���, �����ֹ��ݾ� ���� ��������
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

		//cout << "�����8 : " << name << "/" << phoneNum << "/" << Area << "/" << id << "/" << password << "/" << Balance << "/" << Level << "/" << Accumulated << "/" << endl;
		Customer* C = new Customer(name, phoneNum, Area, id, password);
		C->Balance = stoi(Balance);
		C->Level = stoi(Level);
		C->Accumulated = stoi(Accumulated);
		//�� �̸�, ��ȭ��ȣ, ����, ���̵�, ��й�ȣ, �ܾ�, ���, �����ֹ��ݾ� ���� ��������


		// ������[���ΰ���_�ּ��ֹ�����_�����̸�_���Ծ��̵�_����Ѱ�����] ���� ��������
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

			//cout << "�����9 : " << c_discount << "/" << c_minprice << "/" << c_storename << "/" << c_storeid << "/" << endl;
			Coupon Cp(stoi(c_discount), stoi(c_minprice), c_storename, c_storeid);

			// ����Ѱ����� ��������
			while (coupon[1] != ')') {
				split = coupon.find("_");
				c_storeid = coupon.substr(1, split - 1);
				coupon = coupon.substr(split + 1);

				//cout << "�����10 : " << c_storeid << "/" << endl;
				Cp.customerIDs.push_back(c_storeid);

			}
			coupon = coupon.substr(2);
			C->coupons.push_back(Cp);
			// ����Ѱ����� ��������

		}
		// ������[���ΰ���_�ּ��ֹ�����_�����̸�_���Ծ��̵�_����Ѱ�����] ���� ��������

		installers.push_back(C);

	}

}

//�����Ҵ� �迭 installers ���� �������ִ� �Ҹ���
Delivery::~Delivery() {

	ofstream OF("list.csv");
	int i = 0;
	OF << "���� > �̸�, ��ȭ��ȣ, ����, ���̵�, ��й�ȣ, ����, �޴���[�̸�_����_�����ð�_�޴����λ���], ������[���ΰ���_�ּ��ֹ�����_�����̸�_���Ծ��̵�_����Ѱ�����], [��ް�������], [��޽ð�] " << endl;
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


	OF << "\n�մ� > �̸�,��ȭ��ȣ,����,���̵�,��й�ȣ,�ܰ�,ȸ�����,�����ֹ��ݾ�,[���� ����]" << endl;
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

//�Է¿���ó���Լ� ( ���� �ڷ����� ���ڰ��� �־��� ��)
int Delivery::Input() {
	int tmp;
	cin >> tmp;
	//int�ڷ����� �ٸ� ���� ������ ����ó��
	if (!cin) {
		//�Է¹��ۿ� �ִ°��� �ʱ�ȭ�������ν� ���ѷ��� ���� �ذ�
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return tmp;
}

//�迭���� i-1��° �ε����� �ִ� ��ü�� ��ȯ���ִ� ���ø� �Լ� ( Installer::menus, Installer::coupons, Installer::gifticons,Store::DeliveryArea, Store::DeliveryTime, Menu::details �� ���)
template<class T>
T* Delivery::selectObj(vector<T>* list, int i) {
	//�Էµ� i�� �迭list �ε��� �������, �ش� �ε��� ��ü �ּ� ��ȯ
	if (i <= list->size() && i >= 1) return &list->at(i - 1);
	//�ε��� ������ �ƴ϶�� NULL�� ��ȯ
	else return NULL;
}

//�迭���� i-1��° �ε����� �ִ� ��ü�� �������ִ� ���ø� �Լ� ( Installer::menus, Installer::coupons, Installer::gifticons,Store::DeliveryArea, Store::DeliveryTime, Menu::details�� ���) 
template<class K>
bool Delivery::Delete(vector<K>* list, K* tmp, int index) {
	//�迭(list)�� �ε���(index)�� �ش��ϴ� ��ü(tmp)�� �����Ѵٸ� ����
	if (tmp != NULL) {
		list->erase(list->begin() + index - 1);	//vector�� erase�Լ��� �̿��� index-1�� �ش��ϴ� ��ü ����
		return true;
	}
	else return false;	//����ó��
}

//��ġ�� ���̵� ���� installers���� ��ġ(�ε���)�� ã�� ��ȯ
int Delivery::FindInstallerID(string id) {
	int i = 0;	//�ݺ��� ���� ����
	for (; i < installers.size(); i++) {
		//�Ű������� id�� ���� ��ġ�ڰ� �ִٸ� �ݺ��� ����
		if (installers[i]->id == id) break;
	}
	//��ġ�ڰ� �ִٸ� i���� installersũ�⺸�� �۰�, ��ġ�ڰ� ���ٸ� i == installers.size()�� �ȴ�.

	//�ݺ��� ���� ��ȯ
	return i;
}

//installers�� ��ġ�� �߰�(ȸ������)
void Delivery::InstallerJoin() {
	system("cls");
	cout << endl << "***ȸ������***" << endl;
	//��ġ�� ������ �Է¹��� ������ ����
	string name, phoneNum, Area, id, password;
	cout << "1.��  2.���� : ";
	in = Input();	//���� ������ ��� ���� �������� ����

	if (in != 1 && in != 2) {	//����ó��
		cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		return;
	}

	cout << "'�̸�' '��ȭ��ȣ(-����, �̾)' '����'���Է��ϼ���. : ";
	cin >> name >> phoneNum >> Area;

	cout << "���̵� ��й�ȣ�� �Է��ϼ���. : ";
	cin >> id >> password;


	if (FindInstallerID(id) != installers.size()) {	//����ó�� ( �ߺ��Ǵ� ���̵� ������ �� )
		cout << "�̹� ������� ���̵��Դϴ�." << endl;
	}
	else {
		//vector�� ����Լ� push_back�Լ��� ���� ���ο� �� ��ü�� �迭 �ǵڿ� �߰�
		if (in == 1) {
			Customer* C = new Customer(name, phoneNum, Area, id, password);
			installers.push_back(C);
		}
		//vector�� ����Լ� insert�Լ��� ���� ���ο� ���� ��ü�� �迭 �Ǿտ� �߰�
		else if (in == 2) {
			Store* S = new Store(name, phoneNum, Area, id, password);
			installers.insert(installers.begin(), S);
		}
		cout << "\n^0^ ȸ������ �Ϸ� ^0^" << endl;
	}
}

//installers���� ��ġ�� ����(ȸ��Ż��)
bool Delivery::InstallerLeave(Installer* IT) {
	cout << endl << "***ȸ��Ż��***" << endl;
	string check; //��й�ȣ Ȯ���� �ϱ� ���� ���� ����
	int i = FindInstallerID(IT->id);	//��ġ�� IT�� ��ġ�� i�� ����

	cout << "Ż���Ͻ÷��� ��й�ȣ ������ �ʿ��մϴ�. : ";
	cin >> check;

	if (check == IT->password) { // ��й�ȣ�� ��ġ�ϴٸ� Ż������
		//vector�� ����Լ� erase�� ���� i��° ��ġ�� ��ü ����
		delete installers[i];
		installers.erase(installers.begin() + i);
		cout << "Ż��Ǿ����ϴ�." << endl;
		return true;
	}
	else {	// ��й�ȣ�� �ٸ��ٸ� Ż������
		cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
		return false;
	}
}

//��ġ�� ���̵�� ��й�ȣ�� ���� installers���� �ش��ϴ� �� ��ȯ( �α��� )
Installer* Delivery::InstallerLogin() {
	cout << endl << "***�α���***" << endl;

	string IDcheck, PWcheck;	//���̵�� ��й�ȣ Ȯ���� ���� ���� ����

	cout << "���̵�� ��й�ȣ�� �Է��ϼ���. : ";
	cin >> IDcheck >> PWcheck;

	int i = FindInstallerID(IDcheck);	//�ش��ϴ� ���̵� ���� ��ġ�� ��ġ i�� ����

	//�ش��ϴ� ���̵� ���� ��ġ�ڰ� ���ٸ� NULL��ȯ
	if (i == installers.size()) {
		cout << "���̵� �������� �ʽ��ϴ�." << endl;
		return NULL;
	}
	//��ġ���� ��й�ȣ�� ��ġ�ϸ� �α��� �Ϸ�
	if (installers[i]->password == PWcheck) {
		cout << "�α��� ����" << endl;
		return installers[i];	//�ش� �� ��ȯ
	}
	//��й�ȣ�� ��ġ���� ������ �α��� ���� NULL��ȯ
	else {
		cout << "��й�ȣ�� Ʋ���ϴ�." << endl;
		return NULL;
	}

}

//���� ���ϴ� ���Ը� �����ϸ� �� ���Ը� ��ȯ ( �ֹ�, ����Ƽ�� �����Ҷ� ��� )
Store* Delivery::SelectStore() {
	cout << "���� ���� ��� : ";
	int i = 0; //�ݺ��� ���� ����
	//�ݺ����� ���� installers�� �ִ� ���� �̸� ���
	for (; i < installers.size(); i++) {
		//typeid�Լ��� �̿��� ���� ��ü�� ���
		//ȸ�������Ҷ� ���� ��ü�� �Ǿտ� ���������Ƿ� ���� ��ü���� �׻� ������ �տ� ����
		if (typeid(*installers[i]) != typeid(Store)) break;
		cout << i + 1 << ". " << installers[i]->name << " ";
	}
	cout << endl;

	//�ֹ��ϰ���� ���� ��ġ(�ε���)�Է� ( 0~i )
	cout << "� ���Ը� �����Ͻðڽ��ϱ�? : ";
	in = Input();

	//in�� ���� �ε��� ������ �ִٸ� ���� ��ü ��ȯ
	if (in <= i + 1 && in >= 1) return (Store*)installers[in - 1];
	//in�� ���� �ε��� �������̶��  NULL��ȯ
	else return NULL;
}

//���� ������ ������ ���� �� ��� �ҿ�ð��� ��ȯ	( �ֹ��Ҷ� ��� )
int Delivery::DeliveryTime(Store* S, Customer* C, int i) {
	int totaltime = 0;	//�� ��޼ҿ�ð��� �����ϴ� ���� ���� �� �ʱ�ȭ
	//ù ��° �ݺ����� �̿��Ͽ� �� ��ٱ��Ͽ� �ִ� �޴��� �����ð��� �߰�
	for (int i = 0; i < C->menus.size(); i++) {
		totaltime += C->menus[i].cooktime;
	}
	C->menus.clear();	//�ֹ� �Ϸ� �� ��ٱ��� �ʱ�ȭ

	if (i == 2) {
		//���� �ּұ��� ��޵Ǵ� �ð� �߰�
		for (int i = 0; i < S->DeliveryArea.size(); i++) {
			if (C->Area == S->DeliveryArea[i]) {  //���� ������ ���Կ� ����� ��� ���� ���� �� ��ġ�ϴ� �κ��� �ִٸ�
				totaltime += S->DeliveryTime[i];  //�ش� ���� �ҿ�ð��� �߰�
				break;
			}
		}
	}
	return totaltime;	//�� ��� �ҿ�ð� ��ȯ
}

//�ʱ�ȭ�� �������̽� ( ȸ������, �α��� )
void Delivery::StartInterface() {
	system("cls");
	while (true) {	//�ݺ����� ���� �������̽� �ݺ�
		cout << endl << "***�ʱ�ȭ��***" << endl;
		cout << "1.ȸ������  2.�α���  3.���α׷� ���� : ";
		in = Input();
		if (in == 1) InstallerJoin();	//ȸ������
		else if (in == 2) {				//�α���
			Installer* IT = InstallerLogin();
			if (IT == NULL) continue;	//IT�� NULL�̶�� �α��� ����
			else if (typeid(*IT) == typeid(Customer)) CustomerInterface((Customer*)IT);	//typeid�Լ��� �̿��� IT�� �� Ÿ���̶�� �� �������̽��� �̵�
			else if (typeid(*IT) == typeid(Store)) ManagerInterface((Store*)IT);		//typeid�Լ��� �̿��� IT�� ���� Ÿ���̶�� ���� �������̽��� �̵�
		}
		else if (in == 3) {	//���α׷� ����
			cout << endl << "���α׷� ����." << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;
	}

}

//������ �α��������� ���Ǵ� �������̽� ( �ֹ� / �����ϱ� / �ܾװ��� / ȸ����� / ȸ��Ż�� )
void Delivery::CustomerInterface(Customer* C) {
	system("cls");
	while (true) {		//�ݺ����� ���� �������̽� �ݺ�
		cout << endl << C->name << "��, ȯ���մϴ�." << endl;
		cout << "1.�ֹ� 2.�ܾװ��� 3.ȸ�����Ȯ�� 4.ȸ��Ż�� 5.�α׾ƿ� : ";
		in = Input();	//� �۾��� ���� �Է¹ޱ�

		if (in == 1) StoreInterface(C);		//�ֹ� �������̽��� �̵�
		else if (in == 2) MoneyInterface(C); //�� �ܾ� �������̽��� �̵�
		else if (in == 3) C->Membership();	//ȸ�� ��� Ȯ��
		else if (in == 4) {
			if (InstallerLeave(C)) break; //ȸ��Ż�� ������ �������̽� �ݺ� ����
		}
		else if (in == 5) {	//�� �������̽� ����
			cout << endl << "�ʱ�ȭ������." << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}

}

//�� �ܾװ��� �������̽� ( �ܾ�Ȯ�� / �ܾ�����/ �ܾ����� )
void Delivery::MoneyInterface(Customer* C) {
	system("cls");
	//�ݺ����� ���� �������̽� �ݺ�
	while (true) {
		cout << endl << "***�ܾװ���***" << endl;
		cout << "1.�ܾ�Ȯ��  2.����  3.����  4.�ڷΰ��� : ";
		in = Input();	//� �۾��� ���� �Է¹ޱ�

		if (in == 1) {
			cout << endl << "***�ܾ� Ȯ��***" << endl;
			C->ShowBalance();	//�ܾ� ���
		}
		else if (in == 2) {
			cout << endl << "***�ܾ� ����***" << endl;
			C->ShowBalance();	//���� �ܾ� ���
			cout << "�󸶸� �����Ͻðڽ��ϱ�? : ";
			in = Input();		//���� �ݾ� �Է�
			if (C->PlusBalance(in)) cout << "������ �Ϸ�Ǿ����ϴ�." << endl;	//�Է¹��� ���� ���� �ܾ� ����
			else cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		}
		else if (in == 3) {
			cout << endl << "***�ܾ� ����***" << endl;
			C->ShowBalance();		//���� �ܾ� ���
			cout << "���� �ݾ��� �Է����ּ��� : ";
			in = Input();			//���� �ݾ� �Է�
			C->MinusBalance(in);	//�Է¹��� ���� ���� �ܾ� ����
		}
		else if (in == 4) {			//�ܾ� �������̽� ����
			cout << endl << "����ȭ������" << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}
}

//�� �ֹ� �������̽�	( ���� ���� �� -> ��ٱ��� ���� / �ֹ��ϱ� / �����߰� )
void Delivery::StoreInterface(Customer* C) {
	system("cls");
	cout << endl << "***�ֹ�***" << endl;
	Store* S = SelectStore();	//�ֹ��� ���� ����
	if (S != NULL) {			//�ֹ��� ���� ���� ��
		while (true) {			//�ݺ����� ���� �������̽� �ݺ�
			cout << endl << "������� " << S->name << "�Դϴ�!" << endl;
			cout << "1.��ٱ���  2.�ֹ��ϱ�  3.�����߰�  4.�ڷΰ��� : ";
			in = Input();		//� �۾��� ���� �Է¹ޱ�

			if (in == 1) BasketInterface(C, S);	//��ٱ��� �������̽��� �̵�
			else if (in == 2) {					//�ֹ��ϱ� �������̽��� �̵�
				if (C->menus.size() == 0) cout << endl << "��ٱ��Ͽ� �޴��� �����ϴ�. �߰����ּ���." << endl;	//����ó�� ( ��ٱ��Ͽ� �޴��� ���� ��� )
				else OrderInterface(C, S);
			}
			else if (in == 3) {		//���� �߰�
				cout << endl << "***���� �߰�***" << endl;
				cout << "���� ���� : ";
				S->ShowCoupon();	//������ ������� ���
				cout << "�߰��Ͻ� ���� ��ȣ�� �Է����ּ���. : ";
				in = Input();		//��Ͽ��� ���� ����
				Coupon* m = selectObj<Coupon>(&S->coupons, in);
				C->AddCoupon(m);	//���� �����Կ� ���� �߰�
			}
			else if (in == 4) {		//�ֹ� �������̽� ����
				C->menus.clear();	//��ٱ��� ��� �ʱ�ȭ ( �ֹ��� �Ϸ������Ƿ� )
				cout << endl << "��ٱ��� ����� �ʱ�ȭ�Ǿ����ϴ�." << endl;
				break;
			}
			else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
		}
	}
}

//�� ��ٱ��� �������̽�	( ��ٱ��� ��� / ��ٱ��� �߰� / ��ٱ��� ���� )
void Delivery::BasketInterface(Customer* C, Store* S) {
	system("cls");
	while (true) {	//�ݺ����� ���� �������̽� �ݺ�
		cout << endl << "***��ٱ���***" << endl;
		cout << "1.��ٱ��ϸ��  2.��ٱ����߰�  3.��ٱ��ϻ���  4.�ڷΰ��� : ";
		in = Input();	//� �۾��� ���� �Է¹ޱ�

		if (in == 1) {	//��ٱ��� ��ϰ� �� �ݾ� ���
			cout << endl << "***��ٱ��� ���***" << endl;
			cout << "�� : " << C->ShowMenu() << "�� �Դϴ�." << endl;
		}
		else if (in == 2) {	//��ٱ��Ͽ� �޴� �߰�
			cout << endl << "***��ٱ��� �߰�***" << endl;
			// ������ �޴���Ͽ��� �޴� ����
			cout << "� �޴��� �߰��Ͻðڽ��ϱ�? : ";
			S->ShowMenu();
			in = Input();
			Menu* m = selectObj<Menu>(&S->menus, in);
			if (m != NULL)C->AddMenu(*m);	//���� ��ٱ��Ͽ� ������ �޴� �߰�
			else cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		}
		else if (in == 3) {	//��ٱ��Ͽ��� �޴� ����
			cout << endl << "***��ٱ��� ����***" << endl;
			cout << "���� ��ٱ��� ��� : ";
			// ���� ��ٱ��ϸ�Ͽ��� �޴� ����
			C->ShowMenu();
			cout << "�����Ͻ� �޴��� ��ȣ�� �Է��ϼ���. : ";
			in = Input();
			Menu* m = selectObj<Menu>(&C->menus, in);
			Delete<Menu>(&C->menus, m, in);	//���� ��ٱ��Ͽ� ������ �޴� ����
		}
		else if (in == 4) {	//�ֹ��������̽� ����
			cout << endl << "����ȭ������" << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}
}


//�� �ֹ��ϱ� �������̽�	( ������� / ����Ƽ�ܻ�� / �ֹ����� )
void Delivery::OrderInterface(Customer* C, Store* S) {
	system("cls");
	cout << endl << "***�ֹ�����***" << endl;
	int Deliveryprice = C->ShowMenu();		//�ֹ��ݾ� ( ���� ��ٱ��Ͽ� ����ִ� �޴��� �� �� )
	int CouponPrice = 0, totalPrice = 0;	//���� ���� �ݾ�, �ֹ��ݾ׿��� ���αݾ��� �� ���� �ֹ� �ݾ�
	int CouponIndex;	//���� �����Կ��� ����� ������ ����Ƽ���� ��ġ(�ε���)�� ������ ����
	Coupon* c = NULL;	//���� �����Կ��� ����� ����

	while (true) {
		//���� �ֹ� �ݾ� = �ֹ��ݾ� - �����ݾ�
		totalPrice = Deliveryprice - CouponPrice;
		cout << endl << "(�ֹ��ݾ� : " << Deliveryprice << "��) - (���αݾ� : " << CouponPrice << "��) ===> (�ѱݾ� : " << totalPrice << "��)" << endl;
		cout << "1.������� 2.�ֹ��ϱ� 3.�ڷΰ��� : ";
		in = Input();	//� �۾��� ���� �Է¹ޱ�

		if (in == 1) {	//���� ����
			if (c == NULL) {
				cout << endl << "***���� ���***" << endl;
				//���� �����Կ��� ���� ����
				C->ShowCoupon();
				cout << "� ������ ����Ͻðڽ��ϱ�? : ";
				CouponIndex = Input();
				c = selectObj<Coupon>(&C->coupons, CouponIndex);

				if (c == NULL) cout << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó�� ( �߸��� ���� ��ȣ�� �Է�������� )
				else if (c->storeID != S->id) {	//����ó�� ( �ٸ� ������ ���� ��ȣ�� �Է����� ��� )
					c = NULL;
					cout << "�ش� ������ ������ ��밡���մϴ�." << endl;
				}
				else if (Deliveryprice < c->MinPrice) {	//����ó�� ( �ֹ��ݾ��� �ش� ������ �ּ��ֹ��ݾ׺��� ���� ��� )
					c = NULL;
					cout << "�ֹ��ݾ��� �����մϴ�." << endl;
				}
				else {	//��� ������ �����ϸ� ��������
					CouponPrice += c->Discount;
					cout << "������ ����Ǿ����ϴ�." << endl;
				}
			}
			else cout << "�̹� ������ �����Ͽ����ϴ�." << endl;	//����ó�� ( �ϳ��� �ֹ����� �ϳ��� ������ ��� ���� )
		}
		else if (in == 2) {	//�ֹ�����
			cout << endl << "***�ֹ�***" << endl;
			cout << "�Ⱦ� ����� �������ּ��� 1. ����  2. ��� : ";
			in = Input();
			if (in == 1) {
				if (C->Ordering(totalPrice)) {	//���� �ֹ��ݾ����� ���� ����
					//������ �����ϸ�
					cout << "�ֹ��� �Ϸ�Ǿ����ϴ�." << endl;
					S->TotalOrder++;	//������ �ֹ��Ǽ� �߰�
					S->PlusBalance(Deliveryprice);	//������ ����׿� �ֹ��ݾ� �߰�
					cout << "���� �Ϸ���� �� " << DeliveryTime(S, C, in) << "�� �ɸ��ϴ�." << endl;	//��޽ð� ���

					//����� ���� ���� �����Կ� ����
					if (c != NULL) Delete<Coupon>(&C->coupons, c, CouponIndex);

					break;
				}
				else cout << endl << "�ܾ��� �����Ͽ� ������ �����Ͽ����ϴ�. " << endl;	//����ó�� ( �ܾװ� ������ ��� )
			}
			else if (in == 2) {
				if (C->Ordering(totalPrice)) {	//���� �ֹ��ݾ����� ���� ����
					//������ �����ϸ�
					cout << "�ֹ��� �Ϸ�Ǿ����ϴ�." << endl;
					S->TotalOrder++;	//������ �ֹ��Ǽ� �߰�
					S->PlusBalance(Deliveryprice);	//������ ����׿� �ֹ��ݾ� �߰�
					cout << "��� �Ϸ���� �� " << DeliveryTime(S, C, in) << "�� �ɸ��ϴ�." << endl;	//��޽ð� ���

					//����� ���� ���� �����Կ� ����
					if (c != NULL) Delete<Coupon>(&C->coupons, c, CouponIndex);

					break;
				}
				else cout << endl << "�ܾ��� �����Ͽ� ������ �����Ͽ����ϴ�. " << endl;	//����ó�� ( �ܾװ� ������ ��� )
			}
			else cout << endl << "�ֹ����" << endl;
		}
		else if (in == 3) {	//�ڷΰ���
			cout << endl << "����ȭ������" << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}
}

//���Է� �α��������� ���Ǵ� �������̽� ( �޴����� / �޴����γ������ / ������� / �������� / �ֹ�Ȯ�� /ȸ��Ż�� )
void Delivery::ManagerInterface(Store* S) {
	system("cls");
	while (true) { //�ݺ����� ���� �������̽� �ݺ�
		cout << endl << S->name << "�� ȯ���մϴ�." << endl;
		cout << "1.�޴�����  2.�޴����γ������  3.�����������  4.�������� 5.�ֹ�Ȯ�� 6.ȸ��Ż�� 7.�α׾ƿ� : ";
		in = Input();

		if (in == 1) MenuInterface(S);	//�޴����� �������̽��� �̵�
		else if (in == 2) {
			cout << endl << "���� �޴� : ";
			S->ShowMenu();	//�޴���� ���
			cout << "� �޴��� ���γ����� �����Ͻðڽ��ϱ�? : ";
			in = Input();	//�޴� ����
			Menu* m = selectObj<Menu>(&S->menus, in);
			DetailInterface(m);	//�޴����γ���Ȯ��
		}
		else if (in == 3) DeliveryAreaInterface(S);	//����������� �������̽��� �̵�
		else if (in == 4) CouponInterface(S);	//�������� �������̽��� �̵�
		else if (in == 5) {	//������ �ֹ��Ǽ��� ���� Ȯ��
			cout << endl << "***�ֹ�Ȯ��***" << endl;
			S->ShowTotalOrder();
		}
		else if (in == 6) {	//ȸ��Ż��
			if (InstallerLeave(S)) break; //ȸ��Ż�� ���������� �������̽� ����
		}
		else if (in == 7) {	//���� �������̽� ����
			cout << endl << "�α׾ƿ� ó���Ǿ����ϴ�." << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}

}

//���� �޴����� �������̽� ( �޴���� / �޴��߰� / �޴����� )
void Delivery::MenuInterface(Store* S) {
	system("cls");
	while (true) { //�ݺ����� ���� �������̽� �ݺ�
		cout << endl << "***�޴�����***" << endl;
		cout << "1.�޴����  2.�޴��߰�  3.�޴�����  4.�ڷΰ��� : ";
		in = Input(); //� �۾��� ���� �Է¹ޱ�

		if (in == 1) {	//�޴���� ���
			cout << endl << "***����޴����***" << endl;
			S->ShowMenu();
		}
		else if (in == 2) {	//�޴��߰�
			cout << endl << "***�޴��߰�***" << endl;
			S->AddMenu();
		}
		else if (in == 3) {	//�޴�����
			cout << endl << "***�޴�����***" << endl;
			//������ �޴���Ͽ��� ������ �޴� ����
			cout << "���� �޴� ��� : ";
			S->ShowMenu();
			cout << "�����Ͻ� �޴� ��ȣ�� �Է��ϼ���. : ";
			in = Input();

			Menu* m = selectObj<Menu>(&S->menus, in);
			Delete<Menu>(&S->menus, m, in);	//������ �޴���Ͽ��� ������ �޴� ����
		}
		else if (in == 4) {	//�޴����� �������̽� ����
			cout << endl << "����ȭ������" << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}
}

//���� �޴����γ������ �������̽� ( �޴����γ����� / �޴����γ����߰� / �޴����γ������ )
void Delivery::DetailInterface(Menu* M) {
	system("cls");
	while (M != NULL) {	//�ݺ����� ���� �������̽� �ݺ�
		cout << endl << "***" << M->name << "�� ���γ������***" << endl;
		cout << "1.���γ�����  2.���γ����߰�  3.���γ������  4.�ڷΰ��� : ";
		in = Input();	//� �۾��� ���� �Է¹ޱ�

		if (in == 1) {	//�޴����γ����� ���
			cout << endl << "***���γ��� ���***" << endl;
			M->DetailList();
		}
		else if (in == 2) {	//�޴����γ��� �߰�
			cout << endl << "***���γ��� �߰�***" << endl;
			M->AddDetail();
		}
		else if (in == 3) {	//�޴����γ��� ����
			cout << endl << "***���γ��� ����***" << endl;
			//�޴��� �޴����γ����Ͽ��� ������ �޴����γ��� ����
			cout << "���� ���γ��� : ";
			M->DetailList();
			cout << "�����Ͻ� ���λ����� �Է��ϼ���. : ";
			in = Input();

			Detail* d = selectObj<Detail>(&M->details, in);
			Delete<Detail>(&M->details, d, in);	//�޴��� �޴����γ����Ͽ��� ������ �޴����γ��� ����
		}
		else if (in == 4) {	//�޴����γ��� �������̽� ����
			cout << endl << "����ȭ������" << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}
}

//���� ����������� �������̽� ( ���������� / ��������߰� / ����������� )
void Delivery::DeliveryAreaInterface(Store* S) {
	system("cls");
	while (true) {	//�ݺ����� ���� �������̽� �ݺ�
		cout << endl << "***�����������***" << endl;
		cout << "1.����������  2.��������߰�  3.�����������  4.�ڷΰ��� : ";
		in = Input();	//� �۾��� ���� �Է¹ޱ�

		if (in == 1) {	//���������ϰ� ��޽ð���� ���
			cout << endl << "***������� ���***" << endl;
			S->ShowDeliveryArea();
		}
		else if (in == 2) { //��������� ��޽ð� �߰�
			cout << endl << "***������� �߰�***" << endl;
			S->AddDeliveryArea();
		}
		else if (in == 3) {
			cout << endl << "***������� ����***" << endl;
			//������ ���������ϰ� ��޽ð���Ͽ��� ������ ��������� ��޽ð� ����
			cout << "���� ��� ���� ���� : ";
			S->ShowDeliveryArea();
			cout << "�����Ͻ� ������ �Է����ּ���. : ";
			in = Input();

			string* Area = selectObj<string>(&S->DeliveryArea, in);
			int* time = selectObj<int>(&S->DeliveryTime, in);
			//������ ��������� ��޽ð� ����
			Delete<string>(&S->DeliveryArea, Area, in);
			Delete<int>(&S->DeliveryTime, time, in);
		}
		else if (in == 4) {	//����������� �������̽� ����
			cout << endl << "����ȭ������" << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}
}

//���� �������� �������̽� ( ������� / �����߰� / �������� )
void Delivery::CouponInterface(Store* S) {
	system("cls");
	while (true) {	//�ݺ����� ���� �������̽� �ݺ�
		cout << endl << "***��������***" << endl;
		cout << "1.�������  2.�����߰�  3.��������  4.�ڷΰ��� : ";
		in = Input();	//� �۾��� ���� �Է¹ޱ�

		if (in == 1) {	//������� ���
			cout << endl << "***���� ���***" << endl;
			S->ShowCoupon();
		}
		else if (in == 2) {	//���� �߰�
			cout << endl << "***���� �߰�***" << endl;
			S->AddCoupon();
		}
		else if (in == 3) {	//���� ����
			cout << endl << "***���� ����***" << endl;
			//������ ������Ͽ��� ������ ���� ����
			cout << "���� ���� : ";
			S->ShowCoupon();
			cout << "�����Ͻ� ���� ��ȣ�� �Է����ּ���. : ";
			in = Input();

			Coupon* c = selectObj<Coupon>(&S->coupons, in);
			Delete<Coupon>(&S->coupons, c, in);	//������ ���� ����
		}
		else if (in == 4) {	//�������� �������̽� ����
			cout << endl << "����ȭ������" << endl;
			break;
		}
		else cout << endl << "�߸� �Է��ϼ̽��ϴ�." << endl;	//����ó��
	}
}