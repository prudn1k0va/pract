#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iomanip>

#include <stack>
#include <vector>

using namespace std;


int score = 0;

int undo_limit = 0;

int undo_score = 0;
class play {
	stack<vector<vector<int> > > undo_stack;
	stack<int> score_stack;


	int g[4][4];
	int g_copy[4][4];
	void initialize();
	void display();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	int check_full();
	int random_index(int x);
	void sum_up();
	void sum_down();
	void sum_left();
	void sum_right();
	void generate_new_index();
	int calculate_max();
	void instructions();
	int game_ends();
	void end_display();
	void win_display();
	void lose_display();
	void restart();

public:
	void play_game();
	play() {


	}
};

void play::instructions() {
	cout << "\nInstructions for playing 2048 are:: \n" << endl;
	cout << "For moving tiles enter \nw-move up/na-move left\nd-move right\ns-move down\n" << endl;
	cout << "When two tiles with same number touch, they merge into one. \nWhen 2048 is created, the player wins!\n" << endl;

	cout << "maximum 5 undo operations are supported\n";
	display();
}

int play::random_index(int x) {
	int index;
	index = rand() % x + 0;
	return index;
}

void play::lose_display() {
	system("clear");
	cout << "\t\t\tGAME OVER\n\n";
	cout << "Your final score is " << score << "\n\n";
	exit(0);
}


void play::move_down() {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j >= 0; j--) {
			if (!g[j][i]) {
				for (int k = j - 1; k >= 0; k--) {
					if (g[k][i]) {
						g[j][i] = g[k][i];
						g[k][i] = 0;
						break;
					}
				}
			}
		}
	}
}


void play::move_left() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!g[i][j]) {
				for (int k = j + 1; k < 4; k++) {
					if (g[i][k]) {
						g[i][j] = g[i][k];
						g[i][k] = 0;
						break;
					}
				}
			}
		}
	}
}

void play::move_right() {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j >= 0; j--) {
			if (!g[i][j]) {
				for (int k = j - 1; k >= 0; k--) {
					if (g[i][k]) {
						g[i][j] = g[i][k];
						g[i][k] = 0;
						break;
					}
				}
			}
		}
	}
}



void play::display() {
	cout << "\n\t\t\t\t\t\t\t 2048\n\n";
	cout << " score :: " << score << endl << endl;
	for (int i = 0; i < 4; i++) {
		cout << " ";
		for (int j = 0; j < 4; j++) {
			cout << setw(8) << g[i][j] << setw(8) << "|" << setw(8);
		}
		cout << endl << endl << endl;
	}
	cout << "\n\n\n";
	cout << "\t\t\t\t\t\t\t\t\tr-restart\n\tw\t\t\t\t^\t\t\t\ti-instructions\na\ts\td\t\t<\t" << "v" << "\t>\t\t\tq-quit u-undo\n\n";
}

int main() {
	play p;
	srand(time(NULL));
	p.play_game();
	return 0;
}