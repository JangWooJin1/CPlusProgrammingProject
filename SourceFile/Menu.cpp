#include"Menu.h"
//�޴� ��ü ���� (������)-�޴��̸�, ����, �����ð� ����
Menu::Menu(string name, int price, int cooktime) {
	this->name = name;
	this->price = price;
	this->cooktime = cooktime;
}

//details�� ����� ��� ���γ������
void Menu::DetailList() {
	//details�� ũ�� ��ŭ �ݺ�
	for (int i = 0; i < details.size(); i++) {
		//���λ����� ����� ������ ���
		cout << i + 1 << ". " << details[i].content << " (" << details[i].price << "��) ";
	}
	cout << endl;
}

//details�� ���λ��� �߰�
void Menu::AddDetail() {
	string content;
	int price;
	cout << "���� ���λ��� : ";	//��������� ���� ���� ���
	DetailList();
	cout << "�߰��� ���λ����� �Է��ϼ��� ( ����, ���� ) : ";	//�Է� �ȳ���
	cin >> content >> price;

	if (price < 0) {	//����ó�� ( ������ ������ ��� )
		cout << "������ �߸� �Է��Ͽ����ϴ�." << endl;	//���� �ȳ���
		return;
	}

	//vector�� push_back�Լ��� �̿��Ͽ� �迭�� ��ü �߰�
	details.push_back(Detail(content, price, false));
	cout << "�޴��� ���γ����� �߰��Ǿ����ϴ�." << endl;
}

//details�� ����� ��� ���λ��� ���뿩�� ����
void Menu::SetDetail() {
	for (int i = 0; i < details.size(); i++) {//��� ���� ���뿡 ����
		details[i].SelectYN();	//���� 'y �Ǵ� n'�� ��� ���θ� ����
	}
}