//Board Builder: 
//Creates playable boards to use in Scrabble Junior
//Therefore it is a program complemented by the game itself

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

int valid = 0;
int wordlength, sizeofboard, count = 0; //size of word, size of board, size of Dictionary

//creates vector with all the words
void dictionaryCreator(string lang, vector<string>& words)
{
	//opens dictionary for corresponding language
	string dic = lang + ".txt";
	ifstream file(dic);
	string w;

	while (getline(file, w))
	{
		words.push_back(w);
	}

	file.close();
}

//verifies if word exists in the dictionary
void wordVerifier(vector<string> words, string &Word)
{
	while (find(words.begin(), words.end(), Word) == words.end()) 
	{
		cout << endl << "Word does not exist, choose another one: " << endl;
		cin >> Word;
	}
}

void sizeVerifier(int x, int y, string dir) //Verifier for words vertically (s = size of board, p = pos[0]) 
{

	if ((y + wordlength) - 1 > sizeofboard && dir == "H")
	{
		valid++;
	}

	else if ((x + wordlength) - 1 > sizeofboard && dir == "V")
	{
		valid++;
	}

}

//checks for intersections and verifies the places arround word
void intersection(vector<char> WordSplit, ofstream& myfile, int x, int y, vector<vector<char>> &board, string &pos, string dir) //verify if any intersection occur, and if it occurs, verify if possible
{
	for (int i = 0; i < wordlength; i++)
	{
		if (dir == "H")
		{
			char h = board[x][y + i];
			cout << h << endl;
			if (h != 0)
			{
				if (h != WordSplit[i])
				{
					cout << "Word invalid because of an intersection at " << pos << endl;
					valid++;
					break;
				}
				else
				{
					continue;
				}
			}
		}

		else if (dir == "V")
		{
			char v = board[x + i][y];
			if (v != 0)
			{
				if (v != WordSplit[i])
				{
					valid++;
					break;
				}
				else
				{
					continue;
				}
			}
		}

		//tentativa de palavras nao coladas
		/*if (dir == "H") {
			char h = board[x][y + i];
			if (x != 0) {
				if (board[x - 1][y + i] != 0)
					break;
			}
			if(x != (sizeofboard - 2)) {
				if (board[x + 1][y + i] != 0)
					break;
			}
		}*/

		/*else if (dir == "V") {
			char v = board[x + i][y];
			if (y != 0) {
				if (board[x + i][y - 1] != 0)
					break;
			}
			if (y != (sizeofboard - 2)) {
				if (board[x + i][y + 1] != 0)
					break;
			}

		}*/
	}
}

void insertInBoard(vector<char> WordSplit, ofstream& myfile, int x, int y, vector<vector<char>>& board, string Word, string &pos, string dir) //Insert word in board after it has been verified
{
	for (int i = 0; i < wordlength; i++)
	{
		if (dir == "H")
		{
			char r = WordSplit[i];
			board[x][y + i] = r;
		}

		else
		{
			char r = WordSplit[i];
			board[x + i][y] = r;
		}
	}

	myfile << pos << " " << dir << " " << Word << "\n";
}

void manualBoard(ofstream& myfile, vector<string> words, vector<vector<char>> &board, string &pos, string &dir) //Manual board creator
{
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	int x, y;
	string end = "yes";
	int wordcount = 0;
	string Word;

	while (end != "no") //loops until no more words are asked
	{
		valid = 0;
		cout << "\nWord: \n";
		cin >> Word;

		wordlength = Word.size();
		vector<char> WordSplit(Word.begin(), Word.end());
		for (int i = 0; i < wordlength; i++)
		{
			cout << WordSplit[i] << " ";
		}

		cout << endl;

		wordVerifier(words, Word);

		while (dir != "H" || dir != "V")
		{
			cout << "\nDirection of Word (H or V): \n";
			cin >> dir;
			if (dir == "V")
			{
				break;
			}
			if (dir == "H")
			{
				break;
			}
		}

		cout << "\nPosition of First letter: (in letters, ex: Aa) \n"; cin >> pos;

		int x = alpha.find(pos[0]) + 1;

		int y = ALPHA.find(pos[1]) + 1;

		sizeVerifier(x, y, dir);

		if (valid != 0)
		{
			cout << "Word too long";
		}


		intersection(WordSplit, myfile, x, y, board, pos, dir);

		if (valid != 0)
		{
			continue;
		}
		else
		{
			insertInBoard(WordSplit, myfile, x, y, board, Word, pos, dir);
		}

		wordcount++;
		Word = "";

		cout << "\nYou already have " << wordcount << " words in your board\n" << endl;
		cout << "Do you want to add more words? (yes or no) \n"; cin >> end;
	}

}

