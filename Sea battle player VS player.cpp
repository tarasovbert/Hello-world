#include <iostream>

using namespace std;

//== == = Уровень 3 == == =

//морской бой(реализовать для игры человек с человеком)
//1) отображение полей
//2) расположить корабли\организовать ввод\организовать хранение
//3) реализация стрельбы
//4) переход хода и смена полей для отображения
//5) анализ ситуации.
//все как в крестиках - ноликах
//храним данные - показываем - делаем ход - меняем данные - показываем - делаем ход
//можете сделать отдельный массивы под корабли, можете все хранить в больших
//много вариантов как организовать хранение ситуации

#define NEXT_TURN 5
#define P1_WINS 6
#define P2_WINS 7
#define HIT 8
#define MISS 9
#define ASCII_CODE_A 65
#define ASCII_CODE_J 74
#define ASCII_CODE_a 97
#define ASCII_CODE_j 106
#define ASCII_CODE_0 48
#define ASCII_CODE_1 49
#define ASCII_CODE_9 57
#define LOWER_LETTER_TO_UPPER 32

char field1[22][23], field2[22][23], coordinates[4];
int turn = 0, player,
horizontalCoordinate, verticalCoordinate,
systemHorizontalCoordinate, systemVerticalCoordinate,
systemHorizontalCoordinateNext, systemVerticalCoordinateNext;

void emptyFields() {
	char vertical = 65, horizontal = 49;
	for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 23; ++j) {
			if (j > 0 && j % 2 == 0 && i % 2 == 0)
				field1[i][j] = field2[i][j] = '|';
			if (i % 2 != 0)
				field1[i][j] = field2[i][j] = '-';
			if (j == 0 && j <= 18 && i > 0 && i % 2 == 0) {
				field1[i][j] = field2[i][j] = horizontal;
				++horizontal;
			}
			field1[20][0] = field2[20][0] = '1';
			field1[20][1] = field2[20][1] = '0';
			if (i == 0 && j >= 3 && j % 2 != 0) {
				field1[i][j] = field2[i][j] = vertical;
				++vertical;
			}
		}
	}
}

void display1(int player) {	
#define PLAYER ((player == 1) ? (field1) : (field2))
	for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 23; ++j) {
			if (PLAYER[i][j] == 's')
				cout << 'o';
			else
				cout << PLAYER[i][j];
		}
		cout << endl;
	}
}

void display2(int player) {
	++turn;
#define PLAYER ((player == 1) ? (field1) : (field2))
#define ENEMY ((player == 1) ? (field2) : (field1))
	cout << "\tTurn " << turn << "." << endl <<
		"\tPlayer " << player << "." << endl <<
		"     Your field\t\t\t\tEnemy's field" << endl << endl;
	for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 23; ++j) {
			cout << PLAYER[i][j];
		}
		cout << "\t\t";
		for (int j = 0; j < 23; ++j) {
			if (ENEMY[i][j] == 'o') 
				cout << ' ';
			else
				cout << ENEMY[i][j];
		}
		cout << endl;
	}
}

void coordinatesFromUserToSystem() {
	cout << "Enter a horizontal coordinate from 'A' to 'J' and a vertical coordinate from '1' to '10'." << endl;
	cin >> coordinates;
	while ((coordinates[0] < ASCII_CODE_A || coordinates[0] > ASCII_CODE_J) &&
		(coordinates[0] < ASCII_CODE_a || coordinates[0] > ASCII_CODE_j) ||
		(coordinates[1] < ASCII_CODE_1 || coordinates[1] > ASCII_CODE_9) ||
		(coordinates[1] == ASCII_CODE_1 && coordinates[2] != ASCII_CODE_0 && coordinates[2] != '\0') ||
		(coordinates[1] != ASCII_CODE_1 && coordinates[2] != '\0')) {
		cout << "Error! Enter the correct coordinates!" << endl;
		cin >> coordinates;
	}
	if (coordinates[0] >= ASCII_CODE_a && coordinates[0] <= ASCII_CODE_j)
		coordinates[0] -= LOWER_LETTER_TO_UPPER;
	verticalCoordinate = coordinates[1] - ASCII_CODE_0;
	if (coordinates[2] == ASCII_CODE_0)
		verticalCoordinate *= 10;
	systemHorizontalCoordinateNext = (coordinates[0] - 64) * 2 + 1,
		systemVerticalCoordinateNext = verticalCoordinate * 2;
}

int shot(int player) {
	system("cls");
	int horizontalCoordinate, verticalCoordinate,
		systemHorizontalCoordinate, systemVerticalCoordinate;	
	display2(player);
#define ENEMY ((player == 1) ? (field2) : (field1))
	cout << "Shoot, player " << player << "." <<endl;
	
	coordinatesFromUserToSystem();   	
	if (ENEMY[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] == 'o') {
		ENEMY[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] = 'X';
		return HIT;
	}
	else if (ENEMY[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] == 'X' ||
		ENEMY[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] == '!') {
		cout << "Error! You had already shot here. Make another shot." << endl;
		--turn;
		return HIT;
	}
	else {
		ENEMY[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] = '!';			
		return MISS;
	}
}

