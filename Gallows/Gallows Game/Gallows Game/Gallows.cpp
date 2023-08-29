
#include <iostream>
#include "Gallows.h"
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// �����������
Gallows::Gallows()
{
	CreateFile(); // ������� ���� �� ������� ����

	ChooseWord();

	this->lenght_user_tryes = 0;
	this->guessedNumbers = 0;
}

// ����� ��� �������� ����� �� ������� ����
void Gallows::CreateFile()
{
	ofstream fout;
	fout.open(path, ios_base::out | ios_base::trunc); // ��������� ���� ��� ������ , �������������� ������� ���

	if (!fout.is_open())
		cout << "������ �������� �����\n";
	else {
		cout << "���� ������/������\n"; // ���������� ����� � ����
		fout << "�������\n�����\n�����\n������\n�����\n�����\n������\n������\n�������\n������\n�������\n������\n�������\n���������\n�����\n�����\n�������\n��������\n�����n\n�������\n������\n������\n�����\n�������\n�����\n�����\n�������\n�����\n������\n�������\n�����\n������\n�����\n��������\n������\n��������\n�����\n������\n������\n������\n������\n�����\n�������\n���������\n������\n�����\n�����\n������\n�����\n������\n�����\n��������\n������\n�������\n�����\n������\n�������\n�����\n�����\n�����\n�������\n������\n������\n��������\n�������\n��������\n������\n��������\n������\n�������\n������\n������\n��������"; // 73 �����
	}
	fout.close(); // ��������� ����
}

// ����� ��� ������ ����� �� �����
void Gallows::ChooseWord()
{
	srand(time(NULL));

	ifstream fin;
	fin.open(path); // ��������� ���� ��� ������

	int counter = 1;  // ������� ����
	int stop = rand() % 73 + 1; // ����� �� ����� ����� ������������	

	if (!fin.is_open())
		cout << "������ �������� �����\n";
	else {

		char tmp_word[15]; // ��������� ���������� ��� �������� ������������ �����

		while (!fin.eof()) { // ���� ���� �� ����������

			fin >> tmp_word; // ��������� �� ������� / �������� ������ � ���������� �� ��������� ����������

			if (counter == stop) {

				strcpy_s(word, tmp_word); // �������������� word
				length_word = strlen(tmp_word); // �������������� length_word
			}
			++counter;
		}
	}
	fin.close(); // ��������� ����

	for (int i = 0; i < length_word * 2; ++i) { // ������������ ����� � ����������� �������� ����� ����� � ����� �������� �� "_"  ( �������������� length_word )

		if (i == 0 || i % 2 == 0)
			copy_word[i] = '_';
		else
			copy_word[i] = ' ';
	}
}

// ����� ���� ����
void Gallows::LetPlay()
{
	setlocale(LC_ALL, "Russian");

	// ������� clock() ���������� �����, ���������� � ������� ������� ���������, ��������� ������� clock()
	clock_t start, stop; // ���������� ��� �������� ������� ����

	cout << "\n\n***************************************\n\n";

	cout << "��� ����� ������� �����, ������� �������� ���������, ����� �� ������.\n�� ���������� �� ����� ����� � ������ ��������� ������ " << MAX_MISTAKES << " ���.\n\n\n";

point1:
	cout << "����� ��������� : \n\n1 - ����� ( ������� ��� ����� )\n2 - ������ ( ������� ���� �����\n3 - ������ ( ��� ����� ������� )\n\n���� ����� ? ";
	int difficult; // ���������� ��� ������ ���������	
	cin >> difficult;

	start = clock(); // ����� ������ ����

	switch (difficult) {
	case EASY:		

		FirstHint(); // ���������� 2 ���������
		SecondHint();

		cout << "\n\n\t";
		ShowHiddenWord(copy_word);
		cout << "\n\n";

		Condition();

		break;

	case NORMAL:		

		FirstHint(); //  ���������� 1 ���������

		cout << "\n\n\t";
		ShowHiddenWord(copy_word);
		cout << "\n\n";

		Condition();

		break;

	case HARD:		

		cout << "\n\n\t";
		ShowHiddenWord(copy_word);
		cout << "\n\n";

		Condition();

		break;
	
	default:
		cout << "\n������ ���������� ����� !\n\n";
		goto point1;
		break;
	}	

	stop = clock(); // ����� ����� ����
	// ��� �������������� ������������ �������� � ������� ���� ��������� �� �� ������ CLK_TCK.
	cout << "����� ���� : " << (stop - start) / CLK_TCK << " ������ " << endl;;
		
}

