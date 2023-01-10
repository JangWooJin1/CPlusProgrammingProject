#ifndef INSTALLER_H
#define INSTALLER_H
#include"Menu.h"
#include"Coupon.h"
//#include"Gifticon.h"

class Installer {
public:
	string name, phoneNum, Area, id, password;													//��ġ�� ���� ( �̸�, ��ȭ��ȣ, ����, ���̵�, ��й�ȣ )
	int Balance;																				//��ġ���� �ܾ� ( ���Դ� ����, ���� �ܾ׷� �̿� )
	vector<Menu> menus;																			//��ġ���� �޴��� �����ϴ� �迭 ( ���Դ� �޴�, ���� ��ٱ��Ϸ� �̿� )
	vector<Coupon> coupons;																		//��ġ���� ������ �����ϴ� �迭

	Installer(string name, string phoneNum, string Area, string id, string password, int Balance);	//��ġ�� ��ü����
	void ShowBalance();																			//��ġ���� �ܾ׸� ���
	bool PlusBalance(int price);																	//��ġ���� �ܾ׿� price��ŭ �Ա�
	void MinusBalance(int price);																//��ġ���� �ܾ׿��� price��ŭ ����

	int ShowMenu();																				//menus�� ����� �޴��� ���
	void ShowCoupon();																			//coupons�� ����� ������ ���	
	virtual void dump() = 0;
};


#endif

