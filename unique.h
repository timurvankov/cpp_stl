#include <algorithm>
#include <cstddef>
#include <memory>
#include <tuple>

template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
private:
    std::tuple<T*, Deleter> mPair;

    T*& ptr() { return std::get<0>(mPair); }
    const T*& ptr() const { return std::get<0>(mPair); }

    Deleter& del() { return std::get<1>(mPair); }
    const Deleter& del() const { return std::get<1>(mPair); }

public:
    UniquePtr() noexcept {
        ptr() = nullptr;
    }
    explicit UniquePtr(T* obj_ptr) noexcept {
        ptr() = std::move(obj_ptr);
        obj_ptr = nullptr;
    }
    UniquePtr(UniquePtr&& other) noexcept {
        ptr() = std::move(other.ptr());
        other.ptr() = nullptr;
    }
    UniquePtr(T* obj_ptr, Deleter del) noexcept {
        mPair = std::move(std::make_tuple<T*, Deleter>(std::move(obj_ptr), std::move(del)));
        obj_ptr = nullptr;
    }
    ~UniquePtr() {
        del()(ptr());
    }

    UniquePtr(const UniquePtr& other_ptr) = delete;
    UniquePtr& operator=(const UniquePtr& other_ptr) = delete;

    UniquePtr& operator=(std::nullptr_t other_ptr) noexcept {
        del()(ptr());
        ptr() = other_ptr;
        return *this;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        del()(ptr());
        ptr() = std::move(other.ptr());
        other.ptr() = nullptr;
        return *this;
    }
    T& operator*() const { return *std::get<0>(mPair); }
    T* operator->() const noexcept { return std::get<0>(mPair); }
    T* release() noexcept {
        T* help_ptr = std::move(ptr());
        ptr() = nullptr;
        return help_ptr;
    }
    void reset(T* new_ptr) noexcept {
        del()(ptr());
        ptr() = std::move(new_ptr);
        new_ptr = nullptr;
    }
    void swap(UniquePtr& other_ptr) noexcept {
        T* help_ptr = std::move(ptr());
        ptr() = std::move(other_ptr.ptr());
        other_ptr.ptr() = std::move(help_ptr);
    }
    T* get() const noexcept {
        return std::get<0>(mPair);
    }
    explicit operator bool() const noexcept {
        return std::get<0>(mPair) != nullptr;
    }

    Deleter& get_deleter() { return del(); }
    const Deleter& get_deleter() const { return del(); }
};