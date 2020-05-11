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

int x, y;
int valid = 0;
int wordlength, sizeofboard, count = 0; //size of word, size of board, size of Dictionary
string dir, h = "H", v = "V";

vector<string> words;
string Word, pos;
string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string alpha = "abcdefghijklmnopqrstuvwxyz";


void WordVerifier()
{
	while (find(words.begin(), words.end(), Word) == words.end()) //verify if word exist in the dictionaru
	{
		cout << "\nWord does not exist, choose another one: \n";
		cin >> Word;
	}
}

void translate() //Turn Letters into Numbers
{
	int x = alpha.find(pos[0]);

	int y = ALPHA.find(pos[1]);
}

void sizeverifier() //Verifier for words vertically (s = size of board, p = pos[0]) 
{

	if ((x + wordlength) - 1 > sizeofboard && dir == "H")
	{
		valid++;
	}

	else if ((y + wordlength) - 1 > sizeofboard && dir == "V")
	{
		valid++;
	}

}

void intersection(vector<char> WordSplit, vector<vector<char>> board, ofstream &myfile) //verify if any intersection occur, and if it occurs, verify if possible
{
	for (int i = 0; i < wordlength; i++)
	{

		if (dir == "H")
		{
			if (board[y][x + i] != 0)
			{
				if (board[y][x + i] != WordSplit[i])
				{
					cout << "Word invalid because of an intersection at " << pos;
					valid++;
					break;
				}
			}
		}

		if (dir == "V")
		{
			if (board[y + i][x] != 0)
			{
				if (board[y + i][x] != WordSplit[i])
				{
					cout << "Word invalid because of an intersection at " << pos;
					valid++;
					break;
				}
			}
		}
	}
}

void InsertInBoard(vector<vector<char>> board, vector<char> WordSplit, ofstream &myfile) //Insert word in board after it has been verified
{
	for (int i = 0; i < wordlength; i++)
	{
		if (dir == "V")
		{
			board[x][y+i] = WordSplit[i];
		}
		
		else if (dir == "H")
		{
			board[x+i][y] = WordSplit[i];
		}
	}

	myfile << pos << " " << dir << " " << Word << "\n";
}

void DictionaryCreator(string lang) // Creat set with all the words
{
	//ifstream DIC;
	//DIC.open("it.txt");
	string dic = lang + ".txt";
	ifstream file(dic);
	string w;

	while (getline(file,w))
	{
		words.push_back(w);
	}
	
	file.close();
	//DIC.close();
}

void ManualBoard(vector<vector<char>> board, ofstream &myfile) //Manual board creator
{
	string end = "yes";
	int wordcount = 0;

	while (end != "no") //loops until no more words are asked
	{
		valid = 0;
		cout << "\nWord: \n";
		cin >> Word;

		wordlength = Word.size();
		vector<char> WordSplit(Word.begin(), Word.end());
		WordVerifier();

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
		translate();

		sizeverifier();

		if (valid != 0)
		{
			cout << "Word too long";
		}

		if (dir == "V") //Verify if word fits
		{
			intersection(WordSplit, board, myfile);

			if (valid != 0)
			{
				continue;
			}
			else
			{
				InsertInBoard(board, WordSplit, myfile);
			}
		}

		else if (dir == "H")
		{
			intersection(WordSplit, board, myfile);

			if (valid != 0)
			{
				continue;
			}
			else
			{
				InsertInBoard(board, WordSplit, myfile);
			}
		}

		wordcount++;

		cout << "\nYou already have " << wordcount << " words in your board\n" << endl;
		cout << "Do you want to add more words? (yes or no) \n"; cin >> end;
	}

}

void AutomaticBoard(vector<vector<char>> board, ofstream &myfile, string l)
{
	int wordcount = 0;
	int count = 0;
	string RandDir = "HV";
	string RandX, RandY;

	count = words.size();

	cout << "\n" << count << endl;

	cout << "How many words do you want in the board? (around 30)\n" ; cin >> wordcount;

	while (wordcount != 0)
	{	
		valid = 0;

		random_device rd;
		default_random_engine generator(rd());
		uniform_int_distribution<long long unsigned> distribution(0, words.size());

		int random_number = distribution(generator);

		Word = words[distribution(generator)]; //loop here if words of a certain size are desired
		wordlength = Word.size();
		vector<char> WordSplit(Word.begin(), Word.end());
		
		dir = RandDir[rand() % 2];

		if (wordlength > sizeofboard)
		{
			valid++;
		}

		if (dir == "H") // removes need to check if word fits
		{
			x = rand() % (sizeofboard-wordlength);
			y = rand() % sizeofboard;
		}
		else
		{
			x = rand() % sizeofboard;
			y = rand() % (sizeofboard - wordlength);
		}

		RandX = ALPHA[x];
		RandY = alpha[y];
		
		pos = "";
		pos.append(RandX);
		pos.append(RandY);

		if (dir == "V") //Verify if word fits
		{
			intersection(WordSplit, board, myfile);

			if (valid != 0)
			{
				continue;
			}
			else
			{
				InsertInBoard(board, WordSplit, myfile);
				wordcount--;
			}
		}

		else if (dir == "H")
		{
			intersection(WordSplit, board, myfile);

			if (valid != 0)
			{
				continue;
			}
			else
			{
				InsertInBoard(board, WordSplit, myfile);
				wordcount--;
			}
		}

	}

	cout << "\nBoard has been automatically created, heres a copy of it: \n";

}

int main() //boardbuilder
{
	string l;
	string personalized;

	ifstream language;
	language.open("lang.txt");
	getline (language, l);

	cout << "language: \n" << l << endl;

	language.close();

	DictionaryCreator(l);

	cout << "Size of the Board: \n\n"; cin >> sizeofboard;

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
		ManualBoard(board, myfile);
	}
	else if (personalized == "no")
	{
		AutomaticBoard(board, myfile, l);
	}
	
	myfile.close();

	return 0;

}
