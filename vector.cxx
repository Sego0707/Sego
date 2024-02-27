#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    MyVector() : data(nullptr), capacity(0), size(0) {}

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            reserve(new_capacity);
        }
        data[size++] = value;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = std::move(data[i]);
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }
};

int main() {
    MyVector<int> vec;

    // Add elements to the vector
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Access elements by index
    std::cout << "Element at index 1: " << vec[1] << std::endl;

    // Output size and capacity
    std::cout << "Size: " << vec.getSize() << std::endl;
    std::cout << "Capacity: " << vec.getCapacity() << std::endl;

    // Clear the vector
    vec.clear();
    std::cout << "Size after clear: " << vec.getSize() << std::endl;
    std::cout << "Capacity after clear: " << vec.getCapacity() << std::endl;

    return 0;
}

