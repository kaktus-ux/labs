#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Base {
public:
	virtual ~Base() {
		cout << "Ресурс освобожден.\n";
	}

	virtual void behave() const = 0;
	virtual unique_ptr<Base> clone() const = 0;
};

class Derived : public Base {
public:
	Derived() {
		cout << "Derived - Объект создан\n";
	}

	~Derived() override {
		cout << "Derived - Ресурс освобожден\n";
	}

	void behave() const override {
		cout << "Я нечетное число\n";
	}

	unique_ptr<Base> clone() const override {
		return make_unique<Derived>(*this);
	}
};

class ConcreteBase : public Base {
public:
	ConcreteBase() {
		cout << "Concentrate - Объект создан.\n";
	}

	~ConcreteBase() override {
		cout << "Concentrate - Ресурс освобожден.\n";
	}

	void behave() const override {
		cout << "Я четное число\n";
	}

	unique_ptr<Base> clone() const override {
		return make_unique<ConcreteBase>(*this);
	}
};

using ObjectStorage = vector<unique_ptr<Base>>;

void add(ObjectStorage& storage, const Base& obj) {
	storage.push_back(obj.clone());
	cout << "Объект скопирован и добавлен в хранилище.\n";
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(static_cast<unsigned int>(time(nullptr)));

	ObjectStorage storage;
	const int NUM_OBJECTS = 5;

	cout << "1. Создание объектов и заполнение хранилища\n";

	for (int i = 0; i < NUM_OBJECTS; ++i) {
		int random_val = rand();
		cout << "\nСоздание объекта #" << i + 1 << " (случайное число: " << random_val << "):\n";
		if (random_val % 2 == 0) {
			ConcreteBase cb;
			add(storage, cb);
		}
		else {
			Derived d;
			add(storage, d);
		}
	}

	cout << "\n2. Демонстрация полиморфизма\n";

	int index = 0;
	for (const auto& ptr : storage) {
		cout << "Объект #" << ++index << " в хранилище: ";
		ptr->behave();
	}

	cout << "\n3. Освобождение ресурсов\n";

	storage.clear();
	cout << "Все ресурсы хранилища освобождены.\n";

	return 0;
}
