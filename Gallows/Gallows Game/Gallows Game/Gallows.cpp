
#include <iostream>
#include "Gallows.h"
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// конструктор
Gallows::Gallows()
{
	CreateFile(); // создаем файл со списком слов

	ChooseWord();

	this->lenght_user_tryes = 0;
	this->guessedNumbers = 0;
}

// метод для создания файла со списком слов
void Gallows::CreateFile()
{
	ofstream fout;
	fout.open(path, ios_base::out | ios_base::trunc); // открываем файл для записи , предварительно очистив его

	if (!fout.is_open())
		cout << "Ошибка открытия файла\n";
	else {
		cout << "Файл открыт/создан\n"; // записываем слова в файл
		fout << "человек\nвремя\nжизнь\nработа\nслово\nместо\nвопрос\nстрана\nсторона\nслучай\nребенок\nголова\nсистема\nотношение\nгород\nчасть\nженщина\nпроблема\nземляn\nрешение\nвласть\nмашина\nзакон\nистория\nвойна\nнарод\nобласть\nчисло\nгруппа\nусловие\nкнига\nначало\nформа\nдействие\nстатья\nситуация\nшкола\nдорога\nвзгляд\nмомент\nминута\nмесяц\nпорядок\nпрограмма\nпомощь\nвечер\nрынок\nпартия\nулица\nзадача\nтеатр\nвнимание\nписьмо\nкомната\nсемья\nсмерть\nинтерес\nавтор\nответ\nсовет\nмужчина\nмнение\nпроект\nматериал\nпричина\nкультура\nсердце\nдокумент\nнеделя\nчувство\nслужба\nгазета\nдиректор"; // 73 слова
	}
	fout.close(); // закрываем файл
}

// метод для выбора слова из файла
void Gallows::ChooseWord()
{
	srand(time(NULL));

	ifstream fin;
	fin.open(path); // открываем файл для чтения

	int counter = 1;  // счетчик слов
	int stop = rand() % 73 + 1; // метка на каком слове остановиться	

	if (!fin.is_open())
		cout << "Ошибка открытия файла\n";
	else {

		char tmp_word[15]; // временная переменная для хранения считываемого слова

		while (!fin.eof()) { // пока файл не закончился

			fin >> tmp_word; // считываем до пробела / переноса строки и записываем во временную переменную

			if (counter == stop) {

				strcpy_s(word, tmp_word); // инициализируем word
				length_word = strlen(tmp_word); // инициализируем length_word
			}
			++counter;
		}
	}
	fin.close(); // закрываем файл

	for (int i = 0; i < length_word * 2; ++i) { // переписываем слово с добавлением пробелов через букву и буквы заменяем на "_"  ( инициализируем length_word )

		if (i == 0 || i % 2 == 0)
			copy_word[i] = '_';
		else
			copy_word[i] = ' ';
	}
}

// метод тела игры
void Gallows::LetPlay()
{
	setlocale(LC_ALL, "Russian");

	// Функция clock() возвращает время, пройденное с момента запуска программы, вызвавшей фун­кцию clock()
	clock_t start, stop; // переменные для подсчета времени игры

	cout << "\n\n***************************************\n\n";

	cout << "Вам нужно угадать слово, которое загадала программа, буква за буквой.\nВы угадываете по одной букве и можете ошибиться только " << MAX_MISTAKES << " раз.\n\n\n";

point1:
	cout << "Выбор сложности : \n\n1 - Легко ( открыты две буквы )\n2 - Средне ( открыта одна буква\n3 - Сложно ( все буквы закрыты )\n\nТвой выбор ? ";
	int difficult; // переменная для выбора сложности	
	cin >> difficult;

	start = clock(); // время начала игры

	switch (difficult) {
	case EASY:		

		FirstHint(); // используем 2 подсказки
		SecondHint();

		cout << "\n\n\t";
		ShowHiddenWord(copy_word);
		cout << "\n\n";

		Condition();

		break;

	case NORMAL:		

		FirstHint(); //  используем 1 подсказку

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
		cout << "\nВыбери правильную опцию !\n\n";
		goto point1;
		break;
	}	

	stop = clock(); // время конца игры
	// Для преобразования возвращаемой ве­личины в секунды надо разделить ее на макрос CLK_TCK.
	cout << "Время игры : " << (stop - start) / CLK_TCK << " секунд " << endl;;
		
}

