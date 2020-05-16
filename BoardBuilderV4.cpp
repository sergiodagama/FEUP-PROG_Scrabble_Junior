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
short int sizeofboard, count = 0; 

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
void wordVerifier(vector<string> words, string& Word)
{
	while (find(words.begin(), words.end(), Word) == words.end())
	{
		cout << endl << "Word does not exist, choose another one: " << endl;
		cin >> Word;
	}
}

//Verifier for words vertically (s = size of board, p = pos[0]) 
bool sizeVerifier(int x, int y, string dir, int wordlength)
{
	if ((y + wordlength) - 1 > sizeofboard&& dir == "H")
	{
		return false;
	}
	
	else if ((x + wordlength) - 1 > sizeofboard&& dir == "V")
	{
		return false;
	}
	
	else
	{
		return true;
	}
}

//checks for intersections and verifies the places arround word
bool intersection(vector<char> WordSplit, int x, int y, vector<vector<char>> board, string pos, string dir, int wordlength) //verify if any intersection occur, and if it occurs, verify if possible
{
	short int n = 0;
	char h, v;

	if (dir == "H")
	{
		if (wordlength + 1 + y < sizeofboard)
		{
			if (board[x][ wordlength + y + 1] != 0)
			{
				return false;
				n++;
			}
		}
		if (y > 0 && board[x][y-1] != 0)
		{
			if (board[x - 1][y] != 0)
			{
				return false;
				n++;
			}
		}
	}


	else if (dir == "V")
	{
		if (wordlength + x + 1 < sizeofboard)
		{
			if (board[wordlength + x + 1][y] != 0)
			{
				return false;
				n++;
			}
		}
		if (x > 0 && board[x - 1][y] != 0)
		{
			if (board[x - 1][y] != 0)
			{
				return false;
				n++;
			}
		}
	}

	if (n == 0) 
	{
		for (int i = 0; i < wordlength; i++)
		{
			if (dir == "H")
			{
				h = board[x][y + i];
				if (h != 0)
				{
					if (h != WordSplit[i])
					{
						return false;
						n++;
						break;
					}
				}
			}
			else if (dir == "V")
			{
				v = board[x + i][y];
				if (v != 0)
				{
					if (v != WordSplit[i])
					{
						return false;
						n++;
						break;
					}
				}
			}
		}
	}
	if (n == 0)
	{
		return true;
	}
}

//Inserts word in board
void insertInBoard(vector<char> WordSplit, ofstream& myfile, int x, int y, vector<vector<char>>& board, string Word, string pos, string dir, int wordlength) //Insert word in board after it has been verified
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

//Let the user creat the board manually
void manualBoard(ofstream& myfile, vector<string> words, vector<vector<char>>& board, string& pos, string& dir) //Manual board creator
{
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	short int x = 0, y = 0;
	string end = "yes";
	unsigned short int wordcount = 0;
	string Word;
	
	while (end != "no" && wordcount < 15) //loops until no more words are asked, reasonable Maximum of words 15
	{
		dir = "";
		x = NULL;
		y = NULL;
		
		cout << "\nWord: \n"; //Input a word, check its size, then split it into a vector
		cin >> Word;
		int wordlength = Word.size();
		vector<char> WordSplit(Word.begin(), Word.end());
		wordVerifier(words, Word);
		
		while (dir != "H" || dir != "V") //Ask for words direction
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
		cout << "\nPosition of First letter: (in letters, ex: Aa) \n"; 
		cin >> pos;
		
		x = ALPHA.find(pos[0]) + 1;
		y = alpha.find(pos[1]) + 1;

		if (sizeVerifier(x, y, dir, wordlength) == false)
		{
			cout << "Word too long";
			continue;
		}

		if (intersection(WordSplit, x, y, board, pos, dir, wordlength))
		{
			insertInBoard(WordSplit, myfile, x, y, board, Word, pos, dir, wordlength);
		}
		else
		{
			continue;
		}
		wordcount++;
		Word = "";
		cout << "\nYou already have " << wordcount << " words in your board\n" << endl;
		cout << "Do you want to add more words? (yes or no) \n"; cin >> end;
	}
}

