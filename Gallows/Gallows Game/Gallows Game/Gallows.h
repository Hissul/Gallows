#pragma once

using namespace std;

class Gallows
{
	enum {EASY = 1 , NORMAL = 2 , HARD = 3, MAX_MISTAKES = 6 };
	string path = "GallowsGame.txt"; // название файла со списком слов
	char word[15]; // переменная для записи выбранного слова
	char copy_word[30]; // копия слова где вместо букв "_"
	int length_word; // длина загаданного слова
	char user_tryes[25]; // массив попыток пользователя
	int lenght_user_tryes; // количество попыток
	int guessedNumbers; // колличество угаданых букв

	char hint_first, hint_second;

public:
	Gallows(); // конструктор
	 
	void CreateFile(); // метод для создания файла со списком слов
	void ChooseWord(); // метод для выбора слова из файла

	void LetPlay(); // метод тела игры
	void Condition(); // условия игры и проверки ходов

	void Mistakes(int value); // метод визуализации ошибок

	void FirstHint(); // получаем первую подсказку
	void SecondHint(); // получаем вторую подсказку 

	char operator[](int index) const; // перегрузка оператора []

	void ShowHiddenWord(const char *copy_word); // метод вывода  в консоль загаданого слова 
	void ShowUserTryes(const char *user_tryes);// метод вывода  в консоль букв игрока 
	void ShowResult(); // отображение статистики игры

};

