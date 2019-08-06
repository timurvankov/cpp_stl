#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <cstring>
#include <cstddef>
#include <algorithm>

template <typename T>
class List {
public:
    class Node {
    private:
        T* ptr;
        Node* left;
        Node* right;

    public:
        Node() : ptr(nullptr), left(this), right(this) {}
        Node(T* p, Node* l, Node* r) : ptr(p), left(l), right(r) {
            if (left != nullptr) {
                left->right = this;
            } else {
                left = this;
            }
            if (right != nullptr) {
                right->left = this;
            } else {
                right = this;
            }
        }

        friend class List;
        friend class Iterator;

        ~Node() {
            left = nullptr;
            right = nullptr;
            delete ptr;
        }
    };
    class Iterator {
    private:
        Node* ptr;

    public:
        explicit Iterator(Node* new_ptr) : ptr(new_ptr) {}
        Iterator& operator++() {
            ptr = ptr->right;
            return *this;
        }
        const Iterator operator++(int) {
            auto tmp = ptr;
            ptr = ptr->right;
            return Iterator(tmp);
        }
        Iterator& operator--() {
            ptr = ptr->left;
            return *this;
        }
        const Iterator operator--(int) {
            auto tmp = ptr;
            ptr = ptr->left;
            return Iterator(tmp);
        }

        bool operator==(const Iterator other) const {
            return ptr == other.ptr;
        }
        bool operator!=(const Iterator other) const {
            return !(*this == other);
        }

        T& operator*() {
            return *(ptr->ptr);
        }
    };

private:
    Node* back;
    size_t listSize;

public:
    List<T>() : back(new Node()), listSize(0) {}

    explicit List<T>(const List<T>& new_list) : back(new Node()), listSize(0) {
        auto now = new_list.begin();
        while (now != new_list.end()) {
            push_back(*now);
            ++now;
        }
    }

    List<T>& operator=(const List<T>& new_list) {
        while (listSize != 0)
            pop_back();
        auto now = new_list.begin();
        while (now != new_list.end()) {
            push_back(*now);
            ++now;
        }
        return *this;
    }

    void push_back(const T& e) {
        Node* tmp = new Node(new T(e), back->left, back);
        back->left = tmp;
        tmp->left->right = tmp;
        listSize++;
    }
    void push_front(const T& e) {
        Node* tmp = new Node(new T(e), back, back->right);
        back->right = tmp;
        tmp->right->left = tmp;
        listSize++;
    }
    void pop_back() {
        Node* tmp = back->left;
        tmp->left->right = back;
        back->left = tmp->left;
        delete tmp;
        listSize--;
    }
    void pop_front() {
        Node* tmp = back->right;
        back->right = tmp->right;
        tmp->right->left = back;
        delete tmp;
        listSize--;
    }
    size_t size() const {
        return listSize;
    }

    Iterator begin() {
        return Iterator(back->right);
    }
    Iterator end() {
        return Iterator(back);
    }
    const Iterator begin() const {
        return Iterator(back->right);
    }
    const Iterator end() const {
        return Iterator(back);
    }

    ~List() {
        while (size() != 0)
            pop_back();
        delete back;
    }
};