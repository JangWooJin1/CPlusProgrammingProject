#include"Coupon.h"

//���� ��ü ���� ( ������ ) - ���αݾ�, �ּ��ֹ��ݾ�, �����̸�, ����ID
Coupon::Coupon(int Discount, int Minprice, string storeName, string storeID) {
	this->Discount = Discount;
	this->MinPrice = Minprice;
	this->storeName = storeName;
	this-> storeID = storeID;
}

//customerIDs�� ���� ���̵� �����ϴ��� �ľ�
int Coupon::FindCustomerID(string customerid) {
	int i = 0;	//�ݺ��� ���� ����
	for (; i < customerIDs.size(); i++) {
		//�Ű������� id�� ���� ��ġ�ڰ� �ִٸ� �ݺ��� ����
		if (customerIDs[i] == customerid) break;
	}
	//��ġ�ڰ� �ִٸ� i���� installersũ�⺸�� �۰�, ��ġ�ڰ� ���ٸ� i == installers.size()�� �ȴ�.

	//�ݺ��� ���� ��ȯ
	return i;
}