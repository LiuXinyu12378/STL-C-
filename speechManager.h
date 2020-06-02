#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
using namespace std;

class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//�ɵ�����
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	void initSpeech();

	//����12��ѡ��
	void createSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾѡ����Ϣ
	void showScore();

	//����������ļ�
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��ӡ�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//��Ա����
	//�����һ�ֱ���ѡ�ֱ������
	vector<int>v1;

	//�����һ�ֽ���ѡ�ֱ������
	vector<int>v2;

	//ʤ��ǰ����ѡ�ֱ������
	vector<int>vVictory;

	//��������¼������
	map<int, vector<string>>m_Record;

	//���ѡ�ֱ�ż���Ӧ����ѡ������
	map<int, Speaker>m_Speaker;

	//��ű�������
	int m_Index;

	//��������
	~SpeechManager();
};