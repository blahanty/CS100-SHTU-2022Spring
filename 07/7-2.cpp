#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

template<typename T>
struct Slist_node {
    T value;
    Slist_node<T> *next;

    Slist_node(const T &v) : value(v), next(nullptr) {}

    Slist_node(const T &v, Slist_node<T> *p) : value(v), next(p) {}
};

template<typename T>
class Slist;

template<typename T, bool is_const>
class Slist_iterator {
public:
    using value_type = T;
    using difference_type = typename Slist<T>::difference_type;
    using pointer = typename std::conditional<is_const, const T *, T *>::type;
    using reference = typename std::conditional<is_const, const T &, T &>::type;
    using iterator_category = std::forward_iterator_tag;

private:
    using node_t = Slist_node<T>;
    using self_t = Slist_iterator<T, is_const>;
    node_t *m_cur;

public:
    Slist_iterator(node_t *pos = nullptr) : m_cur(pos) {}

    template<typename Other, typename = typename std::enable_if<
            is_const && std::is_same<Other, Slist_iterator<T, false>>::value>::type>
    Slist_iterator(const Other &oi) : m_cur(oi.base()) {}

    node_t *base() const {
        return m_cur;
    }

    self_t next() const {
        return self_t(m_cur->next);
    }

    reference operator*() const {
        return m_cur->value;
    }

    pointer operator->() const {
        return std::addressof(operator*());
    }

    self_t &operator++() {
        m_cur = m_cur->next;
        return *this;
    }

    self_t operator++(int) {
        self_t tmp = *this;
        ++*this;
        return tmp;
    }
};

template<typename T, bool C1, bool C2>
inline bool operator==(const Slist_iterator<T, C1> &lhs,
                       const Slist_iterator<T, C2> &rhs) {
    return lhs.base() == rhs.base();
}

template<typename T, bool C1, bool C2>
inline bool operator!=(const Slist_iterator<T, C1> &lhs,
                       const Slist_iterator<T, C2> &rhs) {
    return !(lhs == rhs);
}

template<typename T>
class Slist {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using const_pointer = const T *;
    using const_reference = const T &;

    using iterator = Slist_iterator<T, false>;
    using const_iterator = Slist_iterator<T, true>;

private:
    using node_t = Slist_node<T>;

    node_t *m_head;
    size_type m_length;

    void swap(Slist &other) {
        std::swap(m_head, other.m_head);
        std::swap(m_length, other.m_length);
    }

public:
    Slist() : m_head(nullptr), m_length(0) {}

    Slist(const Slist &other) : m_head(nullptr), m_length(other.m_length) {
        if (m_length) {
            m_head = new node_t(other.m_head->value);
            node_t *cur_this = m_head, *cur_other = other.m_head->next;
            for (int i = 0; i < m_length - 1; ++i) {
                cur_this->next = new node_t(cur_other->value);
                cur_this = cur_this->next;
                cur_other = cur_other->next;
            }
        }
    }

    Slist &operator=(const Slist &other) {
        Slist(other).swap(*this);
        return *this;
    }

    ~Slist() {
        clear();
        delete m_head;
    }

    void push_front(const value_type &value) {
        auto new_node = new node_t(value);
        new_node->next = m_head;
        m_head = new_node;
        ++m_length;
    }

    void pop_front() {
        if (m_head) {
            node_t *new_head = m_head->next;
            delete m_head;
            m_head = new_head;
            --m_length;
        }
    }

    iterator insert_after(const_iterator pos, const value_type &value) {
        auto *tar = new node_t(value);
        tar->next = pos.next().base();
        pos.base()->next = tar;
        iterator ins(tar);
        ++m_length;
        return ins;
    }

    void erase_after(const_iterator pos) {
        if (pos.base()->next) {
            node_t *new_next = pos.next().base()->next;
            delete pos.base()->next;
            pos.base()->next = new_next;
            --m_length;
        }
    }

    size_type size() const {
        return m_length;
    }

    bool empty() const {
        return !m_length;
    }

    void clear() {
        node_t *original_head;
        while (m_head != nullptr) {
            original_head = m_head;
            m_head = m_head->next;
            delete original_head;
        }
        m_length = 0;
    }

    iterator begin() {
        return iterator(m_head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator begin() const {
        return const_iterator(m_head);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    const_iterator cbegin() const {
        return begin();
    }

    const_iterator cend() const {
        return end();
    }
};

template<typename T>
inline bool operator==(const Slist<T> &lhs, const Slist<T> &rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
inline bool operator<(const Slist<T> &lhs, const Slist<T> &rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T>
inline bool operator!=(const Slist<T> &lhs, const Slist<T> &rhs) {
    return !(lhs == rhs);
}

template<typename T>
inline bool operator>(const Slist<T> &lhs, const Slist<T> &rhs) {
    return rhs < lhs;
}

template<typename T>
inline bool operator<=(const Slist<T> &lhs, const Slist<T> &rhs) {
    return !(lhs > rhs);
}

template<typename T>
inline bool operator>=(const Slist<T> &lhs, const Slist<T> &rhs) {
    return !(lhs < rhs);
}