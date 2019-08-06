#include <iostream>

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* count;

public:
    SharedPtr() noexcept : ptr(nullptr), count(new size_t(1)) {}
    SharedPtr(T* new_ptr) noexcept : ptr(nullptr), count(new size_t(1)) {
        if (new_ptr != nullptr)
            ++(*count);
        ptr = new_ptr;
    }
    SharedPtr(const SharedPtr& other) noexcept : ptr(nullptr) {
        count = other.count;
        if (other.ptr != nullptr)
            ++(*count);
        ptr = other.ptr;
    }

    void swap(SharedPtr& other) noexcept {
        std::swap(ptr, other.ptr);
        std::swap(count, other.count);
    }
    void reset(T* new_ptr) noexcept {
        if (*count > 1)
            --(*count);
        if (*count == 1) {
            delete ptr;
            delete count;
        }
        count = new size_t(1);
        if (new_ptr != nullptr)
            ++(*count);
        ptr = new_ptr;
    }

    SharedPtr(SharedPtr&& other) noexcept {
        swap(other);
        other.count = new size_t(1);
        other.ptr = nullptr;
    }

    SharedPtr& operator=(T* new_ptr) noexcept {
        reset(new_ptr);
        return *this;
    }
    SharedPtr& operator=(const SharedPtr& other) noexcept {
        SharedPtr<T>(other).swap(*this);
        return *this;
    }
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        SharedPtr<T>(std::move(other)).swap(*this);
        return *this;
    }

    T& operator*() noexcept { return *ptr; }
    const T& operator*() const noexcept { return *ptr; }
    T* operator->() const noexcept { return ptr; }
    T* get() const { return ptr; }
    explicit operator bool() const noexcept { return ptr != nullptr; }

    ~SharedPtr() noexcept {
        if (*count > 1)
            --(*count);
        if (*count == 1) {
            delete ptr;
            delete count;
        }
        count = new size_t(1);
        delete count;
    }
};