#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	fstream inputFile;
	inputFile.open(filename, ios::in);
	if(inputFile.is_open()){
		vector<string> row;
		string line, word;
		int count = 0;
		while(!inputFile.eof()){
			row.clear();
			getline(inputFile, line);
			if(line != "" || count != 0){
				//Separates data
				stringstream ss(line);
				while (getline(ss, word, ',')) {
					row.push_back(word);
				}
				if(row.size() == 5){
					book currentBook;
					currentBook.book_id = stoi(row[0]);
					currentBook.title = row[1];
					currentBook.author = row[2];
					int state = stoi(row[3]);
					if(state == IN){
						currentBook.state = IN;
					}
					else if(state == OUT){
						currentBook.state = OUT;
					}
					else{
						currentBook.state = UNKNOWN;
					}
					currentBook.loaned_to_patron_id = stoi(row[4]);
					books.push_back(currentBook);
				}
				count++;
			}
			else{
				inputFile.close();
				return NO_BOOKS_IN_LIBRARY;
			}
		}
		inputFile.close();
	}
	else{
		return COULD_NOT_OPEN_FILE;
	}
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	fstream outputFile;
	outputFile.open(filename, ios::out);
	if(outputFile.is_open()){
		if(books.size() == 0){
			outputFile.close();
			return NO_BOOKS_IN_LIBRARY;
		}
		else{
			int size = books.size();
			for(int i = 0; i < size; i++){
				outputFile << books[i].book_id;
				outputFile << "," << books[i].title;
				outputFile << "," << books[i].author;
				outputFile << "," << books[i].state;
				outputFile << "," << books[i].loaned_to_patron_id << "\n";
			}
			outputFile.close();
			return SUCCESS;
		}
	}
	else{
		return COULD_NOT_OPEN_FILE;
	}
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	fstream inputFile;
	inputFile.open(filename, ios::in);
	if(inputFile.is_open()){
		vector<string> row;
		string line, word;
		int count = 0;
		while(!inputFile.eof()){
			row.clear();
			getline(inputFile, line);
			if(line != "" || count != 0){
				//Separates data
				stringstream ss(line);
				while (getline(ss, word, ',')) {
					row.push_back(word);
				}
				if(row.size() == 3){
					patron currentPatron;
					currentPatron.patron_id = stoi(row[0]);
					currentPatron.name = row[1];
					currentPatron.number_books_checked_out = stoi(row[2]);
					patrons.push_back(currentPatron);
				}
				count++;
			}
			else{
				inputFile.close();
				return NO_PATRONS_IN_LIBRARY;
			}
		}
		inputFile.close();
	}
	else{
		return COULD_NOT_OPEN_FILE;
	}
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	fstream outputFile;
		outputFile.open(filename, ios::out);
		if(outputFile.is_open()){
			if(patrons.size() == 0){
				outputFile.close();
				return NO_PATRONS_IN_LIBRARY;
			}
			else{
				int size = patrons.size();
				for(int i = 0; i < size; i++){
					outputFile << patrons[i].patron_id << ",";
					outputFile << patrons[i].name << ",";
					outputFile << patrons[i].number_books_checked_out << "\n";
				}
				outputFile.close();
				return SUCCESS;
			}
		}
		else{
			return COULD_NOT_OPEN_FILE;
		}
}
