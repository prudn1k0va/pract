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

void play::restart() {
	char ch;
	cout << "\nAre you sure to restart the game??\n\n";
	cout << "enter y to restart and n to continue.\n\n";
	cin >> ch;
	if (ch == 'y') {
		score = 0;
		undo_score = 0;
		undo_stack = stack<vector<vector<int> > >();
		score_stack = stack<int>();
		initialize();
	}
}

int play::check_full() {
	int full_flag = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (g[i][j] == 0) {
				full_flag = 0;
				break;
			}
		}
	}
	return full_flag;
}

void play::win_display() {
	char ch;
	cout << "\t\t\tYOU WON!!!\n\n";
	cout << "Your total score is " << score << "\n\n";
	cout << "Do you wish to continue???\n";
	cout << "Enter y to continue and n to quit\n\n";
	cin >> ch;
	if (ch == 'n') {
		end_display();
	}
}

int play::calculate_max() {
	int i, j;
	int max = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (g[i][j] > max) {
				max = g[i][j];
			}
		}
	}
	return max;
}

void play::end_display() {
	system("clear");
	cout << "\nYour final score is :: " << score << endl << endl;

	cout << "Good Bye!!!\n" << endl;

	exit(0);
}

int play::game_ends() {
	int i, j, flag = 1;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			if (g[i][j] == g[i][j + 1]) {
				flag = 0;
				break;
			}
		}
		if (flag == 0) {
			break;
		}
	}
	if (flag == 1) {
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 4; j++) {
				if (g[i][j] == g[i + 1][j]) {
					flag = 0;
					break;
				}
			}
			if (flag == 0) {
				break;
			}
		}
	}
	return flag;
}


void play::generate_new_index() {
	int flag = 1;
	if (!check_full()) {
		while (flag) {
			int i = random_index(4);
			int j = random_index(4);
			if (g[i][j] == 0) {
				int y = rand() % 10 + 0;
				if (y < 6) {
					g[i][j] = 2;
				}
				else {
					g[i][j] = 4;
				}
				flag = 0;
			}
		}
	}
}


void play::initialize() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			g[i][j] = 0;
			g_copy[i][j] = 0;
		}
	}
	int i = random_index(4);
	int j = random_index(4);
	g[i][j] = 2;
	i = random_index(4);
	j = random_index(4);
	g[i][j] = 2;
	display();
}


void play::move_up() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!g[j][i]) {
				for (int k = j + 1; k < 4; k++) {
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




