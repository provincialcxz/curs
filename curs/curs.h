#pragma once
#include <iostream> 
#include <stdio.h> 
#include <algorithm> 
#include <string>
using namespace std;

const char* pathB = "C:\\examples\\book.txt"; // файл с книгами 
const char* pathR = "C:\\examples\\reader.txt"; // файл с читателями 
const char* pathC = "C:\\examples\\count.txt"; // файл с отчетом 
int bCOUNT{}, rCOUNT{};

struct Book {
    string title;
    string author;
    int amount;

};

struct Reader {
    string name;
    int numBook;
};

struct Counts {
    int book_inLib;
    int book_inRead;
};

Book* books = nullptr;
Reader* read = nullptr;

void menu();

int save_button();

Book* read_saveBook();
Reader* read_saveRead();

void printBooks(const Book books[]);
void printReader(const Reader read[]);

void editBook(Book& book);
void editReader(Reader& read);

void findBookByTitle(Book* books, const string& title);
void findReaderByName(Reader* read, const string& name);
void findBookByAuthor(Book* books, string author);

void sortByTitleHelper(Book* books, int left, int right);
void sortByAuthorHelper(Book* books, int left, int right);
void sortReaderByNameHelper(Reader* readers, int left, int right);

void sortBooksByTitle();
void sortBooksByAuthor();
void sortReaderByName();

void new_book(Book*& books);
void new_reader(Reader*& massR);

void delete_book(Book*& books);
void delete_reader(Reader* massR);

void report(Book* books, Reader* readers);