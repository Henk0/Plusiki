#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <cassert>

#include "linked_list.hpp"

void test_LinkedList() {
    assert(LinkedList<void *>().empty());
}

void test_LinkedList_other_1() {
    LinkedList<double> a;

    a.push_back((double)rand() / RAND_MAX);
    a.push_back((double)rand() / RAND_MAX);
    a.push_back((double)rand() / RAND_MAX);

    LinkedList<double> b(a);
    assert(a[0] == b[0]);
    assert(a[1] == b[1]);
    assert(a[2] == b[2]);
}

void test_LinkedList_other_2() {
    LinkedList<double> a;

    double a1 = (double)rand() / RAND_MAX;
    double a2 = (double)rand() / RAND_MAX;
    double a3 = (double)rand() / RAND_MAX;

    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);

    LinkedList<double> b(std::move(a));
    assert(b[0] == a1);
    assert(b[1] == a2);
    assert(b[2] == a3);
}

void test_LinkedList_count_value() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(3, value);
    assert(a.size() == 3);
    assert(a[0] == value);
    assert(a[1] == value);
    assert(a[2] == value);
}

void test_delete_LinkedList() {
    auto a = new LinkedList<void *>;

    delete a;
    assert(a->empty());
}

void test_begin() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a;
    a.push_back(value);
    a.push_back(value + 1);

    assert(*a.begin() == value);

    *a.begin() = value + 2;
    assert(*a.begin() == value + 2);
}

void test_const_begin() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a;
    a.push_back(value);
    a.push_back(value + 1);

    assert(*static_cast<const LinkedList<double>>(a).begin() == value);

    *a.begin() = value + 2;
    assert(*a.begin() == value + 2);
}

void test_end() {
    double value = (double)rand() / RAND_MAX;

    const LinkedList<double> a(1, value);
    assert(!(a.begin() + 1 != a.end()));
}

void test_const_end() {
    double value = (double)rand() / RAND_MAX;

    const LinkedList<double> a(1, value);
    assert(!(a.begin() + 1 != a.end()));
}

void test_index_access() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(1, value);
    assert(a[0] == value);

    a[0] = value + 1;
    assert(a[0] == value + 1);
}

void test_const_index_access() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(1, value);
    const LinkedList<double> b(std::move(a));
    assert(b[0] == value);
}

void test_assign() {
    double value = (double)rand() / RAND_MAX;

    const LinkedList<double> a(1, value);
    LinkedList<double> b;

    b = a;
    assert(b.size() == 1);
    assert(b[0] == value);
}

void test_front() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(2, value);
    assert(a.front() == value);
}

void test_const_front() {
    double value = (double)rand() / RAND_MAX;

    const LinkedList<double> a(2, value);
    assert(a.front() == value);
}

void test_back() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(2, value);
    assert(a.back() == value);
}

void test_const_back() {
    double value = (double)rand() / RAND_MAX;

    const LinkedList<double> a(2, value);
    assert(a.back() == value);
}

void test_clear() {
    double value = (double)rand() / RAND_MAX;

    for (unsigned int i = 0; i < 3; ++i) {
        LinkedList<double> a(i, value);
        assert(a.size() == i);

        a.clear();
        assert(a.empty());
    }
}

void test_size() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(2, value);
    a.push_front(value);
    a.push_back(value);

    assert(a.size() == 4);
}

void test_empty() {
    const LinkedList<void *> a;
    assert(a.empty());
}

void test_insert() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a;

    a.insert(0, value);
    assert(a[0] == value);
    assert(a.size() == 1);

    a.insert(0, value);
    a.insert(1, value);
    assert(a[1] == value);
    assert(a.size() == 3);
}

void test_push_front() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(1, value + 1);

    a.push_front(value);
    assert(a[0] == value);
    assert(a.size() == 2);
}

void test_push_back() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(1, value + 1);

    a.push_back(value);
    assert(a[1] == value);
    assert(a.size() == 2);
}

void test_pop_front() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(1, value + 1);
    a.push_back(value);

    assert(a.size() == 2);

    a.pop_front();
    assert(a[0] == value);
    assert(a.size() == 1);
}

void test_pop_back() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(1, value);
    a.push_back(value + 1);
    assert(a.size() == 2);

    a.pop_back();
    assert(a[0] == value);
    assert(a.size() == 1);
}

void test_erase_it() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(1, value);
    a.push_back(value + 1);
    a.push_back(value);

    assert(a.size() == 3);

    a.erase(a.begin() + 1);
    assert(a[0] == value);
    assert(a[1] == value);
    assert(a.size() == 2);
}

void test_erase_pos() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(1, value);
    a.push_back(value + 1);
    a.push_back(value);

    assert(a.size() == 3);

    a.erase(1);
    assert(a[0] == value);
    assert(a[1] == value);
    assert(a.size() == 2);
}

void test_splice() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(3, value);
    a.push_front(value + 1);
    a.push_back(value + 1);

    assert(a.size() == 5);

    auto b = a.splice(1, 3);
    assert(b[0] == value);
    assert(b[1] == value);
    assert(b[2] == value);
    assert(a.size() == 2);
    assert(b.size() == 3);
}

void test_merge() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a(3, value), b(3, value + 1);
    a.merge(b);

    assert(a.size() == 6);
    assert(b.empty());

    assert(a[0] == value);
    assert(a[1] == value);
    assert(a[2] == value);
    assert(a[3] == value + 1);
    assert(a[4] == value + 1);
    assert(a[5] == value + 1);
}

void test_reverse() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a;
    a.push_back(value);
    a.push_back(value + 1);
    a.push_back(value + 2);

    assert(a.size() == 3);
    assert(a[0] == value);
    assert(a[1] == value + 1);
    assert(a[2] == value + 2);

    a.reverse();
    assert(a.size() == 3);
    assert(a[0] == value + 2);
    assert(a[1] == value + 1);
    assert(a[2] == value);
}

void test_swap() {
    double value = (double)rand() / RAND_MAX;

    LinkedList<double> a, b;

    a.push_back(value);
    a.push_back(value + 1);
    a.push_back(value + 2);
    assert(a.size() == 3);
    assert(a[0] == value);
    assert(a[1] == value + 1);
    assert(a[2] == value + 2);

    b.push_back(value + 3);
    b.push_back(value + 4);
    assert(b.size() == 2);
    assert(b[0] == value + 3);
    assert(b[1] == value + 4);

    a.swap(b);
    assert(a.size() == 2);
    assert(a[0] == value + 3);
    assert(a[1] == value + 4);

    assert(b.size() == 3);
    assert(b[0] == value);
    assert(b[1] == value + 1);
    assert(b[2] == value + 2);
}

int main() {
    test_LinkedList();
    test_LinkedList_other_1();
    test_LinkedList_other_2();
    test_LinkedList_count_value();
    test_delete_LinkedList();

    test_begin();
    test_end();

    test_const_begin();
    test_const_end();

    test_index_access();
    test_const_index_access();

    test_assign();

    test_front();
    test_const_front();

    test_back();
    test_const_back();

    test_clear();

    test_size();
    test_empty();

    test_insert();
    test_push_front();
    test_push_back();

    test_pop_front();
    test_pop_back();
    test_erase_it();
    test_erase_pos();

    test_splice();
    test_merge();

    test_reverse();
    test_swap();

    std::cout << "We did it boyz";

    return 0;
}