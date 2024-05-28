#include <iostream>
#include <stdexcept> // Для std::out_of_range

template<typename T>
class Stack {
private:
    T* elements;     // Динамический массив элементов
    int size;        // Размер стека
    int capacity;    // Вместимость стека

public:
    // Конструктор
    Stack() : size(0), capacity(10) {
        elements = new T[capacity];
    }

    // Деструктор
    ~Stack() {
        delete[] elements;
    }

    // Метод для добавления элемента в стек
    void push(const T& item) {
        if (size >= capacity) {
            expandCapacity();
        }
        elements[size++] = item;
    }

    // Метод для извлечения элемента из стека
    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[--size];
    }

    // Метод для получения верхнего элемента без его удаления
    T& top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[size - 1];
    }

    // Метод для проверки пустоты стека
    bool isEmpty() const {
        return size == 0;
    }

    // Метод для получения размера стека
    int getSize() const {
        return size;
    }

private:
    // Приватный метод для увеличения емкости стека
    void expandCapacity() {
        capacity *= 2;
        T* newElements = new T[capacity];
        for (int i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }
};


// Функция для обработки прибытия автомобиля
void handleArrival(Stack<int>& parking, int carNumber);

// Функция для обработки отъезда автомобиля
void handleDeparture(Stack<int>& parking, int carNumber, int& removalCount);

int main() {
    setlocale(LC_ALL, "ru");
    Stack<int> parking; // Создаем стек для стоянки автомобилей
    int removalCount = 0; // Счетчик удалений для обеспечения выезда других автомобилей

    std::string command;
    int carNumber;

    std::cout << "Введите команду (A <номер> для прибытия, D <номер> для отъезда, Q для выхода):" << std::endl;

    while (true) {
        std::cin >> command;

        if (command == "Q") {
            break;
        }
        else if (command == "A") {
            std::cin >> carNumber;
            handleArrival(parking, carNumber);
        }
        else if (command == "D") {
            std::cin >> carNumber;
            handleDeparture(parking, carNumber, removalCount);
        }
        else {
            std::cout << "Неверная команда. Повторите ввод." << std::endl;
        }
    }

    return 0;
}

void handleArrival(Stack<int>& parking, int carNumber) {
    parking.push(carNumber);
    std::cout << "Автомобиль " << carNumber << " прибыл на стоянку." << std::endl;
}

void handleDeparture(Stack<int>& parking, int carNumber, int& removalCount) {
    Stack<int> temp; // Временный стек для сохранения порядка машин

    // Удаляем машины, загораживающие проезд, до тех пор, пока не достигнем нужного номера
    while (!parking.isEmpty() && parking.top() != carNumber) {
        temp.push(parking.pop());
        removalCount++;
    }

    // Если машина, которую нужно вывести, найдена, выводим сообщение о количестве удалений
    if (!parking.isEmpty() && parking.top() == carNumber) {
        std::cout << "Автомобиль " << carNumber << " выехал со стоянки после " << removalCount << " удалений." << std::endl;
        parking.pop(); // Удаляем автомобиль с вершины стека
    }
    else {
        std::cout << "Автомобиль " << carNumber << " не найден на стоянке." << std::endl;
    }

    // Возвращаем машины из временного стека обратно на основную стоянку
    while (!temp.isEmpty()) {
        parking.push(temp.pop());
    }

    removalCount = 0; // Сбрасываем счетчик удалений
}
