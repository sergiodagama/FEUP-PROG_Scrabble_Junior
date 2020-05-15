//Scrabble Junior Game for console

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <conio.h>

//color codes
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

//keyboard keys codes
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ESC 27

using namespace std;

//converts char to string
string getString(char x) {
	string s(1, x);

	return s;
}

//only for debug purposes, prints the current words in total plot
void debugMap(vector<string> all) {
	int sum = 0;
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	for (int i = 0; i < ALPHA.size(); i++) {
		cout << ALPHA.at(i) << ": "<< count(all.begin(), all.end(), getString(ALPHA.at(i))) << endl;
		sum += count(all.begin(), all.end(), getString(ALPHA.at(i)));
	}
	cout << sum;
}

//set cursor coordinates at X and Y
void gotoxy(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//clears screen console by printing spaces at window width
void clear(int startLine, int endLine, int width) {

	string blankWidth;

	for (int i = 0; i < width; i++) {
		blankWidth += "d";
	}
	
	 blankWidth = "                                                                                                                                                                                                            ";
	for (int i = startLine; i < endLine; i++) {
		gotoxy(0, i);
		cout << blankWidth;
	}
}

//highlights the current selected option in menu
void colorSelector(int& a, int& b, int& c, int& d, int& e, int& f, int& current, int color3, int color4) {

	if (current == 4) {
		a = color4;
		b = color3;
		c = color3;
		d = color3;
		e = color3;
		f = color3;
	}
	else if (current == 3) {
		a = color3;
		b = color4;
		c = color3;
		d = color3;
		e = color3;
		f = color3;
	}
	else if (current == 2) {
		a = color3;
		b = color3;
		c = color4;
		d = color3;
		e = color3;
		f = color3;
	}
	else if (current == 1) {
		a= color3;
		b = color3;
		c = color3;
		d = color4;
		e = color3;
		f = color3;
	}
	else if (current == 0) {
		a = color3;
		b = color3;
		c = color3;
		d = color3;
		e = color4;
		f = color3;
	}
	else if (current == -1) {
		a = color3;
		b = color3;
		c = color3;
		d = color3;
		e = color3;
		f = color4;
	}
}

//translates alphabetic position to numeric one on a whole vector<string>
void posTranslator(vector<string> pos, vector<int> &yPos, vector<int> &xPos) {
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	
	for (int i = 0; i < pos.size(); i++) {
		yPos.push_back(ALPHA.find(pos.at(i).substr(0, 1)));
		xPos.push_back(alpha.find(pos.at(i).substr(1, 1)));
	}
}

//translates alphabetic position to numeric one on a string
void soloTranslator(string pos, int& x, int& y) {
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string alpha = "abcdefghijklmnopqrstuvwxyz";

	y = ALPHA.find(pos.substr(0, 1));
	x = alpha.find(pos.substr(1, 1));
}

class Menu;

class Board {

public:

	Board();
	int getSize();
	void readBoard(string lang);
	void chooseBoard(int a, int b, int c, int d, int e, int f, int color3, int color4, HANDLE hConsole, string str14, string str15, string str16, string str17);
	void setChoice(string choice);
	vector<string> positions;
	vector<string> directions;
	vector<string> words;
	vector<string> all;
	vector<int> x;
	vector<int> y;

private:
	int size;
	bool noChoice = true;
	string choice;
	vector<string> file;
};

Board::Board() {
}

void Board::setChoice(string choice) {
	this->choice = choice;
}

//a submenu to choose the type of board
void Board::chooseBoard(int a, int b, int c, int d, int e, int f, int color3, int color4, HANDLE hConsole, string str14, string str15, string str16, string str17) {
	int current = 4, car;

	while (noChoice) {
		colorSelector(a, b, c, d, e, f, current, color3, color4);
		clear(34, 41, 0);

		gotoxy(0, 35);

		SetConsoleTextAttribute(hConsole, a);
		cout << "                                                                                   ";
		cout << str14 << endl;
		SetConsoleTextAttribute(hConsole, b);
		cout << "                                                                                   ";
		cout << str15 << endl << endl;
		SetConsoleTextAttribute(hConsole, 12);
		cout << "                                                                                  ";
		cout << str16 << endl;
		cout << "                                                                                   ";
		cout << str17 << endl;


		switch ((car = _getch())) {

		case KEY_UP:
			if (current < 4)
				current += 1;
			break;
		case KEY_DOWN:
			if (current > 3)
				current -= 1;
			break;
		case ENTER:
			switch (current) {
			case 4:
				setChoice("random");
				break;
			case 3:
				setChoice("custom");
				break;
			}
			noChoice = false;
			break;
		}
	}
}

int Board::getSize() {
	return size;
}

//reads board text file into the game
void Board::readBoard(string lang) {
	ifstream in_stream;
	in_stream.open(choice + "_" + lang + ".txt");  //opens random or custom board from boardbuilder
	if (in_stream.fail()) {
		cerr << "Input file opening failed.\n";
		exit(1);
	}
	if (in_stream.is_open()) {
		string line;
		getline(in_stream, line);
		size = stoi(line);

		while (getline(in_stream, line)) {
			file.push_back(line);
		}

		in_stream.close();
	}

	for (int i = 0; i < file.size(); i++) {
		positions.push_back(file.at(i).substr(0, 2));
		directions.push_back(file.at(i).substr(3, 1));
		words.push_back(file.at(i).substr(5, file.at(i).size() - 5));
	}
	for (int i = 0; i < words.size(); i++) {
		for (int h = 0; h < words.at(i).size(); h++) {
			all.push_back(getString(words.at(i).at(h)));
		}
	}
}

//each player as an individual pool in this game implementation
class Pool {

public:
	Pool(vector<string> &all);
	void newPool(vector<string>& all);
	void delElement(int n);
	void fillPool(vector<string> &all, vector<int> counter);
	bool isEmpty(vector<int> &counter);
	string getElement(int n);

private:
	vector<string> letters;
};

Pool::Pool(vector<string> &all) {
	int temp = 0;

	for (int i = 0; i < 7; i++) {
		temp = rand() % all.size();
		letters.push_back(all.at(temp));
		all.erase(all.begin() + temp);
	}
}

//checkes how many letters were played and retrieves it at counter
bool Pool::isEmpty(vector<int> &counter) {
	for (int i = 0; i < letters.size(); i++) {
		if (letters.at(i) == " ")
			counter.push_back(i);
	}
	if (counter.size() > 0) {
		return true;
	}
	else {
		return false;
	}
}

string Pool::getElement(int n) {
	switch (n) {
	case 0:
		return letters.at(0);
		break;
	case 1:
		return letters.at(1);
		break;
	case 2:
		return letters.at(2);
		break;
	case 3:
		return letters.at(3);
		break;
	case 4:
		return letters.at(4);
		break;
	case 5:
		return letters.at(5);
		break;
	case 6:
		return letters.at(6);
		break;
	}
}

//fills individual pool with (counter) number of random letters at total pool (all)
void Pool::fillPool(vector<string>& all, vector<int> counter) {
	int temp = 0;

	for (int i = 0; i < counter.size(); i++) {
		temp = rand() % all.size();
		letters.at(counter.at(i)) = all.at(temp);
		all.erase(all.begin() + temp);
	}

	vector<string>::iterator new_end;
	new_end = remove(all.begin(), all.end(), " ");
}

//erases elements by replacing it with " " to keep number of elements the same
void Pool::delElement(int n) {
	switch (n) {
		case 0:
			letters.at(0) = " ";
			break;
		case 1:
			letters.at(1) = " ";
			break;
		case 2:
			letters.at(2) = " ";
			break;
		case 3:
			letters.at(3) = " ";
			break;
		case 4:
			letters.at(4) = " ";
			break;
		case 5:
			letters.at(5) = " ";
			break;
		case 6:
			letters.at(6) = " ";
			break;
	}
}

//fills pool with completely new random elements from total pool (all)
void Pool::newPool(vector<string>& all) {
	vector<string> temp;
	int tempe = 0;

	for (int i = 0; i < letters.size(); i++){
		temp.push_back(letters.at(i));
	}

	letters.clear();

	for (int i = 0; i < 7; i++) {
		tempe = rand() % all.size();
		letters.push_back(all.at(tempe));
		all.erase(all.begin() + tempe);
	}

	for (int i = 0; i < temp.size(); i++) {
		all.push_back(temp.at(i));
	}

	vector<string>::iterator new_end;
	new_end = remove(all.begin(), all.end(), " ");
}

class Player {

public:
	Player();
	Player(string name);
	void setName(string name);
	bool verifier(string play, vector<vector<bool>> &played, Board B, vector<vector<int>>& intersections, Pool &pool);
	void scoring(vector<vector<bool>> played, vector<vector<int>> intersections);
	void raiseScore(int raise);
	void setScore(int score);
	string getName();
	int getScore();

private:
	int score;
	string name;
	vector<string> pool;
};

Player::Player() {
	name = "player";
	score = 0;
}

Player::Player(string name) {
	this->name = name;
	score = 0;
}

void Player::scoring(vector<vector<bool>> played, vector<vector<int>> intersections) {
	int J = 0, I = 0;
	bool scored = true;
	bool scored1 = true, scored2 = true;

	if (intersections.size() == 1) {
		J = intersections.at(0).at(0);

		for (int i = 0; i < played.at(J).size(); i++) {
			if (!played.at(J).at(i)) {
				scored = false;
			}
		}
		if (scored) {
			raiseScore(1);
		}
	}
	else if (intersections.size() == 2) {
		for (int w = 0; w < 2; w++) {
			J = intersections.at(w).at(0);

			for (int i = 0; i < played.at(J).size(); i++) {
				if (!played.at(J).at(i)) {
					if (w == 0) {
						scored1 = false;
					}
					else {
						scored2 = false;
					}
				}
			}
		}
		if (scored1 && scored2) {
			raiseScore(2);
		}
		else {
			if (scored1 || scored2) {
				raiseScore(1);
			}
		}
	}
}

//verifies if a play is valid or not -> should give false if is a valid play
bool Player::verifier(string play, vector<vector<bool>> &played, Board B, vector<vector<int>> &intersections, Pool &pool) {
	int x = 0, y = 0;
	int x2 = 0, y2 = 0;
	int J = 0, I = 0;
	bool exists = false;

	soloTranslator(play, x, y);

	if (play.size() != 4) {
		return true;
	}
	else {

		//checks if position exists
		for (int j = 0; j < B.directions.size(); j++) {
			for (int i = 0; i < B.words.at(j).size(); i++) {

				if (B.directions.at(j) == "H") {
					x2 = B.x.at(j) + i; 
					y2 = B.y.at(j);
				}
				else if (B.directions.at(j) == "V") {
					x2 = B.x.at(j);
					y2 = B.y.at(j) + i;
				}
				if (x == x2 && y == y2) {
					exists = true;
					J = j;
					I = i;
					vector<int> vec;
					vec.push_back(J);
					vec.push_back(I);
					intersections.push_back(vec);
				}
			}
		}
		
		if (!exists) {  
			return true;
		}
		else {
			//checks if is in pool
			bool inPool = false;

			for (int i = 0; i < 7; i++) {
				if (getString(play[3]) == pool.getElement(i)) {
					pool.delElement(i);
					inPool = true;
					break;
				}
			}
			if (!inPool) {
				return true;
			}

			//check if it was already played
			if (intersections.size() == 1) {
				if (played.at(J).at(I))
					return true;
			}
			else if (intersections.size() == 2) {  
				for (int i = 0; i < 2; i++) {
					J = intersections.at(i).at(0);
					I = intersections.at(i).at(1);
					if (played.at(J).at(I)) {
						return true;
					}
				}
			}
			if (intersections.size() == 1) { //no intersections
				if (I == 0 && !played.at(J).at(I)) {  //check first if is first letter of word
					played.at(J).at(I) = true;
					return false;
				}
				else {
					bool valid = true;

					for (int a = 0; a < I; a++) {
						if (!played.at(J).at(a)) {
							valid = false;
						}
					}
					if (valid) {
						played.at(J).at(I) = true;
						return false;
					}
				}
			}
			else {  //inersections exists
				for (int e = 0; e < 2; e++) {
					J = intersections.at(e).at(0);
					I = intersections.at(e).at(1);

					if (I == 0 && !played.at(J).at(I)) {  //check first if is first letter of word
						for (int h = 0; h < 2; h++){
							J = intersections.at(h).at(0);
							I = intersections.at(h).at(1);

							played.at(J).at(I) = true;
						}
						return false;
					}

					bool valid = true;

					for (int a = 0; a < I; a++) {
						if (!played.at(J).at(a)) {			
							valid = false;
						}
					}
					if (valid) {
						for (int h = 0; h < 2; h++) {
							J = intersections.at(h).at(0);
							I = intersections.at(h).at(1);

							played.at(J).at(I) = true;
						}
						return false;
					}
				}
			}
			return true;
		}
	}
}

void Player::setName(string name) {
	this->name = name;
}

void Player::setScore(int score) {
	this->score = score;
}

void Player::raiseScore(int raise) {
	score += raise;
}

string Player::getName() {
	return name;
}

int Player::getScore() {
	return score;
}

class Game {

public:
	Game();
	Game(int players);
	void startGame(string str18, string str19, string str20,string str21, int color3, HANDLE hConsole, bool &inMenu, Player& player1, Player& player2, Player& player3, Player& player4);
	void showGame(Board B, HANDLE hConsole,int color1, int color2, Player &p1, Player &p2, Player &p3, Player &p4, string str20, string str21, string str22, string str23, string str24, string lang);
	bool winner(Player p1, Player p2, Player p3, Player p4, Board B, int &winner);

private:
	int players;
	bool inGame = false, win = false;

};

Game::Game() {
	players = 2;
}

Game::Game(int players) {
	this->players = players;
}

bool Game::winner(Player p1, Player p2, Player p3, Player p4, Board B, int& winner) {
	int sum = p1.getScore() + p2.getScore() + p3.getScore() + p4.getScore();
	vector<int> scores = { p1.getScore(), p2.getScore() , p3.getScore() , p4.getScore() };
	int bigger = 0;

	for (int i = 0; i < 4; i++) {  //sees who has more points
		if (scores.at(i) > bigger)
			bigger = scores.at(i);
	}

	winner = bigger;

	if (scores.at(0) == scores.at(1) == scores.at(2) == scores.at(3)) //to check for draws
		winner = 5;

	if (sum == B.words.size())  //to check if all words are full and end the game
		return true;
}

//submenu to choose the players names
void Game::startGame(string str18, string str19, string str20, string str21, int color3, HANDLE hConsole, bool &inMenu, Player &player1, Player &player2, Player &player3, Player &player4) {
	vector<string> names;
	vector<string>::iterator it;
	string temp = "";

	inGame = true;

	SetConsoleTextAttribute(hConsole, color3);
	
	cout << "                                                   ";
	cout << str18 << endl;

	//the next loops serve to check if the name as been already choosen or not
	do {
		temp = "";
		names.push_back(temp);
		clear(41, 42, 0);
		gotoxy(0, 41);
		cout << "                                                   1 -> ";
		cin >> temp;
		player1.setName(temp);
		it = find(names.begin(), names.end(), temp);

	} while (it != names.end() || (temp.size() > 10 && temp != ""));  //also checks if size of name entered is bigger than 10

	names.push_back(temp);
	temp = "";

	do {
		clear(42, 43, 0);
		gotoxy(0, 42);
		cout << "                                                   2 -> ";
	
		if (temp != "") {
			SetConsoleTextAttribute(hConsole, LIGHTRED);
			cout << str19;
			temp = "";
			SetConsoleTextAttribute(hConsole, WHITE);
		}
		cin >> temp;
		player2.setName(temp);
		it = find(names.begin(), names.end(), temp);

	} while (it != names.end() || (temp.size() > 10 && temp != ""));

	names.push_back(temp);
	temp = "";

	if (players == 4) {
		do {
			names.push_back(temp);
			clear(43, 44, 0);
			gotoxy(0, 43);
			cout << "                                                   3 -> ";

			if (temp != "") {
				SetConsoleTextAttribute(hConsole, LIGHTRED);
				cout << str19;
				temp = "";
				SetConsoleTextAttribute(hConsole, WHITE);
			}
			cin >> temp;
			player3.setName(temp);
			it = find(names.begin(), names.end(), temp);

		} while (it != names.end() || (temp.size() > 10 && temp != ""));

		names.push_back(temp);
		temp = "";

		do {
			names.push_back(temp);

			clear(44, 45, 0);
			gotoxy(0, 44);
			cout << "                                                   4 -> ";

			if (temp != "") {
				SetConsoleTextAttribute(hConsole, 12);
				cout << str19;
				temp = "";
				SetConsoleTextAttribute(hConsole, 15);
			}
			cin >> temp;
			player4.setName(temp);
			it = find(names.begin(), names.end(), temp);

		} while (it != names.end() || (temp.size() > 10 && temp != ""));
	}

	inMenu = false;
	clear(0, 45, 0);
	gotoxy(0, 0);
}

//main game mechanics function -> prints the board, players, score, checks for player input and win or exit
void Game::showGame(Board B, HANDLE hConsole,int color1, int color2, Player &p1, Player &p2, Player &p3, Player &p4, string str20, string str21, string str22, string str23, string str24, string lang) {
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	string play1, play2, playerName; 
	int counter = 0, counter2 = 0;  //to change beetween playes in different plays
	bool verifier = true;  
	int colr = 0;  //color of current player 
	int winnerr = 4;  //just a random number with no meaning (players 0-3)
	vector<vector<int>> intersections;
	vector<Pool> allPools;

	B.readBoard(lang);

	Pool pool1(B.all);
	Pool pool2(B.all);
	Pool pool3(B.all);
	Pool pool4(B.all);

	allPools.push_back(pool1);
	allPools.push_back(pool2);
	allPools.push_back(pool3);
	allPools.push_back(pool4);

	posTranslator(B.positions, B.y, B.x);
	vector<vector<bool>> played;

	//played checks for played letters to change colors and to verifie plays
	for (int i = 0; i < B.words.size(); i++) {
		for (int k = 0; k < B.words.at(i).size(); k++) {
			vector<bool> vec;
			played.push_back(vec);
			played.at(i).push_back(false);
		}
	}

	while (!win) {
		vector<int> cou;

		//checks if pools are empty
		if (pool1.isEmpty(cou)) {
			pool1.fillPool(B.all, cou);
		}
		cou.clear();
		if (pool2.isEmpty(cou)) {
			pool2.fillPool(B.all, cou);
		}
		cou.clear();
		if (pool3.isEmpty(cou)) {
			pool3.fillPool(B.all, cou);
		}
		cou.clear();
		if (pool4.isEmpty(cou)) {
			pool4.fillPool(B.all, cou);
		}

		play1 = "";
		play2 = "";

		//print the alpahbet indicators
		SetConsoleTextAttribute(hConsole, color1);

		gotoxy(80, 5);
		for (int i = 0; i < B.getSize(); i++) {
			cout << alpha[i] << " ";
		}

		for (int i = 0; i < B.getSize(); i++) {
			gotoxy(77, 7 + i);
			cout << ALPHA[i];
		}

		//agroups all the code to print the whole parts of game
		auto printBoard = [&]() {
			//print the board
			SetConsoleTextAttribute(hConsole, WHITE);

			for (int j = 0; j < B.directions.size(); j++) {
				for (int i = 0; i < B.words.at(j).size(); i++) {

					if (played.at(j).at(i)) {
						SetConsoleTextAttribute(hConsole, color2);
					}
					else {
						SetConsoleTextAttribute(hConsole, 15);
					}

					if (B.directions.at(j) == "H") {
						gotoxy((B.x.at(j) + i) * 2 + 80, B.y.at(j) + 7);
					}
					else if (B.directions.at(j) == "V") {
						gotoxy(B.x.at(j) * 2 + 80, B.y.at(j) + i + 7);
					}
					cout << B.words.at(j).substr(i, 1);
				}
			}
			
			/*print entire pool of letters available (DEBUG)
			gotoxy(0, 0);
			debugMap(B.all);*/

			//print score, inputs and each ones pool
			if (players == 2) {
				gotoxy(30, 5);
				SetConsoleTextAttribute(hConsole, LIGHTBLUE);
				cout << p1.getName() << ": " << p1.getScore();
				gotoxy(30, 7);
				cout << pool1.getElement(0) << " " << pool1.getElement(1) << " " << pool1.getElement(2) << " " << pool1.getElement(3);
				gotoxy(30, 8);
				cout << pool1.getElement(4) << " " << pool1.getElement(5) << " " << pool1.getElement(6);
				gotoxy(130 + B.getSize(), 5);
				SetConsoleTextAttribute(hConsole, LIGHTRED);
				cout << p2.getName() << ": " << p2.getScore();
				gotoxy(130 + B.getSize(), 7);
				cout << pool2.getElement(0) << " " << pool2.getElement(1) << " " << pool2.getElement(2) << " " << pool2.getElement(3);
				gotoxy(130 + B.getSize(), 8);
				cout << pool2.getElement(4) << " " << pool2.getElement(5) << " " << pool2.getElement(6);

				switch (counter) {
				case 0:
					colr = LIGHTBLUE;
					playerName = p1.getName();
					break;
				case 1:
					colr = LIGHTRED;
					playerName = p2.getName();
					counter = -1;
					break;
				}
			}
			else if (players == 4) {
				gotoxy(30, 5);
				SetConsoleTextAttribute(hConsole, LIGHTBLUE);
				cout << p1.getName() << ": " << p1.getScore();
				gotoxy(30, 7);
				cout << pool1.getElement(0) << " " << pool1.getElement(1) << " " << pool1.getElement(2) << " " << pool1.getElement(3);
				gotoxy(30, 8);
				cout << pool1.getElement(4) << " " << pool1.getElement(5) << " " << pool1.getElement(6);
				gotoxy(130 + B.getSize(), 5);
				SetConsoleTextAttribute(hConsole, LIGHTRED);
				cout << p2.getName() << ": " << p2.getScore();
				gotoxy(130 + B.getSize(), 7);
				cout << pool2.getElement(0) << " " << pool2.getElement(1) << " " << pool2.getElement(2) << " " << pool2.getElement(3);
				gotoxy(130 + B.getSize(), 8);
				cout << pool2.getElement(4) << " " << pool2.getElement(5) << " " << pool2.getElement(6);
				gotoxy(30, 20);
				SetConsoleTextAttribute(hConsole, LIGHTGREEN);
				cout << p3.getName() << ": " << p3.getScore();
				gotoxy(30, 22);
				cout << pool3.getElement(0) << " " << pool3.getElement(1) << " " << pool3.getElement(2) << " " << pool3.getElement(3);
				gotoxy(30, 23);
				cout << pool3.getElement(4) << " " << pool3.getElement(5) << " " << pool3.getElement(6);
				gotoxy(130 + B.getSize(), 20);
				SetConsoleTextAttribute(hConsole, YELLOW);
				cout << p4.getName() << ": " << p4.getScore();
				gotoxy(130 + B.getSize(), 22);
				cout << pool3.getElement(0) << " " << pool3.getElement(1) << " " << pool3.getElement(2) << " " << pool3.getElement(3);
				gotoxy(130 + B.getSize(), 23);
				cout << pool3.getElement(4) << " " << pool3.getElement(5) << " " << pool3.getElement(6);

				switch (counter) {
				case 0:
					colr = LIGHTBLUE;
					playerName = p1.getName();
					break;
				case 1:
					colr = LIGHTRED;
					playerName = p2.getName();
					break;
				case 2:
					colr = LIGHTGREEN;
					playerName = p3.getName();
					break;
				case 3:
					colr = YELLOW;
					playerName = p4.getName();
					counter = -1;
					break;
				}
			}

			SetConsoleTextAttribute(hConsole, color1);

			//instructions for player to input in game
			clear(30, 50, 0);
			gotoxy(60, 27);
			cout << str20;
			gotoxy(60, 28);
			cout << str21;
			gotoxy(60, 29);
			cout << str22;
			gotoxy(60, 30);
			cout << str23;
		};

		win = winner(p1, p2, p3, p4, B, winnerr);

		printBoard();

		verifier = true;

		while (verifier) {
			intersections.clear();

			clear(32, 33, 0);

			play1 = "";

			gotoxy(60, 32);
			SetConsoleTextAttribute(hConsole, colr);
			cout << playerName;
			SetConsoleTextAttribute(hConsole, WHITE);
			cout << "[1] -> ";
			cin >> play1;

			if (play1 == "pass" || play1 == "passar" || play1 == "passer" || play1 == "pasar" || play1 == "passare") {
				break;
			}

			if (play1 == "e") {
				win = true;
				break;
			}

			if (play1 == "n") {
				switch (counter2) {
					case 0:
						pool1.newPool(B.all);
						break;
					case 1:
						pool2.newPool(B.all);
						break;
					case 2:
						pool3.newPool(B.all);
						break;
					case 3:
						pool4.newPool(B.all);
						break;
				}
				break;
			}

			switch (counter2) {
				case 0:
					verifier = p1.verifier(play1, played, B, intersections, pool1);
					p1.scoring(played, intersections);
					break;
				case 1:
					verifier = p2.verifier(play1, played, B, intersections, pool2);
					p2.scoring(played, intersections);
					break;
				case 2:
					verifier = p3.verifier(play1, played, B, intersections, pool3);
					p3.scoring(played, intersections);
					break;
				case 3:
					verifier = p4.verifier(play1, played, B, intersections, pool4);
					p4.scoring(played, intersections);
					break;
			}
		}

		printBoard();

		verifier = true;

		if (win)  //in case of end from play1
			verifier = false;
		else
			win = winner(p1, p2, p3, p4, B, winnerr);

		while (verifier) {
			intersections.clear();

			clear(32, 33, 0);

			play2 = "";

			gotoxy(60, 32);
			SetConsoleTextAttribute(hConsole, colr);
			cout << playerName;
			SetConsoleTextAttribute(hConsole, WHITE);
			cout << " [2] -> ";
			cin >> play2;

			if (play2 == "pass" || play2 == "passar" || play2 == "passer" || play2 == "pasar" || play2 == "passare") {
				break;
			}

			if (play2 == "e") {
				win = true;
				break;
			}

			if (play2 == "n") {
				switch (counter2) {
					case 0:
						pool1.newPool(B.all);
						break;
					case 1:
						pool2.newPool(B.all);
						break;
					case 2:
						pool3.newPool(B.all);
						break;
					case 3:
						pool4.newPool(B.all);
						break;
				}
			break;
			}

			switch (counter2) {
				case 0:
					verifier = p1.verifier(play2, played, B, intersections, pool1);
					p1.scoring(played, intersections);
					break;
				case 1:
					verifier = p2.verifier(play2, played, B, intersections, pool2);
					p2.scoring(played, intersections);
					break;
				case 2:
					verifier = p3.verifier(play2, played, B, intersections, pool3);
					p3.scoring(played, intersections);
					break;
				case 3:
					verifier = p4.verifier(play2, played, B, intersections, pool4);
					p4.scoring(played, intersections);
					break;
				}
		}
		counter++;
		counter2++;
		if (players == 2 && counter2 == 2) {
			counter2 = 0;
		}
		if (players == 4 && counter2 == 4) {
			counter2 = 0;
		}
	}

	clear(0, 50, 0);

	gotoxy(90, 20);

	SetConsoleTextAttribute(hConsole, colr);

	switch (winnerr) {
		case 0:
			cout << p1.getName() << " " << str24 << endl;
			break;
		case 1:
			cout << p2.getName() << " " << str24 << endl;
			break;
		case 2:
			cout << p3.getName() << " " << str24 << endl;
			break;
		case 3:
			cout << p4.getName() << " " << str24 << endl;
			break;
		case 5:
			cout << "Draw // Empate // Match nul";  //in case of draw
	}
	_getch();
}

class Menu {

public:
	Menu();
	Menu(string theme, string lang);
	void setTheme(string theme);
	void setLang(string lang);
	void startMenu();
	void endMenu();
	void show();
	void rules();
	void records(Player p1, Player p2, Player p3, Player p4);

private:
	string theme;
	string lang;
	bool inMenu = false;
	string str1, str2, str3, str4, str5, str6, str7, str8, str9, str10;
	string str11, str12, str13, str14, str15, str16, str17, str18, str19, str20;
	string str21, str22, str23, str24;
	int color1, color2, color3, color4;
};

Menu::Menu() {
	setTheme("light");
	setLang("en");
}

Menu::Menu(string theme, string lang) {
	this->theme = theme;
	this->lang = lang;
}

void Menu::startMenu() {
	inMenu = true;
}

void Menu::endMenu() {
	inMenu = false;
}

//themes selector -> one of the main menu options
void Menu::setTheme(string theme) {
	this->theme = theme;

	if (theme == "light") {
		color1 = LIGHTGREEN;
		color2 = LIGHTCYAN;
		color3 = WHITE;
		color4 = BROWN;
	}
	else if (theme == "dark") {
		color1 = DARKGRAY;
		color2 = MAGENTA;
		color3 = DARKGRAY;
		color4 = WHITE;
	}
	else if (theme == "blue") {
		color1 = LIGHTBLUE;
		color2 = LIGHTCYAN;
		color3 = WHITE;
		color4 = CYAN;
	}
	else if (theme == "red") {
		color1 = RED;
		color2 = BROWN;
		color3 = WHITE;
		color4 = LIGHTRED;
	}
}

//changes language and creates lang text file to be used by Board Builder complementary program
//en -> English
//pt -> Portuguese
//fr -> French
//es -> Spanish
//it -> Italian
void Menu::setLang(string lang) {
	ofstream language;
	language.open("lang.txt");
	language << lang;

	this->lang = lang;

	if (lang == "en") {
		str1 = "--> 2 Players <--";
		str2 = "--> 4 Players <--";
		str3 = "-->   Rules   <--";
		str4 = "-->  Records  <--";
		str5 = "-->  Language <--";
		str6 = "-->   Theme   <--";
		str7 = "Light";
		str8 = "Dark ";
		str9 = "Blue ";
		str10 = "Red  ";
		str11 = " In main menu";
		str12 = "  press";
		str13 = "to exit the game";
		str14 = "-->  Random Game Board  <--";
		str15 = "-->  Custom Game Board  <--";
		str16 = "If custom before clicking go to";
		str17 = "Board Builder to create it!";
		str18 = "Input players name's:";
		str19 = "Name already in use or too big! Input another: ";
		str20 = "Input two letters, to the position and separately, put the character to play";
		str21 = "Example: 'Ab_P'   Note that is case sensitive!";
		str22 = "There will be two inputs, for the two plays: ";
		str23 = "To pass write 'pass', 'n' to new pool and 'e' to end";
		str24 = "WINS";
	}
	else if (lang == "pt") {
		str1 = "--> 2 Jogadores <--";
		str2 = "--> 4 Jogadores <--";
		str3 = "-->    Regras   <--";
		str4 = "-->   Recordes  <--";
		str5 = "-->    Idioma   <--";
		str6 = "-->     Tema    <--";
		str7 = "Claro   ";
		str8 = "Escuro  ";
		str9 = "Azul    ";
		str10 = "Vermelho";
		str11 = "No menu principal";
		str12 = " pressione";
		str13 = "para sair do jogo";
		str14 = u8"-->  Tabuleiro de jogo aleatório  <--";
		str15 = "--> Tabuleiro de jogo costumizado <--";
		str16 = "Se personalizado antes de clicar";
		str17 = "criar o tabuleiro no Board Builder!";
		str18 = "Insira o nome dos jogadores";
		str19 = u8"Nome já utilizado ou muito grande. Insira outro: ";
		str20 = u8"Insira duas letras para a posição e, separadamente, a letra a jogar";
		str21 = u8"Exemplo: 'Ab_P'  Note que faz distinção entre maiúsculas e minúsculas!";
		str22 = u8"Haverá dois 'inputs' para cada jogada:";
		str23 = "Para passar escreva 'passar', 'n' para novas letras e 'e' para terminar";
		str24 = "GANHOU";
	}
	else if (lang == "fr") {
		str1 = "--> 2 Joueurs <--";
		str2 = "--> 4 Joueurs <--";
		str3 = u8"-->  Règles   <--";
		str4 = "-->  Records  <--";
		str5 = "-->  Langue   <--";
		str6 = "-->   Theme   <--";
		str7 = "Clair";
		str8 = "Noir ";
		str9 = "Bleu ";
		str10 = "Rouge";
		str11 = "Dans le menu principal";
		str12 = "   presse";
		str13 = "pour sortir du jeu";
		str14 = u8"-->   Plateau de jeu aléatoire  <--";
		str15 = u8"--> Plateau de jeu personnalisé <--";
		str16 = u8"Si personnalisé avant de cliquer";
		str17 = u8"créez le tableau dans Board Builder!";
		str18 = "Entrez le nom du joueur";
		str19 = u8"Nom déjà utilisé ou trés grand. Entrez un autre: ";
		str20 = u8"Entrez deux lettres pour la position et, séparément, la lettre à jouer";
		str21 = u8"Exemple: 'Ab_P' Notez qu'il est sensible à la casse!";
		str22 = u8"Il y aura deux entrées pour chaque coup : ";
		str23 = u8"Pour passer écrire 'passer' et 'n' pour nouvelles lettres et 'e' pour finir";
		str24 = u8"A GAGNÉ";
	}
	else if (lang == "es") {
		str1 = "--> 2 Jugadores <--";
		str2 = "--> 4 Jugadores <--";
		str3 = "-->   Reglas    <--";
		str4 = u8"-->   Récords   <--";
		str5 = "-->   Idioma    <--";
		str6 = "-->    Tema     <--";
		str7 = "Claro ";
		str8 = "Oscuro";
		str9 = "Azul ";
		str10 = "Rojo  ";
		str11 = u8"En el menú principal";
		str12 = "  presione";
		str13 = "para salir del juego";
		str14 = "-->     Tablero de juego al azar   <--";
		str15 = "--> Tablero de juego personalizado <--";
		str16 = "Si se personaliza antes de hacer clic";
		str17 = "crea el tablero en Board Builder!";
		str18 = "Introduzca el nombre del jugador";
		str19 = "Nombre ya usado ou muy grande.Insertar otro : ";
		str20 = "Ingrese dos letras para la posición y, por separado, la letra para jugar";
		str21 = u8"Ejemplo: 'Ab_P' ¡Tenga en cuenta que distingue entre mayúsculas y minúsculas!";
		str22 = u8"Habrá dos entradas para cada movimiento : ";
		str23 = "Para pasar escribir 'pasar', 'n' para nuevas letras y 'e' para terminar";
		str24 = "GANÓ";
	}
	else if (lang == "it") {
		str1 = "--> 2 Giocatori <--";
		str2 = "--> 4 Giocatori <--";
		str3 = "-->   Regole    <--";
		str4 = "-->   Record    <--";
		str5 = "-->   Lingua    <--";
		str6 = "-->    Tema     <--";
		str7 = "Chiaro";
		str8 = "Scuro ";
		str9 = "Blu   ";
		str10 = "Rosso ";
		str11 = "Nel menu principale";
		str12 = "  premere";
		str13 = "per uscire dal gioco";
		str14 = "-->    Tabellone di gioco casuale     <--";
		str15 = "--> Tabellone di gioco personalizzato <--";
		str16 = "Se personalizzato prima di fare clic";
		str17 = "crea la scheda in Board Builder!";
		str18 = "Inserisci il nome del giocatore";
		str19 = "Nome già utilizzato o troppo grande. Inserisci un altro : ";
		str20 = "Immettere due lettere per la posizione e, separatamente, la lettera da riprodurre";
		str21 = "Esempio: 'Ab_P' Nota che fa distinzione tra maiuscole e minuscole!";
		str22 = "Ci saranno due ingressi per ogni mossa : ";
		str23 = "Per passare scrivi 'passare' e 'n' per nuove lettere e 'e' per terminare";
		str24 = "HA VINTO";
	}

}

//for the sake of simplicity it opens websites with the respective rules at each language
void Menu::rules() {  
	if (lang == "en") {
		system("start https://www.ultraboardgames.com/scrabble/junior-game-rules.php");
	}
	else if (lang == "pt") {
		system("start https://www.ehow.com.br/jogar-scrabble-junior-como_59899/");
	}
	else if (lang == "fr") {
		system("start https://www.calhounride.com/kVRG1y6mj/");
	}
	else if (lang == "es") {
		system("start https://entretenimientodigital.net/instrucciones-de-scrabble-junior/");
	}
	else if (lang == "it") {
		system("start https://iogames.studenti.it/come-giocare-a-scarabeo-433428.html");
	}
}

//more like a log register (deprecated)
void Menu::records(Player p1, Player p2, Player p3, Player p4) {  
	string st;
	ifstream in;
	in.open("records.txt");  
	clear(0, 50, 0);

	if (in.fail()) {
		gotoxy(85, 20);
		cout << "No records yet!!" << endl;

		ofstream rec("records.txt");

		rec << p1.getName() << ":  " << p1.getScore() << endl;
		rec << p2.getName() << ":  " << p2.getScore() << endl;
		rec << p3.getName() << ":  " << p3.getScore() << endl;
		rec << p4.getName() << ":  " << p4.getScore() << endl;

		rec.close();
	}
	else {
		gotoxy(0, 0);
		cout << str4.substr(5,str4.size() - 8) << endl << endl;

		while (getline(in, st)) {
			cout << st << endl;
		}

		_getch();
	}
}

//shows main menu with options controlled by keyboard arrows 
void Menu::show() {
	
	//increases console window size
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL)
		MoveWindow(hwnd, 0, 0, 1500, 1500, TRUE);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle(TEXT("Scrabble Junior"));

	int c = 0;  //to get input from user
	int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0;
	int current = 4;  //used to select each menu option

	while (inMenu) {
		gotoxy(0, 0);

		SetConsoleTextAttribute(hConsole, color1);

		cout << "                  _____                    _____                    _____                    _____                    _____                    _____                    _____     _____                " << endl;
		cout << "                 /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\   /\\    \\  " << endl;
		cout << "                /::\\    \\                /::\\    \\                /::\\    \\                /::\\    \\                /::\\    \\                /::\\    \\                /::\\____\\ /::\\    \\   " << endl;
		cout << "               /::::\\    \\              /::::\\    \\              /::::\\    \\              /::::\\    \\              /::::\\    \\              /::::\\    \\              /:::/    //::::\\    \\ " << endl;
		cout << "              /::::::\\    \\            /::::::\\    \\            /::::::\\    \\            /::::::\\    \\            /::::::\\    \\            /::::::\\    \\            /:::/    //::::::\\    \\  " << endl;
		cout << "             /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/    //:::/\\:::\\    \\ " << endl;
		cout << "            /:::/__\\:::\\    \\        /:::/  \\:::\\    \\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/    //:::/__\\:::\\    \\        " << endl;
		cout << "            \\:::\\   \\:::\\    \\      /:::/    \\:::\\    \\      /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\      /::::\\   \\:::\\    \\      /:::/    //::::\\   \\:::\\    \\        " << endl;
		cout << "          ___\\:::\\   \\:::\\    \\    /:::/    / \\:::\\    \\    /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    /:::/    //::::::\\   \\:::\\    \\       " << endl;
		cout << "         /\\   \\:::\\   \\:::\\    \\  /:::/    /   \\:::\\    \\  /:::/\\:::\\   \\:::\\____\\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\ ___\\  /:::/\\:::\\   \\:::\\ ___\\  /:::/    //:::/\\:::\\   \\:::\\    \\" << endl;
		cout << "        /::\\   \\:::\\   \\:::\\____\\/:::/____/     \\:::\\____\\/:::/  \\:::\\   \\:::|    |/:::/  \\:::\\   \\:::\\____\\/:::/__\\:::\\   \\:::|    |/:::/__\\:::\\   \\:::|    |/:::/____//:::/__\\:::\\   \\:::\\____\\     " << endl;
		cout << "        \\:::\\   \\:::\\   \\::/    /\\:::\\    \\      \\::/    /\\::/   |::::\\  /:::|____|\\::/    \\:::\\  /:::/    /\\:::\\   \\:::\\  /:::|____|\\:::\\   \\:::\\  /:::|____|\\:::\\    \\:::\\    \\:::\\   \\::/    /    " << endl;
		cout << "         \\:::\\   \\:::\\   \\/____/  \\:::\\    \\      \\/____/  \\/____|:::::\\/:::/    /  \\/____/ \\:::\\/:::/    /  \\:::\\   \\:::\\/:::/    /  \\:::\\   \\:::\\/:::/    /  \\:::\\    \\:::\\    \\:::\\   \\/____/     " << endl;
		cout << "          \\:::\\   \\:::\\    \\       \\:::\\    \\                    |:::::::::/    /            \\::::::/    /    \\:::\\   \\::::::/    /    \\:::\\   \\::::::/    /    \\:::\\    \\:::\\    \\:::\\    \\                " << endl;
		cout << "           \\:::\\   \\:::\\____\\       \\:::\\    \\                   |::|\\::::/    /              \\::::/    /      \\:::\\   \\::::/    /      \\:::\\   \\::::/    /      \\:::\\    \\:::\\    \\:::\\____\\   " << endl;
		cout << "            \\:::\\  /:::/    /        \\:::\\    \\                  |::| \\::/____/               /:::/    /        \\:::\\  /:::/    /        \\:::\\  /:::/    /        \\:::\\    \\:::\\    \\::/    /           " << endl;
		cout << "             \\:::\\/:::/    /          \\:::\\    \\                 |::|  ~|                    /:::/    /          \\:::\\/:::/    /          \\:::\\/:::/    /          \\:::\\    \\:::\\    \\/____/             " << endl;
		cout << "              \\::::::/    /            \\:::\\    \\                |::|   |                   /:::/    /            \\::::::/    /            \\::::::/    /            \\:::\\    \\:::\\    \\            " << endl;
		cout << "               \\::::/    /              \\:::\\____\\               \\::|   |                  /:::/    /              \\::::/    /              \\::::/    /              \\:::\\____\\:::\\____\\          " << endl;
		cout << "                \\::/    /                \\::/    /                \\:|   |                  \\::/    /                \\::/____/                \\::/____/                \\::/    /\\::/    /              " << endl;
		cout << "                 \\/____/                  \\/____/                  \\|___|                   \\/____/                  ~~                       ~~                       \\/____/  \\/____/                 " << endl;

		cout << endl;

		SetConsoleTextAttribute(hConsole, color2);

		cout << "                                      .----------------.  .----------------.  .-----------------. .----------------.  .----------------.  .----------------.  " << endl;
		cout << "                                      | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |   " << endl;
		cout << "                                      | |     _____    | || | _____  _____ | || | ____  _____  | || |     _____    | || |     ____     | || |  _______     | |" << endl;
		cout << "                                      | |    |_   _|   | || ||_   _||_   _|| || ||_   \\|_   _| | || |    |_   _|   | || |   .'    `.   | || | |_   __ \\    | |" << endl;
		cout << "                                      | |      | |     | || |  | |    | |  | || |  |   \\ | |   | || |      | |     | || |  /  .--.  \\  | || |   | |__) |   | |" << endl;
		cout << "                                      | |   _  | |     | || |  | '    ' |  | || |  | |\\ \\| |   | || |      | |     | || |  | |    | |  | || |   |  __ /    | |" << endl;
		cout << "                                      | |  | |_' |     | || |   \\ `--' /   | || | _| |_\\   |_  | || |     _| |_    | || |  \\  `--'  /  | || |  _| |  \\ \\_  | |" << endl;
		cout << "                                      | |  `.___.'     | || |    `.__.'    | || ||_____|\\____| | || |    |_____|   | || |   `.____.'   | || | |____| |___| | |" << endl;
		cout << "                                      | |              | || |              | || |              | || |              | || |              | || |              | |" << endl;
		cout << "                                      | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
		cout << "                                       '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;

		gotoxy(0, 0);

		SetConsoleTextAttribute(hConsole, color4);
		cout << u8" ▄▄▄▄" << endl;
		cout << u8" █";
		SetConsoleTextAttribute(hConsole, WHITE);
		cout << lang;
		SetConsoleTextAttribute(hConsole, color4);
		cout << u8"█" << endl;
		cout << u8" ▀▀▀▀" << endl;
		
		for (int i = 0; i < 6; i++) {
			gotoxy(178, 27 + i);
			cout << "                          ";
		}

		gotoxy(178, 27);
		SetConsoleTextAttribute(hConsole, color3);
		cout << str11;
		gotoxy(180, 28);
		cout << str12;
		gotoxy(180, 29);
		SetConsoleTextAttribute(hConsole, color4);
		cout << u8"  ┏───┓";
		gotoxy(180, 30);
		cout << u8"  │ESC│";
		gotoxy(180, 31);
		cout << u8"  ┗───┛";
		gotoxy(178, 32);
		SetConsoleTextAttribute(hConsole, color3);
		cout << str13;

		colorSelector(A, B, C, D, E, F, current, color3, color4);

		gotoxy(0, 34);

		cout << endl;
		SetConsoleTextAttribute(hConsole, A);
		cout << "                                                                                        " << str1 << endl;
		SetConsoleTextAttribute(hConsole, B);
		cout << "                                                                                        " << str2 << endl;
		SetConsoleTextAttribute(hConsole, C);
		cout << "                                                                                        " << str3 << endl;
		SetConsoleTextAttribute(hConsole, D);
		cout << "                                                                                        " << str4 << endl;
		SetConsoleTextAttribute(hConsole, E);
		cout << "                                                                                        " << str5 << endl;
		SetConsoleTextAttribute(hConsole, F);
		cout << "                                                                                        " << str6 << endl;

		switch ((c = _getch())) {
			
		case KEY_UP:
			if (current < 4)
				current += 1;
			break;
		case KEY_DOWN:
			if (current > -1)
				current -= 1;
			break;
		case ESC:
			endMenu();
			break;
		case ENTER:
			Player player1, player2, player3, player4;

			if (current == 4) {
				Board Bo; 
				Bo.chooseBoard(A, B, C, D, E, F, color3, color4, hConsole, str14, str15, str16, str17);
				Game G(2);
				G.startGame(str18, str19, str20, str21, color3, hConsole, inMenu, player1, player2, player3, player4);
				G.showGame(Bo, hConsole,color1, color2, player1, player2, player3, player4, str20, str21, str22, str23, str24, lang);
			}
			else if (current == 3) {
				Board Bo;
				Bo.chooseBoard(A, B, C, D, E, F, color3, color4, hConsole, str14, str15, str16, str17);
				Game G(4);
				G.startGame(str18, str19, str20, str21, color3, hConsole, inMenu, player1, player2, player3, player4);
				G.showGame(Bo, hConsole,color1, color2, player1, player2, player3, player4, str20, str21, str22, str23, str24, lang);
			}
			else if (current == 2) {
				rules();
			}
			else if (current == 1) {
				records(player1, player2, player3, player4);
			}
			else if (current == 0) {
				c = 0;
				while (c != ENTER) {

					colorSelector(A, B, C, D, E, F, current, color3, color4);

					clear(34, 41, 0); 

					gotoxy(0, 34);

					cout << endl;
					SetConsoleTextAttribute(hConsole, A);
					cout << "                                                                                             " << "--> EN <--" << endl;
					SetConsoleTextAttribute(hConsole, B);
					cout << "                                                                                             " << "--> PT <--" << endl;
					SetConsoleTextAttribute(hConsole, C);
					cout << "                                                                                             " << "--> ES <--" << endl;
					SetConsoleTextAttribute(hConsole, D);
					cout << "                                                                                             " << "--> FR <--" << endl;
					SetConsoleTextAttribute(hConsole, E);
					cout << "                                                                                             " << "--> IT <--" << endl;

					switch ((c = _getch())) {

					case KEY_UP:
						if (current < 4)
							current += 1;
						break;
					case KEY_DOWN:
						if (current > 0)
							current -= 1;
						break;
					case ENTER:
						switch (current) {
						case 4:
							setLang("en");
							break;
						case 3:
							setLang("pt");
							break;
						case 2:
							setLang("es");
							break;
						case 1:
							setLang("fr");
							break;
						case 0:
							setLang("it");
							break;
						}
						break;
					}
				}
			}
			else if (current == -1) {
				c = 0;
				current = 4;
				while (c != ENTER) {
					
					colorSelector(A, B, C, D, E, F, current, color3, color4);

					clear(34, 41, 0);

					gotoxy(0, 34);

					cout << endl;
					SetConsoleTextAttribute(hConsole, A);
					cout << "                                                                                        " << "-->   " << str7 << "  <--" << endl;
					SetConsoleTextAttribute(hConsole, B);
					cout << "                                                                                        " << "-->   " << str8 << "  <--" << endl;
					SetConsoleTextAttribute(hConsole, C);
					cout << "                                                                                        " << "-->   " << str9 << "  <--" << endl;
					SetConsoleTextAttribute(hConsole, D);
					cout << "                                                                                        " << "-->   " << str10 <<"  <--" << endl;

					switch ((c = _getch())) {

					case KEY_UP:
						if (current < 4)
							current += 1;
						break;
					case KEY_DOWN:
						if (current > 1)
							current -= 1;
						break;
					case ENTER:
						switch (current) {
						case 4:
							setTheme("light");
							break;
						case 3:
							setTheme("dark");
							break;
						case 2:
							setTheme("blue");
							break;
						case 1:
							setTheme("red");
							break;
						}
						break;
					}
				}
			}
		}
	}
}

int main() {
	SetConsoleOutputCP(CP_UTF8);  //to print UTF8 characters like accents
	bool inGame = true;

	Menu m;
	while (inGame) {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		clear(0, 50, 0);

		m.startMenu();
		m.show();

		clear(0, 50, 0);

		gotoxy(82, 18);
		SetConsoleTextAttribute(h, LIGHTRED);
		cout << "Exit / Sair / Sortir / Salir / Uscire" << endl;
		gotoxy(95, 20);
		cout << u8"  ┏───┓";
		gotoxy(95, 21);
		cout << u8"  │ESC│";
		gotoxy(95, 22);
		cout << u8"  ┗───┛";
		SetConsoleTextAttribute(h, WHITE);

		if (_getch() == ESC)  //to exit game menu
			inGame = false;
	}
	return 0;
}