int check(int player) {
#define ENEMY ((player == 1) ? (field2) : (field1))
	for (int i = 0; i < 22; ++i)
		for (int j = 0; j < 23; ++j) 
			if (ENEMY[i][j] == 'o')
				return NEXT_TURN;
	if (player == 1)
		return P1_WINS;
	if (player == 2)
		return P2_WINS;		
	}							   

void setTheShip(int sect, int ships, int player) {
#define PLAYER ((player == 1) ? (field1) : (field2))
		int firstSectionHorizintalCoordinate, firstSectionVerticalCoordinate,
		sections = sect,
		sectionNumber = 1;
	do {
		display1(player);
		while (sections > 0) {
			cout << "sectionNumber = " << sectionNumber << endl;
			coordinatesFromUserToSystem();			
			if (sectionNumber == 1) {
				firstSectionHorizintalCoordinate = systemHorizontalCoordinateNext;
					firstSectionVerticalCoordinate = systemVerticalCoordinateNext;
			}
			if (PLAYER[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] == 's' ||
				PLAYER[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] == 'o') {
				system("cls");
				cout << "Error! There's another section of a ship already." << endl;
				display1(player);
				continue;
			}
			for (int i = systemVerticalCoordinateNext - 2; i < systemVerticalCoordinateNext + 4; i += 2) {
				for (int j = systemHorizontalCoordinateNext - 2; j < systemHorizontalCoordinateNext + 4; j += 2)
					if (PLAYER[i][j] == 'o') {
						system("cls");
						cout << "Error! Another ship is nearby." << endl;
						PLAYER[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] = 'E';
						break;
					}
				if (PLAYER[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] == 'E')
					break;
			}
			if (PLAYER[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] == 'E') {
				PLAYER[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] = ' ';
				display1(player);
				continue;
			}
			if (sectionNumber > 1) {
				if (((systemHorizontalCoordinateNext != systemHorizontalCoordinate) &&
					(systemVerticalCoordinateNext != systemVerticalCoordinate)) ||
					((systemHorizontalCoordinateNext != firstSectionHorizintalCoordinate) &&
					(systemVerticalCoordinateNext != firstSectionVerticalCoordinate))) {
					system("cls");
					cout << "Error! The ship must be located in one line." << endl;
					display1(player);
					continue;
				}
				else if (((systemHorizontalCoordinateNext > systemHorizontalCoordinate + 2) ||
					(systemHorizontalCoordinateNext < systemHorizontalCoordinate - 2) ||
					(systemVerticalCoordinateNext > systemVerticalCoordinate + 2) ||
					(systemVerticalCoordinateNext < systemVerticalCoordinate - 2)) &&
					((systemHorizontalCoordinateNext > firstSectionHorizintalCoordinate + 2) ||
					(systemHorizontalCoordinateNext < firstSectionHorizintalCoordinate - 2) ||
						(systemVerticalCoordinateNext > firstSectionVerticalCoordinate + 2) ||
						(systemVerticalCoordinateNext < firstSectionVerticalCoordinate - 2))) {
					system("cls");
					cout << "Error! The sections of the ship must be located one by one without empty spaces." << endl;
					display1(player);
					continue;
				}
				else {
					PLAYER[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] = 's';
				}
			}
			else
				PLAYER[systemVerticalCoordinateNext][systemHorizontalCoordinateNext] = 's';
			systemVerticalCoordinate = systemVerticalCoordinateNext;
			systemHorizontalCoordinate = systemHorizontalCoordinateNext;
			system("cls");
			display1(player);
			--sections;
			++sectionNumber;
		}
		for (int i = 0; i < 22; ++i) {
			for (int j = 0; j < 23; ++j) {
				if (PLAYER[i][j] == 's')
					PLAYER[i][j] = 'o';
			}
			cout << endl;
		}
		--ships;
		sections = sect;
		sectionNumber = 1;
		cout << "Ships left = " << ships << endl << endl;
	} while (ships > 0);

}

void locateTheShips() {
	player = 1;		
	for (int i = 0; i < 2; ++i) {
		int sections = 4, ships = 1;
		system("cls");
		cout << "Locate your ships, Player " << player << "." << endl << endl <<
			"One battleship (4-section)." << endl;
		setTheShip(sections, ships, player);
		sections = 3, ships = 2;
		cout << "Two cruisers (3-section)." << endl;
		setTheShip(sections, ships, player);
		sections = 2, ships = 3;
		cout << "Three destroyers (2-section)." << endl;
		setTheShip(sections, ships, player);
		sections = 1, ships = 4;
		cout << "Four boats (1-section)." << endl;
		setTheShip(sections, ships, player);
		cout << "Ships located." << endl;
		if (player == 1)
			player = 2;
	}
	player = 1;
} 

void main() { 	
	cout << "\n\n\t\t-= Sea battle =-" << endl << endl <<
		"Press any key to play" << endl;
	cin.get() << cin.get();
		emptyFields();		
		locateTheShips();
		do{
			if (shot(player) == MISS) 
				player = (player == 1) ? 2 : 1;		
			if (check(player) == P1_WINS) {
				cout << "\n\n\t\t-=Player 1 wins!=-" << endl;
				cin.get() << cin.get();
			}
			if (check(player) == P2_WINS) {
				cout << "\n\n\t\t-=Player 2 wins!=-" << endl;
				cin.get() << cin.get();
			} 		
		} while (check(player) == NEXT_TURN); 
}