// ������� ���� � �������� �����
void Gallows::Condition()
{
	char user_leter; // ����� ������� �������� ������������

	int i = 0; // ������ ��� ������ ���� ������

	bool isFinished = false; // ��� �������� , ���� ����� ��������
	
	int mistake = 0; // ���������� ������

	Mistakes(mistake); // ������ ��������

	while (isFinished != true) { // ���� �� �������� ��� �� ����������� �������				

		point:
		cout << "\n\n\n������ ����� : ";
		cin >> user_leter;

		// �������� �� ������ ���� ����� ��� ���������� ��� ���� ������� ����������
		if (i == 0 && user_leter != hint_first && user_leter != hint_second) {
			++lenght_user_tryes; // ����������� ���������� �������
			user_tryes[i] = user_leter; // ������ � ������ �������
		}
		else if (i > 0 && user_leter != hint_first && user_leter != hint_second) {

			bool repeat = false; // ���������� ��� ��������

			for (int k = 0; k < lenght_user_tryes; ++k) {

				if (user_leter == user_tryes[k] ) { // ���� ����� ����� ��� ����

					cout << "\n��� ����� ��� ������� ��� ���� ������� !";

					repeat = true;
					break;
				}
			}

			if (repeat == false) { // ���� �������� �� ����
				++lenght_user_tryes; // ����������� ���������� �������
				user_tryes[i] = user_leter;
			}
			else // ���� ���� ������� - ������������ �� ���� �����
				goto point;
		}
		else { // ���� ���� ������� - ������������ �� ���� �����
			cout << "\n��� ����� ��� ������� ��� ���� ������� !\n";
			goto point;
		}

		bool found = false; // ���������� ��� �������� ����������

		for (int j = 0; j < length_word; ++j) {

			if (word[j] == user_leter) { // ���� ���� ����������					
				++guessedNumbers; // ����������� ����������� �������� ����

				if (j == 0) {					

					copy_word[j] = user_leter; // ���������� ����� 
					cout << "\n\t";

					ShowHiddenWord(copy_word); // ����� ����������
					
					found = true;
				}
				else {
					
					copy_word[j * 2] = user_leter; // ���������� ����� 
					cout << "\n\t";

					ShowHiddenWord(copy_word); // ����� ����������
					
					found = true;
				}
			}
		}

		if (found == false) { // ��� ���������� 
			cout << "\n����� ����� ���!\n\n\n";
			++mistake; // +1 ������

			Mistakes(mistake); // ������ ��������

			cout << "\n=================================================\n";

			cout << "\n\n�������� " << MAX_MISTAKES - mistake << " �������\n";
			cout << "\n\t";

			ShowHiddenWord(copy_word);
		}

		if (guessedNumbers == length_word) { // �������� ��� �����
			cout << "\n\n����� ��������!\n\n";			

			ShowResult();
			isFinished = true;
		}

		if (mistake == MAX_MISTAKES) { // ��������� ���������� �������
			cout << "\n\n�� ��������!\n\n";			

			ShowResult();
			isFinished = true;
		}

		++i;
	}

	cout << "\n=================================================\n";
}

