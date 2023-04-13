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

int save_button() {
    int num{};
    cout << endl;
    cout << "Сохранить?" << endl;
    cout << "1 - Да" << endl;
    cout << "2 - Нет" << endl;
    do {
        cout << "Выберите действие: ";
        if (!(cin >> num)) {
            cout << "Неверный ввод, попробуйте еще раз" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (num < 1 || num > 2) {
            cout << "Ошибка... Выберите 1 или 2" << endl;
        }
    } while (num < 1 || num > 2);

    return num;
}

Book* read_saveBook() {
    FILE* book;

    int i{};

    if (fopen_s(&book, pathB, "r") != NULL) {
        cout << "The file cannot be opened for " << pathB << "\n";
        return nullptr;
    }

    int Num = save_button();

    if (Num == 1) {
        fscanf_s(book, "%u", &bCOUNT);

        Book* mass = new Book[bCOUNT]{};

        while (!feof(book) && i < bCOUNT) {
            char temp[255]{};
            fscanf_s(book, "%s", &temp, 254);
            mass[i].title = temp;
            fscanf_s(book, "%s", &temp, 254);
            mass[i].author = temp;
            fscanf_s(book, "%d", &mass[i].amount);
            i++;
        }

        fclose(book);

        return mass;
    }
    else if (Num == 2){
        cout << "Окей, файл не сохранен." << endl;
        return 0;
    }
    else {
        cout << "Ошибка..." << endl;
    }
}

Reader* read_saveRead() {
    FILE* reader;

    int i{};

    if (fopen_s(&reader, pathB, "r") != NULL) {
        cout << "The file cannot be opened for " << pathB << "\n";
        return nullptr;
    }

    int Num = save_button();

    if (Num == 1) {
        fscanf_s(reader, "%u", &rCOUNT);

        Reader* massR = new Reader[rCOUNT]{};

        while (!feof(reader) && i < rCOUNT) {
            char temp[255]{};
            fscanf_s(reader, "%s", &temp, 254);
            massR[i].name = temp;
            fscanf_s(reader, "%d", &massR[i].numBook);
            i++;
        }

        fclose(reader);

        return massR;
    }
    else if (Num == 2) {
        cout << "Окей, файл не сохранен." << endl;
        return 0;
    }
    else {
        cout << "Ошибка..." << endl;
    }

}

void printBooks(const Book books[]) {
    FILE* book;

    if (fopen_s(&book, pathB, "w") != NULL) {
        cout << "The file cannot be opened for " << pathB << "\n";
        return;
    }

    fscanf_s(book, "%u", &bCOUNT);

    for (int i = 0; i < bCOUNT; i++) {
        cout << "Название: " << books[i].title << endl;
        cout << "Автор: " << books[i].author << endl;
        cout << "Издательство: " << books[i].amount << endl;
    }
}

void printReader(const Reader read[]) {
    FILE* reads{};

    if (fopen_s(&reads, pathR, "w") != NULL) {
        cout << "The file cannot be opened for " << pathR << "\n";
        return;
    }

    fscanf_s(reads, "%u", &rCOUNT);

    for (int i = 0; i < rCOUNT; i++) {
        cout << "Имя: " << read[i].name << endl;
        cout << "Количество книг: " << read[i].numBook << endl;
    }
}

void editBook(Book& book) {
    int num;
    enum { titleB = 1, autorB = 2, countBB = 3, exitB = 0 };

    do {
        cout << "1. Редактировать название книги" << endl;
        cout << "2. Редактировать автора книги" << endl;
        cout << "3. Редактировать количество книг на складе" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> num;

        switch (num)
        {
        case titleB:
            cout << "Введите название книги: ";
            getline(cin, book.title);
            while (book.title.empty()) {
                cout << "Название книги не может быть пустым! Введите название книги: ";
                getline(cin, book.title);
            }
            break;
        case autorB:
            cout << "Введите имя автора: ";
            getline(cin, book.author);
            while (book.author.empty()) {
                cout << "Имя автора не может быть пустым! Введите имя автора: ";
                getline(cin, book.author);
            }
            break;
        case countBB:
            cout << "Введите количество книг: ";
            while (!(cin >> book.amount) || book.amount < 0) {
                cout << "Количество книг должно быть положительным числом! Введите количество книг: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        case exitB:
            return;
        default:
            cout << "Ошибка...";
            break;
        }
    } while (num != 0);
}

void editReader(Reader& read) {
    int num;
    enum {
        nameR = 1, countBR = 2, exitR = 0
    };

    do {
        cout << "1. Редактировать имя автора" << endl;
        cout << "2. Редактировать количество взятых книг" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> num;

        switch (num) {
        case nameR: {
            string name;
            cout << "Введите имя читателя: ";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            while (name.empty()) {
                cout << "Имя читателя не может быть пустым. Введите имя читателя:\n";
                getline(cin, name);
            }

            read.name = name;
            break;
        }
        case countBR: {
            int countBR;
            cout << "Введите количество взятых книг: ";
            cin >> countBR;

            while (cin.fail() || countBR < 0) {
                cout << "Количество книг должно быть целым положительным числом. Попробуйте ещё раз:\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> countBR;
            }

            read.numBook = countBR;
            break;
        }
        case exitR:
            return;
        default:
            cout << "Ошибка...";
            break;
        }
    } while (num != 0);
}

void findBookByTitle(Book* books, const string& title) {
    bool found = false;

    for (int i = 0; i < bCOUNT; i++) {
        if (books[i].title == title) {
            printBooks(books);
            found = true;
        }
    }

    if (!found) {
        cout << "Книга с названием \"" << title << "\" не найдена." << endl;
    }
}

void findReaderByName(Reader* read, const string& name) {
    bool found = false;

    for (int i = 0; i < rCOUNT; i++) {
        if (read[i].name == name) {
            printReader(read);
            found = true;
        }
    }

    if (!found) {
        cout << "Читатель с именем \"" << name << "\" не найден." << endl;
    }
}

void findBookByAuthor(Book* books, string author) {
    bool found = false;

    for (int i = 0; i < bCOUNT; i++) {
        if (books[i].title == author) {
            printBooks(books);
            found = true;
        }
    }

    if (!found) {
        cout << "Книга с автором \"" << author << "\" не найдена." << endl;
    }
}

void sortByTitleHelper(Book* books, int left, int right) {
    if (left >= right) {
        return;
    }

    int supIndex = (left + right) / 2;
    Book supValue = books[supIndex];

    int i = left;
    int j = right;

    while (i <= j) {
        while (books[i].title < supValue.title) {
            i++;
        }

        while (books[j].title > supValue.title) {
            j--;
        }

        if (i <= j) {
            swap(books[i], books[j]);
            i++;
            j--;
        }
    }

    sortByTitleHelper(books, left, j);
    sortByTitleHelper(books, i, right);
}

void sortBooksByTitle() {
    Book* books = read_saveBook();

    if (books == nullptr) {
        return;
    }

    sortByTitleHelper(books, 0, bCOUNT - 1);

    printBooks(books);

    FILE* book;

    if (fopen_s(&book, pathB, "w") != NULL) {
        cout << "The file cannot be opened for " << pathB << "\n";
        return;
    }

    int Num = save_button();

    if (Num == 1) {
        fprintf(book, "%d\n", bCOUNT);

        for (int i = 0; i < bCOUNT; i++) {
            fprintf(book, "%s %s %d\n", books[i].title.c_str(), books[i].author.c_str(), books[i].amount);
        }

        fclose(book);

        delete[] books;
    }
    else if (Num == 2) {
        cout << "Окей, файл не сохранен." << endl;
        fclose(book);
        return;
    }
    else {
        cout << "Ошибка..." << endl;
    }
}

void sortByAuthorHelper(Book* books, int left, int right) {
    if (left >= right) {
        return;
    }

    int supIndex = (left + right) / 2;
    Book supValue = books[supIndex];

    int i = left;
    int j = right;

    while (i <= j) {
        while (books[i].author < supValue.author) {
            i++;
        }

        while (books[j].author > supValue.author) {
            j--;
        }

        if (i <= j) {
            swap(books[i], books[j]);
            i++;
            j--;
        }
    }

    sortByAuthorHelper(books, left, j);
    sortByAuthorHelper(books, i, right);
}

void sortBooksByAuthor() {
    Book* books = read_saveBook();

    if (books == nullptr) {
        return;
    }

    sortByAuthorHelper(books, 0, bCOUNT - 1);

    printBooks(books);

    FILE* book;

    if (fopen_s(&book, pathB, "w") != NULL) {
        cout << "The file cannot be opened for " << pathB << "\n";
        return;
    }

    int Num = save_button();

    if (Num == 1) {
        fprintf(book, "%d\n", bCOUNT);

        for (int i = 0; i < bCOUNT; i++) {
            fprintf(book, "%s %s %d\n", books[i].title.c_str(), books[i].author.c_str(), books[i].amount);
        }

        fclose(book);

        delete[] books;
    }
    else if (Num == 2) {
        cout << "Окей, файл не сохранен." << endl;
        fclose(book);
        return;
    }
    else {
        cout << "Ошибка..." << endl;
    }
}

void sortReaderByNameHelper(Reader* readers, int left, int right) {
    if (left >= right) {
        return;
    }

    int supIndex = (left + right) / 2;
    Reader supValue = readers[supIndex];

    int i = left;
    int j = right;

    while (i <= j) {
        while (readers[i].name < supValue.name) {
            i++;
        }

        while (readers[j].name > supValue.name) {
            j--;
        }

        if (i <= j) {
            swap(readers[i], readers[j]);
            i++;
            j--;
        }
    }

    sortReaderByNameHelper(readers, left, j);
    sortReaderByNameHelper(readers, i, right);
}

void sortReaderByName() {
    Reader* readers = read_saveRead();

    if (readers == nullptr) {
        return;
    }

    sortReaderByNameHelper(readers, 0, rCOUNT - 1);

    printReader(readers);

    FILE* reader;

    if (fopen_s(&reader, pathR, "w") != NULL) {
        cout << "The file cannot be opened for " << pathR << "\n";
        return;
    }

    int Num = save_button();

    if (Num == 1) {
        fprintf_s(reader, "%d\n", rCOUNT);

        for (int i = 0; i < rCOUNT; i++) {
            fprintf_s(reader, "%s %d\n", readers[i].name.c_str(), readers[i].numBook);
        }

        fclose(reader);

        delete[] readers;
    }
    else if (Num == 2) {
        cout << "Окей, файл не сохранен." << endl;
        fclose(reader);
        return;
    }
    else {
        cout << "Ошибка..." << endl;
    }
}

void new_book(Book*& books) {

    Book newBook;

    cin.ignore();
    cout << "Введите название книги:\n";
    getline(cin, newBook.title);

    while (newBook.title.empty()) {
        cout << "Название книги не может быть пустым. Введите название книги:\n";
        getline(cin, newBook.title);
    }

    cout << "Введите имя автора книги:\n";
    getline(cin, newBook.author);

    while (newBook.author.empty()) {
        cout << "Имя автора книги не может быть пустым. Введите имя автора книги:\n";
        getline(cin, newBook.author);
    }

    cout << "Введите количество книг:\n";
    while (!(cin >> newBook.amount) || newBook.amount < 1) {
        cout << "Количество книг должно быть целым положительным числом. Попробуйте ещё раз:\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Book* newBooks = new Book[bCOUNT + 1];

    for (int i = 0; i < bCOUNT; i++) {
        newBooks[i] = books[i];
    }

    newBooks[bCOUNT] = newBook;

    bCOUNT++;

    delete[] books;

    books = newBooks;

    FILE* book;

    if (fopen_s(&book, pathB, "w") != NULL) {
        cout << "The file cannot be opened for " << pathB << "\n";
        return;
    }

    fprintf_s(book, "%u\n", bCOUNT);

    for (int i = 0; i < bCOUNT; i++) {
        fprintf_s(book, "%s\n", books[i].title.c_str());
        fprintf_s(book, "%s\n", books[i].author.c_str());
        fprintf_s(book, "%d\n", books[i].amount);
    }

    fclose(book);

    cout << "Книга успешно добавлена ​​в библиотеку!\n";
}

void delete_book(Book*& books) {
    string titleToDelete;

    cout << "Введите название книги для удаления:\n";
    getline(cin, titleToDelete);

    int indexToDelete = -1;

    for (int i = 0; i < bCOUNT; i++) {
        if (books[i].title == titleToDelete) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        cout << "Книга \"" << titleToDelete << "\"  не найдена в библиотеке!\n";
        return;
    }

    Book* newBooks = new Book[bCOUNT - 1];

    int j = 0;

    for (int i = 0; i < bCOUNT; i++) {
        if (i != indexToDelete) {
            newBooks[j] = books[i];
            j++;
        }
    }

    bCOUNT--;

    delete[] books;

    books = newBooks;

    FILE* book;

    if (fopen_s(&book, pathB, "w") != NULL) {
        cout << "The file cannot be opened for " << pathB << "\n";
        return;
    }

    fprintf_s(book, "%u\n", bCOUNT);

    for (int i = 0; i < bCOUNT; i++) {
        fprintf_s(book, "%s\n", books[i].title.c_str());
        fprintf_s(book, "%s\n", books[i].author.c_str());
        fprintf_s(book, "%d\n", books[i].amount);
    }

    fclose(book);

    cout << "Книга \"" << titleToDelete << "\" была успешно удалена из библиотеки!\n";
}

void new_reader(Reader*& massR) {
    string name;
    cout << "Введите имя читателя: ";
    getline(cin, name);

    while (name.empty()) {
        cout << "Имя не может быть пустым! Введите имя читателя заново: ";
        getline(cin, name);
    }

    int numBook;
    cout << "Введите количество взятых книг: ";
    cin >> numBook;

    while (cin.fail() || numBook < 0) {
        cout << "Количество книг должно быть положительным! Введите количество книг заново: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> numBook;
    }

    Reader newReader = { name, numBook };

    Reader* newReaders = new Reader[rCOUNT + 1];

    for (int i = 0; i < rCOUNT; i++) {
        newReaders[i] = massR[i];
    }

    newReaders[rCOUNT] = newReader;

    delete[] massR;

    massR = newReaders;

    rCOUNT++;
}

void delete_reader(Reader* massR) {
    int index;
    cout << "Введите номер читателя";
    cin >> index;

    if (index < 0 || index >= rCOUNT) {
        cout << "Неверный номер!" << endl;
        return;
    }

    for (int i = index; i < rCOUNT - 1; i++) {
        massR[i] = massR[i + 1];
    }

    rCOUNT--;

    Reader* temp = new Reader[rCOUNT]{};

    for (int i = 0; i < rCOUNT; i++) {
        temp[i] = massR[i];
    }

    delete[] massR;

    massR = temp;

    FILE* reader;
    if (fopen_s(&reader, pathR, "w") != NULL) {
        cout << "The file cannot be opened for " << pathR << endl;
        return;
    }

    fprintf_s(reader, "%d\n", rCOUNT);

    for (int i = 0; i < rCOUNT; i++) {
        fprintf_s(reader, "%s %d\n", massR[i].name.c_str(), massR[i].numBook);
    }

    fclose(reader);
}

void report(Book* books, Reader* readers) { //спросить как сделать правильно у кого какая книга
    FILE* count;

    if (fopen_s(&count, pathC, "w") != NULL) {
        cout << "The file cannot be opened for " << pathC << "\n";
        return;
    }

    int book_inLib{};
    int book_inRead{};

    for (int i = 0; i < bCOUNT; i++) {
        book_inLib += books[i].amount;
    }

    for (int i = 0; i < rCOUNT; i++) {
        book_inRead += readers[i].numBook;
    }

    fprintf(count, "Количество книг в библиотеке: %d\n", book_inLib);
    fprintf(count, "Количество книг: %d\n", bCOUNT);
    fprintf(count, "Количество читателей: %d\n", rCOUNT);
    fprintf(count, "Количество книг у читателей: %d\n", book_inRead);

    fclose(count);
}

void menu() {
    cout << "Приветствую!!!" << endl; //вы попали в библиотеку или что-то типо
    cout << "Это мини-библиотека" << endl;
    cout << "" << endl;

    system("pause");

    int num;
    enum{ReadB = 1, ReadR = 2, NewB = 3, DelB = 4, EditB = 5, NewR = 6, DelR = 7, EditR = 8, SortBautor = 9, SortBtitle = 10, SortRname = 11, PrintB = 12, PrintR = 13, Report = 14, exit = 15};

    Book* books = nullptr;
    Reader* read = nullptr;

    while (true) {
        cout << "1. Считать все книги из файла" << endl;
        cout << "2. Считать всех читателей из файла" << endl;
        cout << "3. Добавить новую книгу" << endl;
        cout << "4. Удалить книгу" << endl;
        cout << "5. Редактировать книгу" << endl;
        cout << "6. Добавить нового читателя" << endl;
        cout << "7. Удалить читателя" << endl;
        cout << "8. Редактировать читателя" << endl;
        cout << "9. Отсортировать книги по автору" << endl;
        cout << "10. Отсортировать книги по названию" << endl;
        cout << "11. Отсортировать читателей по имени" << endl;
        cout << "12. Печать всех книг" << endl;
        cout << "13. Печать всех читателей" << endl;
        cout << "14. Отчет" << endl;
        cout << "15. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> num;

        switch (num)
        {
        case ReadB:
            read_saveBook();
            break;
        case ReadR:
            read_saveRead();
            break;
        case NewB:
            new_book(books);
            break;
        case DelB:
            delete_book(books);
            break;
        case EditB:
            editBook(*books);
            break;
        case NewR:
            new_reader(read);
            break;
        case DelR:
            delete_reader(read);
            break;
        case EditR:
            editReader(*read);
            break;
        case SortBautor:
            sortBooksByAuthor();
            break;
        case SortBtitle:
            sortBooksByTitle();
            break;
        case SortRname:
            sortReaderByName();
            break;
        case PrintB:
            printBooks(books);
            break;
        case PrintR:
            printReader(read);
            break;
        case Report:
            report(books, read);
            break;
        case exit:
            return;
        default:
            cout << "Ошибка..." << endl;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    menu();

    return 0;
}
// многофайловость!!!