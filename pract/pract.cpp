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


for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 3; j++) {
		if (g[j][i] && g[j][i] == g[j + 1][i]) {
			g[j][i] = g[j][i] + g[j + 1][i];
			g[j + 1][i] = 0;
			score += g[j][i];
			undo_score += g[j][i];
		}
	}
}
}

void play::sum_down() {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			if (g[j][i] && g[j][i] == g[j - 1][i]) {
				g[j][i] = g[j][i] + g[j - 1][i];
				g[j - 1][i] = 0;
				score += g[j][i];
				undo_score += g[j][i];
			}
		}
	}
}

void play::sum_left() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (g[i][j] && g[i][j] == g[i][j + 1]) {
				g[i][j] = g[i][j] + g[i][j + 1];
				g[i][j + 1] = 0;
				score += g[i][j];
				undo_score += g[i][j];
			}
		}
	}
}

void play::sum_right() {
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > 0; j--) {
			if (g[i][j] && g[i][j] == g[i][j - 1]) {
				g[i][j] = g[i][j] + g[i][j - 1];
				g[i][j - 1] = 0;
				score = score + g[i][j];
				undo_score += g[i][j];
			}
		}
	}
}


void play::play_game() {
	int flag = 0;
	char choice, ch;
	initialize();
	cin >> choice;

	while ((choice == 'w' || choice == 'a' || choice == 's' || choice == 'd' || choice == 'q' || choice == 'i' || choice == 'u' || choice == 'r')) {

		if (choice != 'u') {
			vector<vector <int> > current_copy;
			current_copy.resize(4);
			for (int m = 0; m < 4; m++) {
				for (int n = 0; n < 4; n++) {
					current_copy[m].push_back(g[m][n]);
				}
			}
			undo_stack.push(current_copy);
		}


		switch (choice) {

		case 'w':
			undo_score = 0;
			move_up();
			sum_up();
			move_up();
			generate_new_index();
			system("clear");
			display();
			score_stack.push(undo_score);
			break;

		case 's':
			undo_score = 0;
			move_down();
			sum_down();
			move_down();
			generate_new_index();
			system("clear");
			display();
			score_stack.push(undo_score);
			break;

		case 'a':
			undo_score = 0;
			move_left();
			sum_left();
			move_left();
			generate_new_index();
			system("clear");
			display();
			score_stack.push(undo_score);
			break;

		case 'd':
			undo_score = 0;
			move_right();
			sum_right();
			move_right();
			generate_new_index();
			system("clear");
			display();
			score_stack.push(undo_score);
			break;

		case 'q':
			cout << "Are you sure you want to quit??\nEnter y to quit and n to continue!\n" << endl;
			cin >> ch;
			if (ch == 'y' || ch == 'Y') {
				end_display();
			}
			display();
			break;
			//display instructions
		case 'i':
			instructions();
			break;

		case 'r':
			restart();
			break;

		case 'u':
			if (undo_limit < 5) {
				if (!undo_stack.empty()) {
					vector<vector<int> > previous_copy = undo_stack.top();
					undo_stack.pop();
					for (int m = 0; m < 4; m++) {
						for (int n = 0; n < 4; n++) {
							g[m][n] = previous_copy[m][n];
						}
					}

					score -= score_stack.top();
					score_stack.pop();
					undo_limit += 1;
				}
				else {
					system("clear");
					cout << "\n\nundo not POSSIBLE, reached initial state!!!\n\n";
					display();
				}
			}
			else {
				system("clear");
				display();
				cout << "\n\nYou cannot undo the matrix more than 5 times.\n\nSorry!!!\n" << endl;
			}
		}

		int find_max = calculate_max();
		if (find_max == 2048) {
			win_display();
		}

		if (check_full()) {
			if (game_ends()) {
				lose_display();
			}
		}
		cout << "enter choice: " << endl;
		cin >> choice;
		while (choice != 'w' && choice != 's' && choice != 'd' && choice != 'a' && choice != 'q' && choice != 'i' && choice != 'u' && choice != 'r') {
			cout << "\nYou had entered the wrong choice!\nPlease enter correct choice to continue!" << endl;
			cin >> choice;
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