//Check if Word2 is valid and if it fits
void Wordintersecting(vector<vector<char>>& board, string& Word2, vector<string> words, string dir, int random_number, vector<char> WordSplit, int x, int y, ofstream& myfile, int& W2)
{
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	string Xl, Yl; //Letter in x and Letter in Y
	string dir2, pos2;
	vector<char> WordSplit2(Word2.begin(), Word2.end());
	short int x2 = -1;
	short int y2 = -1;
	bool F = true;

	if (dir == "H") //Word2 needs to be perpendicular to Word1 so it intersects
	{
		dir2 = "V";
	}
	else
	{
		dir2 = "H";
	}

	int check = 0;

	for (int i = 0; i < WordSplit.size(); i++) //Check if Words have any letter in common
	{
		for (int j = 0; j < WordSplit2.size(); j++)
		{
			if (WordSplit[i] == WordSplit2[j])
			{
				if (dir2 == "H")
				{
					x2 = x - j;
					y2 = y + i;
					check++;
					break;
				}
				else
				{
					x2 = x + i;
					y2 = y - j;
					check++;
					break;
				}
			}
		}
		
		if (check != 0)
		{
			break;
		}
	}

	//Check if starting position is possible
	if ((x2 < 0 || y2 < 0 || (y2 + WordSplit2.size()) < sizeofboard) && dir2 == "H")
	{
		F = false;
	}
	else if ((x2 < 0 || y2 < 0 || (x2 + WordSplit2.size()) < sizeofboard) && dir2 == "V")
	{
		F = false;
	}

	
	if (F == true)
	{
		Xl = ALPHA[x2];
		Yl = alpha[y2];

		pos2 = "";
		pos2.append(Xl);
		pos2.append(Yl);
		if (sizeVerifier(x2, y2, dir2, Word2.size()))
		{
			if (intersection(WordSplit2, x2, y2, board, pos2, dir2, Word2.size()) == true)
			{
				insertInBoard(WordSplit2, myfile, x2, y2, board, Word2, pos2, dir2, Word2.size());
				W2++;
			}
		}
	}

}
void automaticBoard(ofstream& myfile, string, vector<string> words, vector<vector<char>>& board, string& pos, string& dir)
{
	string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	short int x = 0, y = 0, word_count = 0;
	int random_number;
	string RandDir = "HV", RandX, RandY;
	string Word, Word2;

	cout << "\nHow many words do you want in the board? (less than 15)\n"; cin >> word_count;

	while (word_count < 1 || word_count > 15)
	{
		cout << "\nInvalid number of words; select another number:" << endl;
		cin >> word_count;
	}

	while (word_count != 0)
	{
		random_number = rand() % words.size();
		Word = words[random_number];
		int wordlength = Word.size();
		vector<char> WordSplit(Word.begin(), Word.end());
		dir = RandDir[rand() % 2];

		//ignore this word if it is too long
		if (wordlength > (sizeofboard - 1))
		{
			continue;
		}

		int c = sizeofboard - wordlength;

		//removes need to check if word fits (selects random number in range)
		if (dir == "H") 
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

		//Create position

		pos = "";
		pos.append(RandX);
		pos.append(RandY);

		if (intersection(WordSplit, x, y, board, pos, dir, wordlength) == false)
		{
			continue;
		}

		else if (intersection(WordSplit, x, y, board, pos, dir, wordlength) == true && word_count > 1)
		{
			insertInBoard(WordSplit, myfile, x, y, board, Word, pos, dir, wordlength);
			
			int RN = rand() % words.size();
			Word2 = words[RN];
			int W2 = 0;
			Wordintersecting(board, Word2, words, dir, random_number, WordSplit, x, y, myfile, W2);
			
			if (W2 == 0)
			{
				word_count--;
			}
			
			else
			{
				word_count -= 2;
			}
		}

		else
		{
			insertInBoard(WordSplit, myfile, x, y, board, Word, pos, dir, wordlength);
			word_count--;
		}
	}
	cout << endl << "Board has been automatically created, heres a copy of it: " << endl;
}

//prints the whole board text file for user visualization
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
	short int x, y;
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

	while (personalized != "yes")
	{
		if (personalized == "no")
			break;
		cout << "Option not available, try again: (yes or no)" << endl;
		cin >> personalized;
	}

	//Give different to board depending if its created by the user or automatically
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
