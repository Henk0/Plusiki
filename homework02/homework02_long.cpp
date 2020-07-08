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

    safe_long_long_t operator+=(safe_long_long_t b) {
        value += b.value;
        return value;
    }

    safe_long_long_t operator-=(safe_long_long_t b) {
        value -= b.value;
        return value;
    }

    safe_long_long_t operator*=(safe_long_long_t b) {
        value *= b.value;
        return value;
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

safe_long_long_t operator+(safe_long_long_t a, safe_long_long_t b) {
    return safe_long_long_t(a.Value() + b.Value());
}

safe_long_long_t operator*(safe_long_long_t a, safe_long_long_t b) {
    return safe_long_long_t(a.Value() * b.Value());
}

safe_long_long_t operator-(safe_long_long_t a, safe_long_long_t b) {
    return safe_long_long_t(a.Value() - b.Value());
}

bool operator<(safe_long_long_t a, safe_long_long_t b) {
    return a.Value() < b.Value();
}

bool operator>(safe_long_long_t a, safe_long_long_t b) {
    return a.Value() > b.Value();
}

bool operator>=(safe_long_long_t a, safe_long_long_t b) {
    return a.Value() >= b.Value();
}

bool operator<=(safe_long_long_t a, safe_long_long_t b) {
    return a.Value() <= b.Value();
}

bool operator!=(safe_long_long_t a, safe_long_long_t b) {
    return a.Value() != b.Value();
}

bool operator==(safe_long_long_t a, safe_long_long_t b) {
    return a.Value() == b.Value();
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
    std::cout << (b++) << std::endl;     // 6
    std::cout << b << std::endl;         // 7
    std::cout << (a == 2) << std::endl;  // 1
    std::cout << (a > 3) << std::endl;   // 0
    std::cout << (b += 4) << std::endl;  // 11
    std::cout << (b -= 6) << std::endl;  // 5
    std::cout << (b *= 3) << std::endl;  // 15
    std::cout << (b >= 6) << std::endl;  // 1
    return 0;
}
