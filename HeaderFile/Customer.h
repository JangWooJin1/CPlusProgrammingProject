#ifndef CUSTOMER_H
#define CUSTOMER_H
#include"Installer.h"

class Customer : public Installer{
public:
	int Level;							//ȸ�����
	int Accumulated;					//�����ֹ��ݾ�

	Customer(string name, string phoneNum, string Area, string id, string password);

	void Membership();					//���� ȸ����ް� ������ ���
	int Benefits(int price);			//���� ���ÿ� �´� �������� ���� �� ��ȯ ( ����Ƽ�� ���ų� �ֹ��� ��� )
	bool LevelUp();						//���� ȸ������� ��� ( ����Ƽ�� ���ų� �ֹ��� ��� )
	void AddMenu(Menu m);				//���� ��ٱ���(menus)�� �޴��� �߰�
	void AddCoupon(Coupon* c);			//���� ������(copons)�� ������ �߰�
	bool Ordering(int price);			//���� ����

	void dump() {} //���� �����Լ��� ��������� ����
};
#endif