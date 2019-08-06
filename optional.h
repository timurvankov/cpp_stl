#include <algorithm>
#include <cstddef>
#include <memory>
struct BadOptionalAccess {
};

template <typename T>
class Optional {
private:
    // alignas нужен для правильного выравнивания блока памяти
    alignas(T) unsigned char data[sizeof(T)];
    bool defined = false;

    void destroy() {
        if (defined)
            reinterpret_cast<T*>(data)->~T();
        defined = false;
    }

public:
    Optional() = default;
    explicit Optional(const T& elem) {
        if (defined)
            value() = elem;
        else
            new (data) T(elem);
        defined = true;
    }

    Optional(T && elem) {
        if (defined)
            value() = std::move(elem);
        else
            new (data) T(std::move(elem));
        defined = true;
    }
    Optional(const Optional& other) {
        if (other.has_value()) {
            if (defined)
                value() = other.value();
            else
                new (data) T(other.value());
            defined = true;
        } else {
            destroy();
        }
    }

    Optional& operator=(const Optional& other) {
        if (other.has_value()) {
            if (defined)
                value() = other.value();
            else
                new (data) T(other.value());
            defined = true;
        } else {
            destroy();
        }
        return *this;
    }
    Optional& operator=(const T& elem) {
        if (defined)
            value() = elem;
        else
            new (data) T(elem);
        defined = true;
        return *this;
    }
    Optional& operator=(T&& elem) {
        if (defined)
            value() = std::move(elem);
        else
            new (data) T(std::move(elem));
        defined = true;
        return *this;
    }

    bool has_value() const { return defined; }

    T& operator*() { return *reinterpret_cast<T*>(data); }
    const T& operator*() const { return *reinterpret_cast<const T*>(data); }

    T* operator->() { return reinterpret_cast<T*>(data); }
    const T* operator->() const { return reinterpret_cast<const T*>(data); }

    T& value() {
        if (has_value())
            return *reinterpret_cast<T*>(data);
        throw BadOptionalAccess();
    }
    const T& value() const {
        if (has_value())
            return *reinterpret_cast<const T*>(data);
        throw BadOptionalAccess();
    }

    void reset() {
        destroy();
    }

    ~Optional() {
        reset();
    }
};