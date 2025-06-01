#pragma once
template <typename T>
class BaseSingleton {
public:
    static T& GetInstance() {
        static T instance;
        return instance;
    }

protected:
    BaseSingleton() = default;
    virtual ~BaseSingleton() = default;

    BaseSingleton(const BaseSingleton&) = delete;
    BaseSingleton& operator=(const BaseSingleton&) = delete;
};