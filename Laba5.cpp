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

int main() {
    setlocale(LC_ALL, "ru");
    // Создание стека типа int
    Stack<int> intStack;

    // Добавление элементов
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    // Вывод размера стека
    std::cout << "Размер стека: " << intStack.getSize() << std::endl;

    // Получение верхнего элемента без удаления
    std::cout << "Верхний элемент стека: " << intStack.top() << std::endl;

    // Извлечение элементов из стека
    while (!intStack.isEmpty()) {
        std::cout << "Извлечен элемент: " << intStack.pop() << std::endl;
    }

    return 0;
}
