#include <iostream>
#include <string>

using namespace std;

class Sales {
protected:
	float sales[3];

public:
	Sales() {
		for (int i = 0; i < 3; i++) {
			sales[i] = 0.0;
		}
	}

	void getSalesData() {
		cout << "Введите продажи за последние 3 месяца:" << endl;
		for (int i = 0; i < 3; i++) {
			cout << "Месяц " << i + 1 << ": ";
			cin >> sales[i];
		}
	}

	void putSalesData() const {
		cout << "Продажи за последние 3 месяца:" << endl;
		for (int i = 0; i < 3; i++) {
			cout << "Месяц " << i + 1 << ": " << sales[i] << " руб." << endl;
		}
	}
};

class Publication {
protected:
	string title;
	float price;

public:
	Publication() : title(""), price(0.0) {}

	virtual void getdata() {
		cout << "Введите название: ";
		cin.ignore();
		getline(cin, title);
		cout << "Введите цену: ";
		cin >> price;
	}

	virtual void putdata() const {
		cout << "Название: " << title << endl;
		cout << "Цена: " << price << " руб." << endl;
	}

	virtual ~Publication() {}
};

class Book : public Publication, public Sales {
private:
	int pages;

public:
	Book() : pages(0) {}

	void getdata() override {
		Publication::getdata();
		cout << "Введите количество страниц: ";
		cin >> pages;
		Sales::getSalesData();
	}

	void putdata() const override {
		Publication::putdata();
		cout << "Количество страниц: " << pages << endl;
		Sales::putSalesData();
	}
};

class Type : public Publication, public Sales {
private:
	float time;  

public:
	Type() : time(0.0) {}

	void getdata() override {
		Publication::getdata();
		cout << "Введите время записи в минутах: ";
		cin >> time;
		Sales::getSalesData();
	}

	void putdata() const override {
		Publication::putdata();
		cout << "Время записи: " << time << " мин" << endl;
		Sales::putSalesData();
	}
};

int main() {
	setlocale(LC_ALL, "RU");
	Book book;
	Type audio;

	cout << "Введите данные книги" << endl;
	book.getdata();

	cout << "\nВведите данные аудиозаписи" << endl;
	audio.getdata();

	cout << "\nИнформация о книге:" << endl;
	book.putdata();

	cout << "\nИнформация об аудиозаписи:" << endl;
	audio.putdata();

	return 0;
}
