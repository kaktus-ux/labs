#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;
enum class BookType {
	FICTION,
	TECHNICAL
};

class Book {
private:
	string author;
	string title;
	BookType type;

public:
	Book(const string& auth, const string& titl, BookType t) {
		if (auth.empty() || titl.empty()) {
			throw invalid_argument("Автор и название книги не могут быть пустыми");
		}
		author = auth;
		title = titl;
		type = t;
	}

	string getAuthor() const { return author; }
	string getTitle() const { return title; }
	BookType getType() const { return type; }

	void printInfo() const {
		string typeStr = (type == BookType::FICTION) ? "Художественная" : "Техническая";
		cout << "Автор: " << author << ", Название: " << title
			<< ", Тип: " << typeStr << endl;
	}
};

class Library {
private:
	vector<Book*> books;

public:
	Library() = default;

	void addBook(Book* book) {
		books.push_back(book);
	}

	void countBooksWithSwitch() const {
		int fictionCount = 0;
		int technicalCount = 0;

		for (const auto& book : books) {
			switch (book->getType()) {
			case BookType::FICTION:
				fictionCount++;
				break;
			case BookType::TECHNICAL:
				technicalCount++;
				break;
			}
		}

		cout << "\nПодсчет со switch:" << endl;
		cout << "Художественная литература: " << fictionCount << " книг" << endl;
		cout << "Техническая литература: " << technicalCount << " книг" << endl;
	}

	void countBooksWithoutSwitch() const {
		int fictionCount = 0;
		int technicalCount = 0;

		for (const auto& book : books) {
			if (book->getType() == BookType::FICTION) {
				fictionCount++;
			}
			else {
				technicalCount++;
			}
		}

		cout << "\nПодсчет без switch:" << endl;
		cout << "Художественная литература: " << fictionCount << " книг" << endl;
		cout << "Техническая литература: " << technicalCount << " книг" << endl;
	}

	void printAllBooks() const {
		cout << "\nВсе книги в библиотеке:" << endl;
		for (size_t i = 0; i < books.size(); ++i) {
			cout << i + 1 << ". ";
			books[i]->printInfo();
		}
	}

	~Library() {
		for (auto& book : books) {
			delete book;
		}
		books.clear();
	}

	Library(const Library&) = delete;
	Library& operator=(const Library&) = delete;
};

int main() {
	setlocale(LC_ALL, "RU");

	Library library;

	try {
		library.addBook(new Book("Альфред Адлер", "Наука жить", BookType::TECHNICAL));
		library.addBook(new Book("Дмитрий Глуховский", "Метро 2033", BookType::FICTION));
		library.addBook(new Book("Джордж Клейсон", "Самый богатый человек в вавилоне", BookType::FICTION));
		library.addBook(new Book("Доктор Джо Диспенза", "Сила подсознания", BookType::FICTION));

		library.printAllBooks();

		library.countBooksWithSwitch();

		library.countBooksWithoutSwitch();

	}
	catch (const std::exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
		return 1;
	}

	return 0;
}
