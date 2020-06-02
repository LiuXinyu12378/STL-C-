#include "speechManager.h"
#include<string>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>

//���캯��
SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
}

//�ɵ�չʾ
void SpeechManager::show_Menu()
{
	cout << "****************************************************" << endl;
	cout << "************* ��ӭ�μ��ݽ����� *********************" << endl;
	cout << "************* 1.��ʼ�ݽ����� ***********************" << endl;
	cout << "************* 2.�鿴�����¼ ***********************" << endl;
	cout << "************* 3.��ձ�����¼ ***********************" << endl;
	cout << "************* 0.�˳�����ϵͳ ***********************" << endl;
	cout << "****************************************************" << endl;
	cout << endl;
}

void SpeechManager::createSpeaker()
{
	string SpeakerSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < SpeakerSeed.size(); i++)
	{
		string name = "ѡ��";
		name += SpeakerSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0.0;
		}

		//����ѡ�ֱ�� ���ҷ��뵽v1������
		this->v1.push_back(i + 10001);

		//ѡ�ֱ���Լ���Ӧѡ�� ���뵽map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ʼ����
void SpeechManager::startSpeech()
{
	//��һ�ֱ���

	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();
	//�ڶ��ֱ�����ʼ
	this->m_Index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->showScore();
	//�����ļ�����
	this->saveRecord();

	//���ñ�������ȡ��¼
	//��ʼ������������
	this->initSpeech();
	//����12��ѡ��
	this->createSpeaker();
	//���������¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "�ڡ�" << this->m_Index << "���ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "----------------------" << endl;

	if (this->m_Index == 1)
	{
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;
	system("pause");
	cout << endl;
}

//����
void SpeechManager::speechContest()
{
	cout << "----------------��" << this->m_Index << "�ֱ�����ʽ��ʼ----------------" << endl;

	//׼����ʱ������ ���С��ɼ�
	multimap<double, int, greater<double>> groupScore;

	int num = 0;  //��¼��Ա���� 6��һ��

	vector<int>v_Src;  //����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		deque<double>d;

		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());

		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;//��������� ���뵽��ʱС��������

		groupScore.insert(make_pair(avg, *it));  //key�ǵ÷֣�value�Ǿ���ѡ�ֱ��

		//ÿ6��ȡ��ǰ3��
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name << " �ɼ�" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			
			int cout = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&cout<3; it++,cout++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear();//С���������

		}
	}
	cout << "--------------------��" << this->m_Index << "�ֱ�����ϣ�--------------------" << endl;
	system("pause");
}

//��ʾ�÷�
void SpeechManager::showScore()
{
	cout << "-----------------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�---------------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << "������" << this->m_Speaker[*it].m_Name << " �÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	system("pause");
	system("cls");
	this->show_Menu();
}

//�������ݵ��ļ�
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //׷�ӵķ�ʽд�ļ�

	//��ÿ��ѡ������ д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it <<","<<this->m_Speaker[*it].m_Name<< "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;

	//�м�¼�ˣ��ļ���Ϊ����
	this->fileIsEmpty = false;
}

void SpeechManager::initSpeech()
{
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;
	this->m_Record.clear();
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//���ļ�
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//�ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof())    //
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch);// �������ȡ�ĵ����ַ� �Ż���
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;//�鵽������λ�õı���
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
			//û���ҵ�
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

}

//��ʾ�����¼
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		{
			cout << "��" << it->first << "�� " << " �ھ���ţ�" << it->second[0] << " �ھ�������" << it->second[1] << " �ھ�������" << it->second[2] <<
				" �Ǿ���ţ�" << it->second[3] << " �Ǿ�������" << it->second[4] << " �Ǿ�������" << it->second[5] <<
				" ������ţ�" << it->second[6] << " ����������" << it->second[7] << " ����������" << it->second[8] << endl;
		}
	}
	system("pause");
	system("cls");
}

//��ձ�����¼
void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ���" << endl;
	cout << "1.��" << endl;
	cout << "2.��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//ȷ�����
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeech();

		//����12��ѡ��
		this->createSpeaker();

		//���������¼
		this->loadRecord();

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

//��������
SpeechManager::~SpeechManager()
{

}