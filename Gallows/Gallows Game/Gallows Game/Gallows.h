#pragma once

using namespace std;

class Gallows
{
	enum {EASY = 1 , NORMAL = 2 , HARD = 3, MAX_MISTAKES = 6 };
	string path = "GallowsGame.txt"; // �������� ����� �� ������� ����
	char word[15]; // ���������� ��� ������ ���������� �����
	char copy_word[30]; // ����� ����� ��� ������ ���� "_"
	int length_word; // ����� ����������� �����
	char user_tryes[25]; // ������ ������� ������������
	int lenght_user_tryes; // ���������� �������
	int guessedNumbers; // ����������� �������� ����

	char hint_first, hint_second;

public:
	Gallows(); // �����������
	 
	void CreateFile(); // ����� ��� �������� ����� �� ������� ����
	void ChooseWord(); // ����� ��� ������ ����� �� �����

	void LetPlay(); // ����� ���� ����
	void Condition(); // ������� ���� � �������� �����

	void Mistakes(int value); // ����� ������������ ������

	void FirstHint(); // �������� ������ ���������
	void SecondHint(); // �������� ������ ��������� 

	char operator[](int index) const; // ���������� ��������� []

	void ShowHiddenWord(const char *copy_word); // ����� ������  � ������� ���������� ����� 
	void ShowUserTryes(const char *user_tryes);// ����� ������  � ������� ���� ������ 
	void ShowResult(); // ����������� ���������� ����

};

