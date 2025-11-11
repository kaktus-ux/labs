#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

using namespace std;

template <typename T, typename... Args>
void create_and_add_to_container(
	vector<unique_ptr<class Component>>& container,
	Args&&... args
);

class Component {
protected:
	string name;
	int id;
	Component(const string& name, int id) : name(name), id(id) {
		cout << "  > Компонент создан: " << name << " (ID: " << id << ")\n";
	}

public:
	virtual ~Component() {
		cout << "  < Компонент уничтожен: " << name << " (ID: " << id << ")\n";
	}

	virtual void show_info() const = 0;

	template <typename T, typename... Args>
	friend void create_and_add_to_container(
		vector<unique_ptr<Component>>& container,
		Args&&... args
	);
};

class Part : public Component {
private:
	string material;

protected:
	Part(const string& name, int id, const string& material)
		: Component(name, id), material(material) {
		cout << "  > Деталь создана (Материал: " << material << ")\n";
	}

public:
	virtual ~Part() override {
		cout << "  < Деталь уничтожена: " << name << "\n";
	}

	void show_info() const override {
		cout << "Деталь: " << name << ", ID: " << id << ", Материал: " << material << "\n";
	}

	template <typename T, typename... Args>
	friend void create_and_add_to_container(
		vector<unique_ptr<Component>>& container,
		Args&&... args
	);­
};

class Assembly : public Component {
private:
	int num_parts;

protected:
	Assembly(const string& name, int id, int num_parts)
		: Component(name, id), num_parts(num_parts) {
		cout << "  > Сборка создана (Деталей: " << num_parts << ")\n";
	}

public:
	virtual ~Assembly() override {
		cout << "  < Сборка уничтожена: " << name << "\n";
	}

	void show_info() const override {
		cout << "Сборка: " << name << ", ID: " << id << ", Всего деталей: " << num_parts << "\n";
	}

	template <typename T, typename... Args>
	friend void create_and_add_to_container(
		vector<unique_ptr<Component>>& container,
		Args&&... args
	);
};

template <typename T, typename... Args>
void create_and_add_to_container(
	vector<unique_ptr<Component>>& container,
	Args&&... args
) {
	container.push_back(unique_ptr<T>(new T(forward<Args>(args)...)));
	cout << "Объект добавлен в контейнер.\n";
}

int main() {
	setlocale(LC_ALL, "RU");
	cout << "Начало программы" << endl;

	vector<unique_ptr<Component>> inventory;

	cout << "\nСоздание объектов с помощью фабричной функции\n";

	create_and_add_to_container<Part>(inventory, "Брус", 101, "Дерево");

	create_and_add_to_container<Assembly>(inventory, "Сифон", 201, 52);

	create_and_add_to_container<Part>(inventory, "Труба", 102, "Пластик");

	cout << "\nИнформация об инвентаре (Полиморфизм)\n";
	for (const auto& item : inventory) {
		item->show_info();
	}

	cout << "\nКонец программы (уничтожение объектов)\n";

	return 0;
}
