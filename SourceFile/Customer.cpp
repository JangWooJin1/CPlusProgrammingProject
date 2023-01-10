#include"Customer.h"

//�� ��ü ���� ( ������ )
Customer::Customer(string name, string phoneNum, string Area, string id, string password) : Installer(name,phoneNum,Area,id,password,0) {
	Level = 0;	//ȸ����� 0���� �ʱ�ȭ
	Accumulated = 0;	//�����ֹ��ݾ� 0���� �ʱ�ȭ
}

//���� ȸ����ް� ������ ���
void Customer::Membership() {
	cout << endl << "***ȸ�����Ȯ��***" << endl;
	cout << "ȸ������ ����� ���� " << Level << "�Դϴ�." << endl;
	if (Level == 0) {
		cout << "���� ��޿��� ������ �����ϴ�." << endl;
		cout << "���� ��ޱ��� " << 10000 - Accumulated << "�� ���ҽ��ϴ�." << endl;
	}
	else if (Level == 1) {
		cout << "���� ��޿��� ������ 1% ����" << endl;
		cout << "���� ��ޱ��� " << 50000 - Accumulated << "�� ���ҽ��ϴ�." << endl;
	}
	else if (Level == 2) {
		cout << "���� ��޿��� ������ 3% ����" << endl;
		cout << "���� ��ޱ��� " << 100000 - Accumulated << "�� ���ҽ��ϴ�." << endl;
	}
	else if (Level == 3) {
		cout << "���� ��޿��� ������ 5% ����" << endl;
	}
}

//���� ���ÿ� �´� �������� ���� �� ��ȯ ( ����Ƽ�� ���ų� �ֹ��� ��� )
int Customer::Benefits(int price) {
	int Benefit = 0;
	if (Level == 0) Benefit+=0;
	else if (Level == 1) Benefit += int(price * 0.01);
	else if (Level == 2) Benefit += int(price * 0.03);
	else if (Level == 3) Benefit += int(price * 0.05);
	return Benefit;
}

//���� ȸ������� ��� ( ����Ƽ�� ���ų� �ֹ��� ��� )
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
	//ȸ������� ����Ͽ��ٸ� true, �ƴ϶�� false��ȯ
	return false;
}

//���� ��ٱ���(menus)�� �޴��� �߰�
void Customer::AddMenu(Menu m) {
	//��ٱ��Ͽ� �߰��ϱ� ���� ���λ����� üũ
	cout << m.name << "�� ���λ����� üũ���ּ���." << endl;
	m.SetDetail();

	//���λ��� üũ�� �Ϸ�Ǿ��ٸ� ��ٱ��Ͽ� �޴� �߰�
	menus.push_back(m);
	cout << "��ٱ��Ͽ� " << m.name << "��(��) �߰��Ǿ����ϴ�." << endl;
	
}

//���� ������(copons)�� ������ �߰�
void Customer::AddCoupon(Coupon* c) {
	if (c != NULL) { 
		//���� �ߺ� �߱� ������ ���� ���� ���̵� ������ Ȯ��
		int i = c->FindCustomerID(this->id);

		if (i == c->customerIDs.size()) {	
			coupons.push_back(*c);	//��� ������ �����Ѵٸ� ���� �����Կ� �߰�
			c->customerIDs.push_back(this->id);	//�ߺ� �߱� ������ ���� ������ �� ���̵� ����
			cout << "������ �߰��Ǿ����ϴ�." << endl;
		}
		// ����ó�� ( �̹� �߱޹��� ������ ��� )
		else cout << "�̹� �߱޹��� �����Դϴ�." << endl;
	}
	// ����ó�� ( �߸��� ���� ��ȣ�� �Է����� ��� )
	else cout << "�ش��ϴ� ������ �����ϴ�." << endl;
}

//���� ����
bool Customer::Ordering(int price) {
	//������ �Ϸ�Ǹ� true, �����ϸ� false�� ��ȯ
	if (Balance >= price) {
		Accumulated += price;	//�����ֹ��ݾ� ����
		Balance -= price;		//���� �ܾ� ����
		cout << "����������� " << Benefits(price) << "�� �����Ǿ����ϴ�." << endl;	//������ ȸ����޿� ���� ������ ó��
		if (LevelUp()) cout << "����� ������ " << Level << "�� �ö����ϴ�!" << endl;	//�����ֹ��ݾ׿� ���� ȸ����� ����� �߻��ߴ��� �ľ�
		return true;
	}
	//����ó�� ( �ܾװ� ������ ��� )
	else return false;
}