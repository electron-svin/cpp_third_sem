#include<iostream>

class S {
public:
    S() = delete;
    S(const S&) = default;
    S& operator=(const S&) = delete;
    S(int) {};
};

template <typename T>
class Array {
public:

    explicit Array(size_t size, const T& value) : m_size(size) {
        //new char[N * sizeof(T)]
        m_beg = (T*) new char[sizeof(T) * size];
        for (size_t i = 0; i < m_size; i++) {
            new (m_beg + i) T(value);
        }
    }

    Array(const Array& other) {
        m_size = other.m_size;
        m_beg = new T[other.m_size];
        for (size_t i = 0; i < other.m_size; i++) {
            *(m_beg + i)(*(other.m_beg + i));
        }
    }

    Array(Array&& other) {
        m_size = other.m_size;
        m_beg = other.m_beg;
        other.m_size = 0;
        other.m_beg = nullptr;
    }

    ~Array() {
        if (m_size == 0) { return; }
        delete[] m_beg;
    }
    Array& operator=(const Array& other) {
        Array tmp(other);
        std::swap(tmp.m_size, m_size);
        std::swap(tmp.m_beg, m_beg);
        return *this;
    }

    Array& operator=(Array&& other) {
        Array tmp = std::move(other);
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
    size_t m_size;
    T* m_beg;
};


int main() {

    Array<int> tmp(5, 1);
    Array<S> tmp1(5, 1);
    tmp.print();
    return 0;
}