void automaticBoard(ofstream& myfile, string, vector<string> words, vector<vector<char>>& board, string &pos, string &dir)
{
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	int x, y, word_count = 0;
	int random_number;
	string RandDir = "HV", RandX, RandY;
	string Word;

	cout << "How many words do you want in the board? (around 30)" << endl; 
	cin >> word_count;

	while (word_count != 0) 
	{
		valid = 0;

		random_number = rand() % words.size();

		Word = words[random_number]; 

		wordlength = Word.size();

		vector<char> WordSplit(Word.begin(), Word.end());

		dir = RandDir[rand() % 2];

		//ignore this word if it is too long
		if (wordlength > (sizeofboard - 1))
			continue;

		int c = (sizeofboard - 1) - wordlength;

		if (dir == "H"){ //removes need to check if word fits
			x = rand() % sizeofboard;
			y = rand() % (c + 1);
		}
		else{
			x = rand() % (c + 1);
			y = rand() % sizeofboard;
		}

		RandX = ALPHA[x];
		RandY = alpha[y];

		pos = "";
		pos.append(RandX);
		pos.append(RandY);

		intersection(WordSplit, myfile, x, y, board, pos, dir);

		if (valid != 0)
		{
			word_count++;
			continue;
		}
		else
		{
			insertInBoard(WordSplit, myfile, x, y, board, Word, pos, dir);
			word_count--;
		}
	}

	cout << endl << "Board has been automatically created, heres a copy of it: " << endl;
}

//prints the whole boar text file
void printBoard(string nameFile)
{
	ifstream print;
	print.open(nameFile + ".txt");
	string w;

	while (getline(print, w))
	{
		cout << w << endl;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int x, y;
	char r;
	vector<string> words;
	string l, nameFile, personalized, pos, dir;
	//int sizeofboard;
	vector<vector<char>> board(sizeofboard, vector<char>(sizeofboard));  //maps the whole board

	//opens file that contains language choice made in Scrabble Junior
	ifstream language;  
	language.open("lang.txt");
	getline(language, l);
	language.close();

	cout << "language: " << l << endl;

	dictionaryCreator(l, words);

	int count = words.size();  //number of words in dictionary

	cout << endl << count << endl;

	cout << endl << "Size of the Board: " << endl;
	cin >> sizeofboard;

	while (sizeofboard <= 9 || sizeofboard >= 21)
	{
		cout << "Size of the Board is not available, try another size: (Between 10 & 20)" << endl; 
		cin >> sizeofboard;
	}

	//fills the map with zeros
	for (int i = 0; i < sizeofboard; i++)
	{
		vector<char> filler;
		for (int j = 0; j < sizeofboard; j++)
		{
			filler.push_back(0);
		}
		board.push_back(filler);
	}

	cout << endl << "Do you want to create the board yourself? (yes or no)" << endl;
	cin >> personalized;

	while (personalized != "yes") {

		if (personalized == "no") 
			break;

		cout << "Option not available, try again: (yes or no)" << endl;
		cin >> personalized;
	}

	if (personalized == "yes")
	{
		nameFile = "custom_";
	}
	else if (personalized == "no")
	{
		nameFile = "random_";
	}

	nameFile += l;

	//writes the first line in board text file
	ofstream myfile;
	myfile.open(nameFile + ".txt");
	myfile << sizeofboard << "  x  " << sizeofboard << "\n";

	if (personalized == "yes")
	{
		manualBoard(myfile, words, board, pos, dir);
	}
	else if (personalized == "no")
	{
		automaticBoard(myfile, l, words, board, pos, dir);
	}

	myfile.close();

	printBoard(nameFile);

	return 0;
}
