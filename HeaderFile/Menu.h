#ifndef MENU_H
#define MENU_H
#include"Detail.h"

class Menu {
public:
	string name;				//�޴� �̸�
	int price;					//�޴� ����
	int cooktime;				//���� �ð�
	vector<Detail> details;		//�޴��� ���γ���

	Menu(string name, int price, int cooktime);  //�޴� ��ü���� ( ���԰� �޴��� �߰��� �� )
	void DetailList();							 //�޴� ���γ��� ���
	void AddDetail();							 //�޴� ���γ��� �߰� ( ���԰� ���γ����� �߰��� �� )
	void SetDetail();							 //�޴� ���γ��� ���� ( ���� �ֹ��� �� ��� )
};

#endif
