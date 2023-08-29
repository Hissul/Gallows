
/*
3 Тема:
Создайте консольную версию игры
«Виселица».

Необходимо реализовать :

● Слово выбирается компьютером из списка слов.
● Список слов находится в файле в зашифрованном виде.
● По завершении игры на экран выводится статистика игры :
   •количество времени;
   •количество попыток;
   •искомое слово;
   •буквы игрока.
*/

#include <iostream>
#include "Gallows.h"
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>

using namespace std;

int main() {
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Gallows game; // создаем обьект класа
	 
	game.LetPlay(); // играем

	return 0;
}