// ����� ������������ ������
void Gallows::Mistakes(int value)
{
	switch (value) {
	case 1:
		cout << "\t* * * * * *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *      ( )   \n";
		cout << "\t  *            \n";
		cout << "\t  *            \n";
		cout << "\t  *            \n";
		cout << "\t  *\n";
		cout << "\t  *\n";
		cout << "\t* * * * * * * * * *\n";
		break;
	case 2:
		cout << "\t* * * * * *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *      ( )   \n";
		cout << "\t  *       |    \n";
		cout << "\t  *       |    \n";
		cout << "\t  *       |    \n";
		cout << "\t  *\n";
		cout << "\t  *\n";
		cout << "\t* * * * * * * * * *\n";
		break;
	case 3:
		cout << "\t* * * * * *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *      ( )   \n";
		cout << "\t  *      /|    \n";
		cout << "\t  *       |    \n";
		cout << "\t  *       |    \n";
		cout << "\t  *\n";
		cout << "\t  *\n";
		cout << "\t* * * * * * * * * *\n";
		break;
	case 4:
		cout << "\t* * * * * *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *      ( )   \n";
		cout << "\t  *      /|\\  \n";
		cout << "\t  *       |    \n";
		cout << "\t  *       |    \n";
		cout << "\t  *\n";
		cout << "\t  *\n";
		cout << "\t* * * * * * * * * *\n";
		break;
	case 5:
		cout << "\t* * * * * *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *      ( )   \n";
		cout << "\t  *      /|\\  \n";
		cout << "\t  *       |    \n";
		cout << "\t  *       |    \n";
		cout << "\t  *      /     \n";
		cout << "\t  *\n";
		cout << "\t* * * * * * * * * *\n";
		break;
	case 6:
		cout << "\t* * * * * *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *      ( )   \n";
		cout << "\t  *      /|\\  \n";
		cout << "\t  *       |    \n";
		cout << "\t  *       |    \n";
		cout << "\t  *      / \\  \n";
		cout << "\t  *\n";
		cout << "\t* * * * * * * * * *\n";
		break;
	default:
		cout << "\t* * * * * *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *       *    \n";
		cout << "\t  *            \n";
		cout << "\t  *            \n";
		cout << "\t  *            \n";
		cout << "\t  *            \n";
		cout << "\t  *\n";
		cout << "\t  *\n";
		cout << "\t* * * * * * * * * *\n";
	}
}

// �������� ������ ���������
void Gallows::FirstHint()
{
	bool check = false;

	// ��������� � ������ �����
	// �������� - ����� ����� ������� ����� ��������� �� �����������
	for (int i = 0; i < length_word; ++i) {
		for (int j = 0; j < length_word; ++j) {
			
			if (i != j && word[i] != word[j]) { 
				check = true;
			}
			else {
				if (i == j)
					continue;
				else {
					check = false;
					break; // ����� �� ����� ���� ���� ������������� �����
				}
			}
		}
		if (check == true) { // ���� ��� ���������� - ��������� �����
			++guessedNumbers; // ����������� ����������� �������� ����

			hint_first = word[i]; // ��������� ����� � ����������

			if (i == 0) { // ���������� ����� � ����� �����
				copy_word[i] = word[i];
			}
			else {
				copy_word[i * 2] = word[i];
			}
			break;
		}
	}
}

// �������� ������ ��������� 
void Gallows::SecondHint()
{
	bool check = false;

	// ��������� � ����� �����
	// �������� ����� ����� ������� ����� ��������� �� �����������
	for (int i = length_word - 1; i >= 0; --i) {
		for (int j = length_word - 1; j >= 0; --j) {

			if (i != j && word[i] != word[j]) { 
				check = true;
			}
			else {
				if (i == j)
					continue;
				else {
					check = false;
					break; // ����� �� ����� ���� ���� ������������� �����
				}
			}
		}
		if (check == true) { // ���� ��� ���������� - ��������� �����
			++guessedNumbers; // ����������� ����������� �������� ����

			hint_second = word[i]; // ��������� ����� � ����������

			if (i == 0) { // ���������� ����� � ����� �����
				copy_word[i] = word[i];
			}
			else {
				copy_word[i * 2] = word[i];
			}
			break;
		}
	}
}

// ���������� ��������� []
char Gallows::operator[](int index) const
{
	if (index < 0 || index >= strlen(word)) {
		exit(-1);
	}
	return word[index];
}

// ����� ������  � ������� ���������� ����� 
void Gallows::ShowHiddenWord(const char *copy_word)
{
	for (int i = 0; i < length_word * 2; ++i) {
		cout << copy_word[i];
	}
}

// ����� ������  � ������� ���� ������ 
void Gallows::ShowUserTryes(const char *user_tryes)
{
	for (int i = 0; i < lenght_user_tryes; ++i) {
		cout << user_tryes[i] << ' ';
	}
}

// ����������� ���������� ����
void Gallows::ShowResult()
{
	cout << "\t���������� ���� : \n\n������� ����� : " << word << "\n���������� ���� : " << length_word << "\n���������� ������� : " << lenght_user_tryes << "\n����� ������ : ";

	ShowUserTryes(user_tryes);
	cout << endl;
}
