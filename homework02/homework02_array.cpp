#include <iostream>

template <typename T>
class safe_c_array_t {
   private:
    int size = 0;
    T *array{};

   public:
    explicit safe_c_array_t(int size_value) {
        size = size_value;
        array = new T[size_value];
    }

    safe_c_array_t(safe_c_array_t const &arr) {
        size = arr.size;
        array = new T[size];
        for (int i = 0; i < size; i++) {
            array[i] = arr.array[i];
        }
    }

    safe_c_array_t &operator=(const safe_c_array_t &arr) {
        if (this != &arr) {
            delete[] array;
            size = arr.size;
            array = new T[size];
            for (int i = 0; i < size; i++) {
                array[i] = arr.array[i];
            }
        }
        return *this;
    }

    ~safe_c_array_t() {
        delete[] array;
    }

    T &operator[](int n) {
        return array[n];
    }
};

int main() {
    auto arr = safe_c_array_t<int>(5);
    auto arr_2 = safe_c_array_t<int>(arr);
    arr[4] = 1;
    std::cout << arr[4] << std::endl;  // 1
    std::cout << arr_2[4];             // 0
    return 0;
}