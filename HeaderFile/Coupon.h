#ifndef COUPON_H
#define COUPON_H
#include"Detail.h"

class Coupon {
public:
	int Discount;							//���� ���αݾ�
	int MinPrice;							//���� ����� ���� �ּ� �ֹ��ݾ�
	string storeName;						//���� ����� ������ �����̸�
	string storeID;							//���� ����� ������ ���Ծ��̵�
	vector<string> customerIDs;				//������ �߱޹��� ���� ���̵� �����ϴ� �迭	( ���� �ߺ� �߱� ������ ���� ��� )

	Coupon(int Discount, int Minprice, string storeName, string storeID);
	int FindCustomerID(string customerid);		//customerIDs�� ���� ���̵� �������� �ľ� ( ���� �ߺ� �߱� ������ ���� ��� )
};
#endif