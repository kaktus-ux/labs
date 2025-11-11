#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class ProgramError {
private:
	string message;
public:
	ProgramError(const string& msg) : message(msg) {}
	virtual ~ProgramError() {}
	virtual const string& what() const { return message; }
};

class OutOfMemoryError : public ProgramError {
public:
	OutOfMemoryError() : ProgramError("Недостаточно памяти.") {}
};


class FileOperationError : public ProgramError {
public:
	FileOperationError(const string& type) :
		ProgramError("Ошибка " + type + " файла.") {}
};

template <typename T>
class PointerArray {
private:
	T** data;
	size_t size;

public:
	PointerArray(size_t initialSize) : size(initialSize) {
		if (size == 0) {
			data = nullptr;
			return;
		}

		try {
			data = new T*[size];
		}
		catch (const std::bad_alloc&) {
			throw OutOfMemoryError();
		}

		for (size_t i = 0; i < size; ++i) {
			data[i] = nullptr;
		}
	}

	~PointerArray() {
		if (data != nullptr) {
			f­or (size_t i = 0; i < size; ++i) {
				delete data[i];
			}
			delete[] data;
			data = nullptr;
		}
	}

	T*& operator[](size_t index) {­
		if (index >= size) {
			throw std::logic_error("Ошибка индекса: " + to_string(index) +
				" выходит за границы [0, " + to_string(size - 1) + "].");
		}
		return data[index];
	}

	size_t getSize() const { return size; }
};

class Item {
private:
	string name;
public:
	Item(const string& n) : name(n) {
		cout << "Конструктор Item: " << name << endl;
	}
	~Item() {
		cout << "Деструктор Item: " << name << endl;
	}
	void info() const {
		cout << "Элемент: " << name << endl;
	}
};

int main() {
	setlocale(LC_ALL, "RU");

	cout << "Инициализация массива указателей" << endl;

	const size_t ARRAY_SIZE = 3;
	PointerArray<Item> itemArray(ARRAY_SIZE);

	try {
		itemArray[0] = new Item("Объект 1");
		itemArray[1] = new Item("Объект 2");
		itemArray[2] = new Item("Объект 3");

		cout << "\nПроверка доступа к элементам" << endl;
		for (size_t i = 0; i < itemArray.getSize(); ++i) {
			if (itemArray[i] != nullptr) {
				itemArray[i]->info();
			}
		}

		cout << "\nПопытка вызвать logic_error (индекс 3)" << endl;
		itemArray[3] = new Item("Этот объект не будет создан");

	}
	catch (const logic_error& e) {
		cerr << "\nlogic_error: " << e.what() << endl;
	}
	catch (const ProgramError& e) {
		cerr << "\nProgramError: " << e.what() << endl;
	}
	catch (...) {
		cerr << "\nНеизвестное исключение." << endl;
	}

	cout << "\nПроверка иерархии исключений" << endl;
	try {
		throw FileOperationError("записи");
	}
	catch (const ProgramError& e) {
		cerr << "ProgramError: " << e.what() << endl;
	}

	cout << "\nЗавершение программы" << endl;


	return 0;
}
