#include"Detail.h"
//���λ��� ��ü ���� (������)-����, ����, ���뿩�� ����
Detail::Detail(string content, int price, bool YN) {
	this->content = content;
	this->price = price;
	this->YN = YN;
}

//���λ������뿩��(YN)�� �� ����
void Detail::SelectYN() {
	string select;	//YN�� ���� �ӽ� �����ϴ� ����
	//���� ���������� ����Ҷ����� �ݺ�
	while (true) {
		cout << content << "(" << price << "��) (Y or N) : "; //���λ��� �ȳ� �� ���� ���� ����
		cin >> select;	
		if (select == "Y" || select == "y") {	//���� 'Y' / 'y'�߿��� ����� ���
			YN = true;	//���λ��� ����
			break;
		}
		else if (select == "N" || select == "n") { //���� 'N' / 'n' �߿��� ����� ���
			YN = false; //���λ��� �������� ����
			break;
		}
		else cout << "�߸� �Է��ϼ̽��ϴ�." << endl;	//�� ���� ���
	}
}
