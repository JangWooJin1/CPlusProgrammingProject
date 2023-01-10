#include"Installer.h"

//��ġ�� ��ü�� ���� ( ������ )
Installer::Installer(string name, string phoneNum, string Area, string id, string password, int Balance) {
	this->name = name;
	this->phoneNum = phoneNum;
	this->Area = Area;
	this->id = id;
	this->password = password;
	this->Balance = Balance;
}

//��ġ���� �ܾ׸� ���
void Installer::ShowBalance() {
	cout << "���� �ܾ� : " << Balance << "��" << endl;
}

//��ġ���� �ܾ׿� �Ա�
bool Installer::PlusBalance(int price) {
	if (price > 0) {	//����ó�� ( �Ա��Ϸ��� �ݾ��� ������ �� ) 
		Balance += price;
		return true;
	}
	else return false;
}

//��ġ���� �ܾ׿��� ����
void Installer::MinusBalance(int price) {
	if (price > 0) {	//����ó�� ( �����Ϸ��� �ݾ��� ������ �� )
		if (Balance >= price) {	//����ó�� ( �ܾװ� �����Ұ�� )
			Balance -= price;
			cout << "���� �Ϸ�." << endl;
		}
		else cout << "�ܾ��� �����մϴ�." << endl;
	}
	else cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
}

//menus�� ����Ǿ��ִ� �޴��� ��� �� �� �ݾ��� ��ȯ
int Installer::ShowMenu() {
	int totalprice = 0;	//��� �޴��� ������ �����ϴ� ����
	int price;	//�ϳ��� �޴��� ������ �����ϴ� ����
	//ù��° �ݺ����� ���� �޴� ���� price�� �ֱ�
	for (int i = 0; i < menus.size(); i++) {
		price = menus[i].price;
		//�ι�° �ݺ����� ���� ���λ��� ���� �ݾ� price�� �߰�
		for (int j = 0; j < menus[i].details.size(); j++) {
			if (menus[i].details[j].YN == true) 	price += menus[i].details[j].price;
		}
		totalprice += price;	//�� �޴��� �ݾ��� �Ѿ׿� �߰�
		cout << i + 1 << ". " << menus[i].name << " (" << price << "��) ";
	}
	cout << endl;
	//�� �ݾ� ��ȯ
	return totalprice;
}

//coupons�� ����Ǿ��ִ� ���� ���� ���
void Installer::ShowCoupon() {
	cout << "���� ���� ��� : ";

	for (int i = 0; i < coupons.size(); i++) {
		cout << i+1 <<". " << coupons[i].storeName << "�� " << coupons[i].Discount << "�� �������� ( �ּ��ֹ��ݾ� : " << coupons[i].MinPrice << " ) ";
	}
	cout << endl;
}


