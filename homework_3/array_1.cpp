#include <iostream>
#include <cstring>
#include  <algorithm>


template <typename T>
class Array {
public:

    explicit Array(size_t size, const T& value) : m_size(size) {
        m_beg = new T[size];
        for (size_t i = 0; i < m_size; i++) {
            m_beg[i] = value;
        }
    }

    Array(const Array& other) : Array(other.m_size) {
        std::memcpy(m_beg, other.m_beg, m_size * sizeof(T));
        std::copy(other.m_beg, other.m_beg + other.m_size, m_beg);
    }
   
    Array(Array&& other) noexcept : m_size(other.m_size), m_beg(other.m_beg) {
        other.m_size = 0;
        other.m_beg = nullptr;
    }
    
    ~Array() {
        if (m_size == 0) { return; }
        delete[] m_beg;
    }

    Array& operator=(const Array& other) {
        if (&other == this) {
            return *this;
        }
        Array tmp(other);
        std::swap(tmp.m_size, m_size);
        std::swap(tmp.m_beg, m_beg);
        return *this;
    }

    Array& operator=(Array&& other) {
        if (&other == this) {
            return *this;
        }

        delete[] m_beg;
        size = other.size;
        m_beg = other.m_beg;

        other.size = 0;
        other.m_beg = nullptr;
        return *this;
    }

    size_t size() const {
        return m_size;
    }

    T& operator[](size_t idx) {
        return m_beg[idx];
    }

    const T& operator[](size_t idx) const {
        return m_beg[idx];
    }

    void print() {
        for (size_t i = 0; i < m_size; i++) {
            std::cout << *(m_beg + i) << std::endl;
        }
    }

private:

    size_t m_size = 0;
    T* m_beg = nullptr;
};


int main() {
    Array<int> tmp(5, 1);
    int x = 42;
    Array<int> a1(10, x);
    Array<int> a2 = std::move(a1);
    tmp.print();
    return 0;
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out-1.txt ./array_1