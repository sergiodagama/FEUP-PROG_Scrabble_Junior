// PROJ 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <conio.h>
#include <vector>
#include <cmath>
#include <string.h>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

int valid = 0;
int wordlength, sizeofboard, count = 0; //size of word, size of board, size of Dictionary
string dir, h = "H", v = "V";

string Word, pos;
string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string alpha = "abcdefghijklmnopqrstuvwxyz";


void WordVerifier(vector<string> words)
{
	while (find(words.begin(), words.end(), Word) == words.end()) //verify if word exist in the dictionaru
	{
		cout << "\nWord does not exist, choose another one: \n";
		cin >> Word;
	}
}

void sizeverifier(int x, int y) //Verifier for words vertically (s = size of board, p = pos[0]) 
{

	if ((y + wordlength) - 1 > sizeofboard&& dir == "H")
	{
		valid++;
	}

	else if ((x + wordlength) - 1 > sizeofboard&& dir == "V")
	{
		valid++;
	}

}

void intersection(vector<char> WordSplit, vector<vector<char>> board, ofstream& myfile, int x, int y) //verify if any intersection occur, and if it occurs, verify if possible
{
	for (int i = 0; i < wordlength; i++)
	{

		if (dir == "H")
		{
			if (board[x][y+i] != NULL)
			{
				if (board[x][y + i] != WordSplit[i])
				{
					cout << "Word invalid because of an intersection at " << pos;
					valid++;
					break;
				}
			}
		}

		if (dir == "V")
		{
			if (board[x + i][y] != NULL)
			{
				if (board[x + i][y] != WordSplit[i])
				{
					cout << "Word invalid because of an intersection at " << pos;
					valid++;
					break;
				}
			}
		}
	}
}

void InsertInBoard(vector<vector<char>> board, vector<char> WordSplit, ofstream& myfile, int x, int y) //Insert word in board after it has been verified
{
	for (int i = 0; i < wordlength; i++)
	{
		if (dir == "H")
		{
			board[x][y + i] = WordSplit[i];
		}

		else
		{
			board[x + i][y] = WordSplit[i];
		}
	}

	myfile << pos << " " << dir << " " << Word << "\n";
}

void DictionaryCreator(string lang, vector<string>& words) // Creat set with all the words
{
	//ifstream DIC;
	//DIC.open("it.txt");
	string dic = lang + ".txt";
	ifstream file(dic);
	string w;

	while (getline(file, w))
	{
		words.push_back(w);
	}

	file.close();
	//DIC.close();

}

void ManualBoard(vector<vector<char>> board, ofstream& myfile, vector<string> words) //Manual board creator
{
	int x, y;
	string end = "yes";
	int wordcount = 0;

	while (end != "no") //loops until no more words are asked
	{
		valid = 0;
		cout << "\nWord: \n";
		cin >> Word;

		wordlength = Word.size();
		vector<char> WordSplit(Word.begin(), Word.end());
		WordVerifier(words);

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

		int x = alpha.find(pos[0]);

		int y = ALPHA.find(pos[1]);

		sizeverifier(x, y);

		if (valid != 0)
		{
			cout << "Word too long";
		}


		intersection(WordSplit, board, myfile, x, y);

		if (valid != 0)
		{
			continue;
		}
		else
		{
			InsertInBoard(board, WordSplit, myfile, x, y);
		}

		wordcount++;

		cout << "\nYou already have " << wordcount << " words in your board\n" << endl;
		cout << "Do you want to add more words? (yes or no) \n"; cin >> end;
	}

}

void AutomaticBoard(vector<vector<char>> board, ofstream& myfile, string, vector<string> words)
{
	int x, y;
	int wordcount = 0;
	int count = 0;
	string RandDir = "HV";
	string RandX, RandY;

	count = words.size();

	cout << "\n" << count << endl;

	cout << "How many words do you want in the board? (around 30)\n"; cin >> wordcount;

	while (wordcount != 0)
	{
		valid = 0;

		random_device rd;
		default_random_engine generator(rd());
		uniform_int_distribution<int> distribution(0, words.size());

		int random_number = distribution(generator);

		Word = words[distribution(generator)]; //loop here if words of a certain size are desired
		wordlength = Word.size();
		vector<char> WordSplit(Word.begin(), Word.end());

		dir = RandDir[rand() % 2];

		if (wordlength > (sizeofboard - 1))
		{
			continue;
		}

		int c = (sizeofboard - 1) - wordlength;

		if (dir == "H") // removes need to check if word fits
		{
			x = rand() % sizeofboard;
			y = rand() % c;
		}

		else
		{
			x = rand() % c;
			y = rand() % sizeofboard;
		}

		RandX = ALPHA[x];
		RandY = alpha[y];

		pos = "";
		pos.append(RandX);
		pos.append(RandY);

		intersection(WordSplit, board, myfile, x, y);

		if (valid > 0)
		{
			continue;
		}
		else
		{
			InsertInBoard(board, WordSplit, myfile, x, y);
			wordcount--;
		}


	}

	cout << "\nBoard has been automatically created, heres a copy of it: \n";

}

void PrintBoard(string nameFile)
{
	ifstream print;
	print.open(nameFile + ".txt");
	string w;

	while (getline(print, w))
	{
		cout << w << endl;
	}
}

int main() //boardbuilder
{
	int x, y;
	vector<string> words;
	string l;
	string personalized;

	ifstream language;
	language.open("lang.txt");
	getline(language, l);
	language.close();

	cout << "language: \n" << l << endl;

	DictionaryCreator(l, words);

	cout << "\nSize of the Board: \n"; cin >> sizeofboard;

	while (sizeofboard <= 9 || sizeofboard >= 21)
	{
		cout << "Size of the Board is not available, try another size: (Between 10 & 20)\n"; cin >> sizeofboard;
	}

	vector<vector<char>> board(sizeofboard, vector<char>(sizeofboard));

	cout << "\nDo you want to create the board yourself? (yes or no) \n"; cin >> personalized;

	string nameFile;

	if (personalized == "yes")
	{
		nameFile = "custom_";
	}
	else if (personalized == "no")
	{
		nameFile = "random_";
	}

	nameFile += l;

	ofstream myfile;
	myfile.open(nameFile + ".txt");
	myfile << sizeofboard << "  x  " << sizeofboard << "\n";

	if (personalized == "yes")
	{
		ManualBoard(board, myfile, words);
	}
	else if (personalized == "no")
	{
		AutomaticBoard(board, myfile, l, words);
	}

	myfile.close();

	PrintBoard(nameFile);

	return 0;

}
