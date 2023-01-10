#ifndef STORE_H
#define STORE_H
#include"Installer.h"

class Store : public Installer{
public:
	int TotalOrder;						//���� �� �ֹ��Ǽ�
	vector<string> DeliveryArea;		//��� ���� �����̸��� �����ϴ� �迭
	vector<int> DeliveryTime;			//��� �ð��� �����ϴ� �迭

	Store(string name, string phoneNum, string Area, string id, string passowrd);

	void AddMenu();						//���� �޴���(menus)�� �޴��߰�
	void AddCoupon();					//���� ������(coupons)�� �����߰�
	void AddDeliveryArea();				//���� ��ް�����������Ʈ(DeliveryArea, DeliveryTime)�� ��ް��������� ��޽ð� �߰�
	void ShowDeliveryArea();			//���� ��ް��������� ��޽ð��� ���
	void ShowTotalOrder();				//���� �� �ֹ��Ǽ��� ������ ���

	void dump() {} //���� �����Լ��� ��������� ����
};
#endif