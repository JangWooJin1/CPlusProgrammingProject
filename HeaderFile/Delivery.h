#ifndef DELIVERY_H
#define DELIVERY_H
#include"Store.h"
#include"Customer.h"
#include<typeinfo>
#include<fstream>
#include<windows.h>

class Delivery {
private:
	vector<Installer*> installers;								//��ġ��(��, ����)�� �����ϴ� �迭 ( �����Ҵ� ��� )
	int in;												//� ������ ���� �����ϴ� ����
public:
	Delivery();									//�����Ҵ� �迭 installers ���� �������ִ� �Ҹ���
	~Delivery();									//�����Ҵ� �迭 installers ���� �������ִ� �Ҹ���

	int Input();										//�Է¿���ó���Լ� ( ���� �ڷ����� ���ڰ��� �־��� ��)

	//�迭���� i-1��° �ε����� �ִ� ��ü�� ��ȯ���ִ� ���ø� �Լ� ( Installer::menus, Installer::coupons, Installer::gifticons,Store::DeliveryArea, Store::DeliveryTime, Menu::details �� ���)
	template<class T>
	T* selectObj(vector<T>* list, int i);		

	//�迭���� i-1��° �ε����� �ִ� ��ü�� �������ִ� ���ø� �Լ� ( Installer::menus, Installer::coupons, Installer::gifticons,Store::DeliveryArea, Store::DeliveryTime, Menu::details�� ���) 
	template<class K>
	bool Delete(vector<K>* list, K* tmp, int index);	

	int FindInstallerID(string id);							//��ġ�� ���̵� ���� installers���� ��ġ(�ε���)�� ã�� ��ȯ
	void InstallerJoin();									//installers�� ��ġ�� �߰�(ȸ������)
	bool InstallerLeave(Installer* IT);							//installers���� ��ġ�� ����(ȸ��Ż��)
	Installer* InstallerLogin();									//��ġ�� ���̵�� ��й�ȣ�� ���� installers���� �ش��ϴ� �� ��ȯ( �α��� )
	Store* SelectStore();							//���� ���ϴ� ���Ը� �����ϸ� �� ���Ը� ��ȯ ( �ֹ�, ����Ƽ�� �����Ҷ� ��� )
	int DeliveryTime(Store* S, Customer* C, int i);			//���� ������ ������ ������ ���� ��޽ð��� ��ȯ	( �ֹ��Ҷ� ��� )

	void StartInterface();								//ȸ������, �α��� �������̽�

	void CustomerInterface(Customer* C);						//������ �α��������� ���Ǵ� �������̽� ( �ֹ� / �����ϱ� / �ܾװ��� / ȸ����� / ȸ��Ż�� )
	void MoneyInterface(Customer* C);						//�� �ܾװ��� �������̽� ( �ܾ�Ȯ��/ �ܾ�����/ �ܾ����� )
	void StoreInterface(Customer* C);						//�� �ֹ� �������̽�	( ���� ���� �� => ��ٱ��� ���� / �ֹ��ϱ� / �����߰� )
	void BasketInterface(Customer* C, Store* S);		//�� ��ٱ��� �������̽�	( ��ٱ��ϸ�� / ��ٱ����߰� / ��ٱ������� )
	void OrderInterface(Customer* C, Store* S);		//�� �ֹ��ϱ� �������̽�	( ������� / ����Ƽ�ܻ�� / �ֹ����� )

	void ManagerInterface(Store* S);					//���Է� �α��������� ���Ǵ� �������̽� ( �޴����� / �޴����γ������ / ������� / �������� / ����Ƽ�ܰ��� / �ֹ�Ȯ�� /ȸ��Ż�� )
	void MenuInterface(Store* S);					//���� �޴����� �������̽� ( �޴���� / �޴��߰� / �޴����� )
	void DetailInterface(Menu* M);					//���� �޴����γ������ �������̽� ( �޴����γ����� / �޴����γ����߰� / �޴����γ������ )
	void DeliveryAreaInterface(Store* S);			//���� ����������� �������̽� ( ���������� / ��������߰� / ����������� )
	void CouponInterface(Store* S);				//���� �������� �������̽� ( ������� / �����߰� / �������� )
};

#endif