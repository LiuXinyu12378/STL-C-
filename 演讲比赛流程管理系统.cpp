#include"speechManager.h"
#include<iostream>
#include<ctime>
using namespace std;


int main()
{
	//创建管理类对象
	SpeechManager sm;
	srand((unsigned int)time(NULL));

	int choice = 0;
	while (true)
	{
		sm.show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:   //开始比赛
			sm.startSpeech();
			break;
		case 2:   //查看往届比赛记录
			sm.loadRecord();
			sm.showRecord();
			break;
		case 3:   //清空退出比赛
			sm.clearRecord();
			break;
		case 0:   //退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}