// условия игры и проверки ходов
void Gallows::Condition()
{
	char user_leter; // буква которую называет пользователь

	int i = 0; // индекс для записи букв игрока

	bool isFinished = false; // для проверки , если слово отгадано
	
	int mistake = 0; // количество ошибок

	Mistakes(mistake); // рисуем виселицу

	while (isFinished != true) { // пока не отгадано или не закончились попытки				

		point:
		cout << "\n\n\nУгадай букву : ";
		cin >> user_leter;

		// проверка на случай если буква уже называлась или была открыта изначально
		if (i == 0 && user_leter != hint_first && user_leter != hint_second) {
			++lenght_user_tryes; // увеличиваем количество попыток
			user_tryes[i] = user_leter; // запись в массив попытки
		}
		else if (i > 0 && user_leter != hint_first && user_leter != hint_second) {

			bool repeat = false; // переменная для повторов

			for (int k = 0; k < lenght_user_tryes; ++k) {

				if (user_leter == user_tryes[k] ) { // если такая буква уже была

					cout << "\nЭта буква уже открыта или была названа !";

					repeat = true;
					break;
				}
			}

			if (repeat == false) { // если повторов не было
				++lenght_user_tryes; // увеличиваем количество попыток
				user_tryes[i] = user_leter;
			}
			else // если были повторы - возвращаемся на ввод буквы
				goto point;
		}
		else { // если были повторы - возвращаемся на ввод буквы
			cout << "\nЭта буква уже открыта или была названа !\n";
			goto point;
		}

		bool found = false; // переменная для найденых совпадений

		for (int j = 0; j < length_word; ++j) {

			if (word[j] == user_leter) { // если есть совпадение					
				++guessedNumbers; // увеличиваем колличество угаданых букв

				if (j == 0) {					

					copy_word[j] = user_leter; // записываем букву 
					cout << "\n\t";

					ShowHiddenWord(copy_word); // вывод результата
					
					found = true;
				}
				else {
					
					copy_word[j * 2] = user_leter; // записываем букву 
					cout << "\n\t";

					ShowHiddenWord(copy_word); // вывод результата
					
					found = true;
				}
			}
		}

		if (found == false) { // нет совпадений 
			cout << "\nТакой буквы нет!\n\n\n";
			++mistake; // +1 ошибка

			Mistakes(mistake); // рисуем виселицу

			cout << "\n=================================================\n";

			cout << "\n\nОсталось " << MAX_MISTAKES - mistake << " попыток\n";
			cout << "\n\t";

			ShowHiddenWord(copy_word);
		}

		if (guessedNumbers == length_word) { // отгаданы все буквы
			cout << "\n\nСлово отгадано!\n\n";			

			ShowResult();
			isFinished = true;
		}

		if (mistake == MAX_MISTAKES) { // исчерпано количество попыток
			cout << "\n\nТы проиграл!\n\n";			

			ShowResult();
			isFinished = true;
		}

		++i;
	}

	cout << "\n=================================================\n";
}

// метод визуализации ошибок
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

// получаем первую подсказку
void Gallows::FirstHint()
{
	bool check = false;

	// проверяем с начала слова
	// проверка - чтобы буква которую будем открывать не повторялясь
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
					break; // выход из цикла если есть повторяющиеся буквы
				}
			}
		}
		if (check == true) { // если нет повторений - открываем букву
			++guessedNumbers; // увеличиваем колличество угаданых букв

			hint_first = word[i]; // сохраняем букву в переменной

			if (i == 0) { // записываем букву в копию слова
				copy_word[i] = word[i];
			}
			else {
				copy_word[i * 2] = word[i];
			}
			break;
		}
	}
}

// получаем вторую подсказку 
void Gallows::SecondHint()
{
	bool check = false;

	// проверяем с конца слова
	// проверка чтобы буква которую будем открывать не повторялясь
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
					break; // выход из цикла если есть повторяющиеся буквы
				}
			}
		}
		if (check == true) { // если нет повторений - открываем букву
			++guessedNumbers; // увеличиваем колличество угаданых букв

			hint_second = word[i]; // сохраняем букву в переменной

			if (i == 0) { // записываем букву в копию слова
				copy_word[i] = word[i];
			}
			else {
				copy_word[i * 2] = word[i];
			}
			break;
		}
	}
}

// перегрузка оператора []
char Gallows::operator[](int index) const
{
	if (index < 0 || index >= strlen(word)) {
		exit(-1);
	}
	return word[index];
}

// метод вывода  в консоль загаданого слова 
void Gallows::ShowHiddenWord(const char *copy_word)
{
	for (int i = 0; i < length_word * 2; ++i) {
		cout << copy_word[i];
	}
}

// метод вывода  в консоль букв игрока 
void Gallows::ShowUserTryes(const char *user_tryes)
{
	for (int i = 0; i < lenght_user_tryes; ++i) {
		cout << user_tryes[i] << ' ';
	}
}

// отображение статистики игры
void Gallows::ShowResult()
{
	cout << "\tСтатистика игры : \n\nИскомое слово : " << word << "\nКоличество букв : " << length_word << "\nКоличество попыток : " << lenght_user_tryes << "\nБуквы игрока : ";

	ShowUserTryes(user_tryes);
	cout << endl;
}
