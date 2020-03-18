#include <iostream>

class safe_long_long_t {
   private:
    long long value;

   public:
    safe_long_long_t(long long a) : value(a) {}

    long long Value() {
        return value;
    }

    void operator=(safe_long_long_t a) {
        value = a.value;
    }

    safe_long_long_t operator++(int i) {
        safe_long_long_t temp = value;
        value = value + 1;
        return temp;
    }

    safe_long_long_t& operator++() {
        value = value + 1;
        return *this;
    }

    safe_long_long_t operator+(safe_long_long_t b) {
        return safe_long_long_t(value + b.value);
    }

    safe_long_long_t operator-(safe_long_long_t b) {
        return safe_long_long_t(value - b.value);
    }

    bool operator<(safe_long_long_t b) {
        return value < b.value;
    }

    bool operator>(safe_long_long_t b) {
        return value > b.value;
    }

    bool operator!=(safe_long_long_t b) {
        return value != b.value;
    }

    bool operator==(safe_long_long_t b) {
        return value == b.value;
    }
};

std::ostream& operator<<(std::ostream& out, safe_long_long_t a) {
    out << a.Value();
    return out;
}

std::istream& operator>>(std::istream& in, safe_long_long_t a) {
    in >> a.Value();
    return in;
}
int main() {
    safe_long_long_t a = 2;
    std::cout << a << std::endl;  // 2
    safe_long_long_t b = safe_long_long_t(6);
    std::cout << b << std::endl;         // 6
    std::cout << (a + b) << std::endl;   // 8
    std::cout << (b - a) << std::endl;   // 4
    std::cout << (b > a) << std::endl;   // 1
    std::cout << (b + 1) << std::endl;   // 7
    std::cout << (++b) << std::endl;     // не работает
    std::cout << (b++) << std::endl;     // 7
    std::cout << b << std::endl;         // 8
    std::cout << (a == 2) << std::endl;  // 1
    std::cout << (a > 3);                // 0
    return 0;
}
