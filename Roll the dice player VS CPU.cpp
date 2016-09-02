#include <iostream>
#include <iomanip>
#include <time.h>
#include <math.h>

using namespace std;

/*
Kубики по две штуки:
вы кидаете кубики, комп кидает кубики, вы кидаете кубики, комп кидает кубики ...
(на самом деле что вы, что комп -- все равно кидает рандом).
—читаете суммy баллов и находите победител€
1) показать красиво кубики (нарисовать псевдографикой); 2) рандом; 3) смена хода; 4) подсчет.
*/

#define HEIGHT 6 
#define WIDTH 11 
#define GRANES 6
char dice[HEIGHT][WIDTH][GRANES] = {};

/*
j012345678910
i
0  _______
1 /       \
2|  *   *  |
3|  * * *  |
4|  *   *  |
5 \_______/
*/

void createTheDices() {
	for (int k = 0; k < GRANES; ++k) {
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
				if ((i == 0 || i == HEIGHT - 1) && (j > 0 && j < WIDTH - 1))
					dice[i][j][k] = '_';
				else if ((i == 1 && j == 0) || (i == HEIGHT - 1 && j == WIDTH - 1))
					dice[i][j][k] = '/';
				else if ((i == 1 && j == WIDTH - 1) || (i == HEIGHT - 1 && j == 0))
					dice[i][j][k] = '\\';
				else if (i > 1 && i < HEIGHT - 1)
					dice[i][0][k] = dice[i][WIDTH - 1][k] = '|';
				else
					dice[i][j][k] = ' ';
				if ((k == 0 || k == 2 || k == 4) && i == 3 && j == 5 ||
					(k != 0) && ((i == 2 && j == 3) || (i == 4 && j == 7)) ||
					k > 2 && ((i == 4 && j == 3) || (i == 2 && j == 7)) ||
					k == 5 && i == 3 && (j == 3 || j == 7))
					dice[i][j][k] = '*';
			}			
		}
	}
}

int drop(int delay, int divider) {
	int turns = rand() % divider + divider;
	int k1 = 0, k2 = 0;
	while (turns > 0) {
		system("cls");
		k1 = rand() % 6, k2 = rand() % 6;
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j)
				cout << dice[i][j][k1];
			cout << "\t\t";
			for (int j = 0; j < WIDTH; ++j)
				cout << dice[i][j][k2];
			cout << endl;
		}
		_sleep(delay);
		system("cls");
		--turns;
	}
	system("cls");
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j)
			cout << dice[i][j][k1];
		cout << "\t\t";
		for (int j = 0; j < WIDTH; ++j)
			cout << dice[i][j][k2];
		cout << endl;
	}
	++k1; ++k2;
	return k1 + k2;
}

int fullDrop() {
	int delay = 15,
		divider = 5,
		score;
	while (divider > 1) {
		drop(delay, divider);
		delay *= 2;
		--divider;
	}
	score = drop(delay, divider);
	cout << "The score is " << score << "." << endl;
	return score;
}

void main() {
	
	cout << "\t\t-=Roll the dice=-" << endl << endl;
		srand(time(NULL));
		char answer;
		int player = 1, yourScore, CPUscore;
		createTheDices();
		do {
			cout << "Your turn. Press 'ENTER' to continue.";
			cin.get();
			yourScore = fullDrop();
			cout << "CPU's turn. Press 'ENTER' to continue.";
			cin.get();
			CPUscore = fullDrop();
			if (yourScore > CPUscore)
				cout << "You win." << endl << endl;
			else if (yourScore < CPUscore)
				cout << "CPU win." << endl << endl;
			else
				cout << "It's draw." << endl << endl;
			cout << "Play again? (Y\\N)";
			cin >> answer;
			while (answer != 'n' && answer != 'N' && answer != 'y' && answer != 'Y') {
				cout << "'Y' or 'N', please.";
				cin >> answer;
			}
		} while (answer != 'n' && answer != 'N');	
}
