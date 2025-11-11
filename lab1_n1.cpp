#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    const int SIZE = 10;

    double* array = new double[SIZE];

    cout << "Заполнение массива 10 числами типа double:" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << "Введите элемент [" << i << "]: ";
        cin >> array[i];
    }

    cout << "\nСодержимое массива:" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << "array[" << i << "] = " << fixed << setprecision(2)
            << array[i] << endl;
    }

    double* startAddress = array;
    cout << "\nАдрес начала массива: " << startAddress << endl;

    cout << "\nРасстояние элементов от начала массива:" << endl;
    cout << "Элемент\tАдрес\t\tРасстояние (байты)\tРасстояние (элементы)" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int i = 0; i < SIZE; ++i) {
        double* elementAddress = &array[i];
        size_t byteDistance = reinterpret_cast<char*>(elementAddress) - reinterpret_cast<char*>(startAddress);
        size_t elementDistance = elementAddress - startAddress;

        cout << "array[" << i << "]\t" << elementAddress << "\t"
            << byteDistance << "\t\t\t" << elementDistance << endl;
    }

    delete[] array;

    return 0;
}
