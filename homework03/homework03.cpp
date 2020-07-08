#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class linkedList {
   private:
    struct node_t {
        T value;
        node_t *next = nullptr;
        node_t *prev = nullptr;
    };
    node_t *top = new node_t;
    node_t *bottom = new node_t;
    size_t list_size;

    node_t *find(size_t pos) const {
        node_t *current;
        if (list_size / 2 > pos) {
            current = bottom->next;
            while (pos > 0) {
                current = current->next;
                pos--;
            }
        } else {
            current = top;
            while (pos != list_size) {
                current = current->prev;
                pos++;
            }
        }
        return current;
    }

   public:
    linkedList() {
        bottom->next = top;
        top->prev = bottom;
        list_size = 0;
    }

    linkedList(const linkedList<T> &list) {
        bottom->next = top;
        top->prev = bottom;
        list_size = 0;
        node_t *current = list.bottom->next;
        while (current != list.top) {
            push_back(current->value);
            current = current->next;
        }
    }

    linkedList(size_t count, T value) {
        bottom->next = top;
        top->prev = bottom;
        list_size = 0;
        for (size_t i = 0; i < count; i++) {
            push_back(value);
        }
    }

    ~linkedList() {
        clear();
        delete bottom;
        delete top;
    }

    linkedList &operator=(const linkedList &other) {
        if (this != &other) {
            clear();
            node_t *current = other.bottom->next;
            while (current != other.top) {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    T &operator[](size_t pos) {
        if (pos >= list_size) {
            std::cerr << "Index out of bound" << std::endl;
            assert(false);
        }
        return find(pos)->value;
    }

    const T &operator[](size_t pos) const {
        if (pos >= list_size) {
            std::cerr << "Index out of bound" << std::endl;
            assert(false);
        }
        return find(pos)->value;
    }

    void push_back(T value) {
        insert(list_size, value);
    }

    void push_front(T value) {
        insert(0, value);
    }

    void insert(size_t pos, const T &value) {
        if (pos > list_size) {
            std::cerr << "Index out of bound" << std::endl;
            assert(false);
        }
        auto *before = find(pos);
        auto *new_element = new node_t;
        new_element->next = before;
        new_element->prev = before->prev;
        before->prev->next = new_element;
        before->prev = new_element;
        new_element->value = value;
        list_size++;
    }

    bool empty() const {
        return list_size == 0;
    }

    T &back() {
        return top->prev->value;
    }

    const T &back() const {
        return top->prev->value;
    }

    T &front() {
        return bottom->next->value;
    }

    const T &front() const {
        return bottom->next->value;
    }

    void clear() {
        while (list_size != 0) {
            erase(0);
        }
    }

    size_t size() const {
        return list_size;
    }

    void erase(size_t pos) {
        if (pos >= list_size) {
            std::cerr << "Index out of bound" << std::endl;
            assert(false);
        }
        node_t *current = find(pos);
        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
        list_size--;
    }

    void pop_front() {
        erase(0);
    }

    void pop_back() {
        erase(list_size - 1);
    }

    linkedList splice(size_t start_pos, size_t count) {
        if (start_pos + count > list_size) {
            std::cerr << "Index out of bound" << std::endl;
            assert(false);
        }

        linkedList spliced_list = linkedList();
        node_t *first = find(start_pos);
        node_t *last = find(start_pos + count - 1);
        first->prev->next = last->next;
        last->next->prev = first->prev;
        spliced_list.top->prev = last;
        spliced_list.bottom->next = first;
        first->prev = spliced_list.bottom;
        last->next = spliced_list.top;
        this->list_size -= count;
        spliced_list.list_size += count;
        return spliced_list;
    }

    linkedList &merge(linkedList &other) {
        if (other.size() != 0) {
            node_t *first = other.bottom->next;
            node_t *last = other.top->prev;
            other.bottom->next = other.top;
            other.top->prev = other.bottom;
            top->prev->next = first;
            first->prev = top->prev;
            top->prev = last;
            last->next = top;
            list_size += other.list_size;
            other.list_size = 0;
        }
        return *this;
    }

    void reverse() {
        node_t *current = bottom->next;
        node_t *next;
        node_t *prev = top;
        top->prev->next = bottom;
        std::swap(top->prev, bottom->next);
        while (current != bottom) {
            next = current->next;
            current->next = prev;
            current->prev = next;
            prev = current;
            current = next;
        }
    }

    void swap(linkedList &other) {
        std::swap(this->bottom, other.bottom);
        std::swap(this->top, other.top);
        std::swap(list_size, other.list_size);
    }

    friend std::istream &operator>>(std::istream &stream, linkedList &list) {
        T value;
        std::string line;
        std::getline(stream, line);
        std::stringstream ss(line);
        while (!ss.eof()) {
            ss >> value;
            list.push_back(value);
        }
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, const linkedList &list) {
        for (int i = 0; i < list.size(); i++) {
            stream << list[i] << " ";
        }
        stream << "\n";
        return stream;
    }
};

int main() {
    linkedList<int> l1(4, 5);
    linkedList<int> l2(l1);
    l2.push_front(1);
    l2.insert(3, 10);
    assert(l2.size() == 6);
    assert(l2.back() == 5);
    assert(l2.front() == 1);
    assert(!l2.empty());
    l2.erase(2);
    l2.merge(l1);
    l2.pop_back();
    l2.pop_front();
    assert(l2.front() == 5);
    assert(l2.back() == 5);
    assert(l2.size() == 7);
    std::cout << l2.splice(0, 2) << std::endl;
    l2.clear();
    assert(l2.empty());
    l1.push_back(5);
    l1.push_back(8);
    l1.push_back(32);
    l2.swap(l1);
    assert(l2.size() == 3);
    assert(l1.empty());
    l2.push_back(11);
    l2.reverse();
    l2.insert(l2.size(), 7);
    assert(l2.back() == 7);
    l2 = l2;
    l1 = l2;
    std::cin >> l2;
    std::cout << l2;
    std::cout << l1;
}
