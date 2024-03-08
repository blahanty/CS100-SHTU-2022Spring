
// DO NOT MODIFY THE CODE BELOW
#include <cstddef>

class Array {
public:
    Array();

    explicit Array(std::size_t n);

    explicit Array(int *begin, int *end);

    Array(const Array &other);

    Array &operator=(const Array &other);

    ~Array();

    int &at(std::size_t n);

    const int &at(std::size_t n) const;

    std::size_t size() const;

    bool empty() const;

    void clear();

    Array slice(std::size_t l, std::size_t r, std::size_t s = 1) const;

private:
    std::size_t m_size;
    int *m_data;
};

// YOUR CODE STARTS HERE
Array::Array() {
    m_size = 0;
    m_data = nullptr;
}

Array::Array(std::size_t n) {
    m_size = n;
    m_data = new int[m_size];
    for (int i = 0; i < m_size; i++)
        m_data[i] = 0;
}

Array::Array(int *begin, int *end) {
    m_size = std::size_t(end - begin);
    m_data = new int[m_size];
    for (int i = 0; i < m_size; i++)
        m_data[i] = begin[i];
}

Array::Array(const Array &other) {
    m_size = other.m_size;
    m_data = new int[m_size];
    for (int i = 0; i < m_size; i++)
        m_data[i] = other.m_data[i];
}

Array &Array::operator=(const Array &other) {
    if (this != &other) {
        delete[] m_data;
        m_size = other.m_size;
        m_data = new int[m_size];
        for (int i = 0; i < m_size; i++)
            m_data[i] = other.m_data[i];
    }
    return *this;
}

Array::~Array() {
    delete[] m_data;
}

int &Array::at(std::size_t n) {
    return m_data[n];
}

const int &Array::at(std::size_t n) const {
    return m_data[n];
}

std::size_t Array::size() const {
    return m_size;
}

bool Array::empty() const {
    if (m_size)
        return false;
    else
        return true;
}

void Array::clear() {
    m_size = 0;
    delete[] m_data;
    m_data = nullptr;
}

Array Array::slice(std::size_t l, std::size_t r, std::size_t s) const {
    std::size_t size = 0;
    std::size_t right = m_size;
    if (r <= right)
        right = r;
    if (l < right)
        size = (right - l - 1) / s + 1;
    Array arr(size);
    for (int i = 0; i < arr.m_size; i++)
        arr.m_data[i] = m_data[l + s * i];
    return arr;
}

// YOUR CODE ENDS HERE

int main() {
    // You can test your implementation here, but we will replace the main function on OJ.
    return 0;
}