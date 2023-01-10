#include"Store.h"

//���� ��ü ���� ( ������ )
Store::Store(string name, string phoneNum, string Area, string id, string password) : Installer(name, phoneNum, Area, id, password,0) {
	this->TotalOrder = 0;	//���� �� �ֹ��Ǽ� 0���� �ʱ�ȭ
}

//���� �޴���(menus)�� �޴��߰�
void Store::AddMenu() {
	string name;	//�޴��̸�
	int price,cooktime;	//�޴� ���ݰ� �����ð�
	cout << "�޴��̸��� ����, �����ð�(��)�� �Է��ϼ���. : ";
	cin >> name >> price >> cooktime;
	
	if (price < 0) {//����ó�� ( ������ �����϶� )
		cout << "������ �߸� �Է��ϼ̽��ϴ�." << endl;
		return;
	}
	if (cooktime < 0) { //����ó�� ( �����ð��� �����϶� )
		cout << "�����ð��� �߸� �Է��ϼ̽��ϴ�." << endl;
		return;
	}

	//�޴� ��ü ������ menus�� �߰�
	menus.push_back(Menu(name, price, cooktime));
	cout << "�޴��� �߰��Ǿ����ϴ�." << endl;
}

//���� ������(conpos)�� �����߰�
void Store::AddCoupon() {
	ShowCoupon();
	int Discount, MinPrice;
	cout << "���αݾװ� �ּ��ֹ��ݾ��� �����ϼ���. : ";
	cin >> Discount >> MinPrice;

	if (Discount <= 0) { //����ó�� ( ���αݾ��� �����ΰ�� )
		cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		return;
	}
	if (MinPrice <= Discount) { //����ó�� ( �ּ��ֹ��ݾ��� ���αݾ׺��� ������� )
		cout << "�ּ��ֹ��ݾ��� ���αݾ׺��� ���� �� �����ϴ�." << endl;
		return;
	}

	//���� ��ü ���� �� coupons�� ��ü �߰�
	coupons.push_back(Coupon(Discount, MinPrice, this->name, this->id));
	cout << "������ �߰��Ǿ����ϴ�." << endl;
}

//���� ��ް�����������Ʈ(DeliveryArea, DeliveryTime)�� ��ް��������� ��޽ð� �߰�
void Store::AddDeliveryArea() {
	cout << "���� ���� : ";
	ShowDeliveryArea();
	string Area;	//��� ����
	int cooktime;	//��� �ð�
	cout << "�߰��Ͻ� ������ ��޽ð��� �Է����ּ���. : ";
	cin >> Area >> cooktime;

	if (cooktime > 0) {	//����ó�� ( ��޽ð��� ������ ��� )
		DeliveryArea.push_back(Area);	//DeliveryArea�� ������� �߰�
		DeliveryTime.push_back(cooktime);	//DeliveryTime�� ��޽ð� �߰�
		cout << "������ �߰��Ǿ����ϴ�." << endl;
	}
	else cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
}

//���� ��ް��������� ��޽ð��� ���
void Store::ShowDeliveryArea() {
	for (int i = 0; i < DeliveryArea.size(); i++) {
		cout << i + 1 << ". " << DeliveryArea[i] << "(" << DeliveryTime[i] << "��) ";
	}
	cout << endl;
}

//���� �� �ֹ��Ǽ��� ������ ���
void Store::ShowTotalOrder() {
	cout << "�� " << TotalOrder << "���� �ֹ��� ���԰�, ��������� ������ " << Balance << "�� �Դϴ�." << endl;
}




