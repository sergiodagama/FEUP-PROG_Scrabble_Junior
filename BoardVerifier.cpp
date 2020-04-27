// PROJ 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <conio.h>
using namespace std;
set<string> words;
string Word, pos, dir;
int main() //boardbuilder
{
	int sizeofboard;
	cout << "Size of the Board: \n"; cin >> sizeofboard;
	while (sizeofboard <= 1 && sizeofboard >= 21)
	{
		cout << "Size of the Board is not available, try another size: \n"; cin >> sizeofboard;
	}
	ofstream myfile;
	myfile.open("BOARD1.txt");
	myfile << sizeofboard << "  x  " << sizeofboard << "\n";
	myfile.close();
	int C = sizeofboard;
	//interface of board (insert here)
	DicCreator; //Create a set with all the words
	int wordcount, verifier = 0;
	while (verifier == 0)
	{
		cout << "Word: \n"; cin >> Word;
		WordVerifier(Word);
		cout << "Position of First letter: \n"; cin >> pos;
	}
}
void WordVerifier(string A)
{
	while (words.find(A) == words.end())
	{
		cout << "Word does not exist, choose another one: ";
		cin >> A;
	}
	Word = A;
}
void DicCreator()
{
	ifstream DIC; //create a set with all words
	DIC.open("WORDS.txt");
	ifstream file("WORDS.txt");
	string w;
	while (file >> w)
	{
		words.insert(w);
	}
	DIC.close();
}
//Falta um WordChecker para verificar se a posição é 'legal' e falta o template para saber como implementar a palavra
//na matriz
