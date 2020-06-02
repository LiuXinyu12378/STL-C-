#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
using namespace std;

class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//采单功能
	void show_Menu();

	//退出系统
	void exitSystem();

	void initSpeech();

	//创建12名选手
	void createSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示选手信息
	void showScore();

	//保存分数到文件
	void saveRecord();

	//读取记录
	void loadRecord();

	//判断文件是否为空
	bool fileIsEmpty;

	//打印往届记录
	void showRecord();

	//清空记录
	void clearRecord();

	//成员属性
	//保存第一轮比赛选手编号容器
	vector<int>v1;

	//保存第一轮晋级选手编号容器
	vector<int>v2;

	//胜出前三名选手编号容器
	vector<int>vVictory;

	//存放往届记录的容器
	map<int, vector<string>>m_Record;

	//存放选手编号及对应具体选手容器
	map<int, Speaker>m_Speaker;

	//存放比赛轮数
	int m_Index;

	//析构函数
	~SpeechManager();
};